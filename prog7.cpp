#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc, char* argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	float recvbuf, sendbuf[100], gathbuf[100];
	float value;
	if (rank == 0) {
		printf("Before Scatter: Sendbuf Values of Rank 0:\n");
		for (int i = 0; i < size; i++) {
			srand(i);
			sendbuf[i] = (double)(rand() % 1000) / 10;
			printf("%.1f ", sendbuf[i]);
			value = sendbuf[0];
		}
		printf("\nAfter Scatter\n");
	}
	MPI_Scatter(sendbuf, 1, MPI_FLOAT, &recvbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	printf("Rank %d recvbbuf after scatter:  %.1f\n", rank, recvbuf);
	MPI_Bcast(&value, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	printf("Rank %d after broadcast:  %.1f\n", rank, value);
	MPI_Gather(&recvbuf, 1, MPI_FLOAT, &gathbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		printf("After Gather: rank 0: ");
		for (int i = 0; i < size; i++) {
			printf("%.1f ", gathbuf[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
}
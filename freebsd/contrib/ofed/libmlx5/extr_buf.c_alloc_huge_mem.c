#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_hugetlb_mem {int shmid; void* shmaddr; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  MLX5_DBG_CONTIG ; 
 size_t MLX5_Q_CHUNK_SIZE ; 
 int /*<<< orphan*/  MLX5_SHMAT_FLAGS ; 
 int /*<<< orphan*/  MLX5_SHM_ADDR ; 
 int /*<<< orphan*/  MLX5_SHM_LENGTH ; 
 int SHM_HUGETLB ; 
 int SHM_R ; 
 int SHM_W ; 
 size_t align (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct mlx5_hugetlb_mem*) ; 
 struct mlx5_hugetlb_mem* malloc (int) ; 
 scalar_t__ mlx5_bitmap_init (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* shmat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int shmdt (void*) ; 
 int shmget (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_hugetlb_mem *alloc_huge_mem(size_t size)
{
	struct mlx5_hugetlb_mem *hmem;
	size_t shm_len;

	hmem = malloc(sizeof(*hmem));
	if (!hmem)
		return NULL;

	shm_len = align(size, MLX5_SHM_LENGTH);
	hmem->shmid = shmget(IPC_PRIVATE, shm_len, SHM_HUGETLB | SHM_R | SHM_W);
	if (hmem->shmid == -1) {
		mlx5_dbg(stderr, MLX5_DBG_CONTIG, "%s\n", strerror(errno));
		goto out_free;
	}

	hmem->shmaddr = shmat(hmem->shmid, MLX5_SHM_ADDR, MLX5_SHMAT_FLAGS);
	if (hmem->shmaddr == (void *)-1) {
		mlx5_dbg(stderr, MLX5_DBG_CONTIG, "%s\n", strerror(errno));
		goto out_rmid;
	}

	if (mlx5_bitmap_init(&hmem->bitmap, shm_len / MLX5_Q_CHUNK_SIZE,
			     shm_len / MLX5_Q_CHUNK_SIZE - 1)) {
		mlx5_dbg(stderr, MLX5_DBG_CONTIG, "%s\n", strerror(errno));
		goto out_shmdt;
	}

	/*
	 * Marked to be destroyed when process detaches from shmget segment
	 */
	shmctl(hmem->shmid, IPC_RMID, NULL);

	return hmem;

out_shmdt:
	if (shmdt(hmem->shmaddr) == -1)
		mlx5_dbg(stderr, MLX5_DBG_CONTIG, "%s\n", strerror(errno));

out_rmid:
	shmctl(hmem->shmid, IPC_RMID, NULL);

out_free:
	free(hmem);
	return NULL;
}
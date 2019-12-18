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
struct mlx5_hugetlb_mem {int /*<<< orphan*/  shmid; int /*<<< orphan*/  shmaddr; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  MLX5_DBG_CONTIG ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct mlx5_hugetlb_mem*) ; 
 int /*<<< orphan*/  mlx5_bitmap_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int shmdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_huge_mem(struct mlx5_hugetlb_mem *hmem)
{
	mlx5_bitmap_cleanup(&hmem->bitmap);
	if (shmdt(hmem->shmaddr) == -1)
		mlx5_dbg(stderr, MLX5_DBG_CONTIG, "%s\n", strerror(errno));
	shmctl(hmem->shmid, IPC_RMID, NULL);
	free(hmem);
}
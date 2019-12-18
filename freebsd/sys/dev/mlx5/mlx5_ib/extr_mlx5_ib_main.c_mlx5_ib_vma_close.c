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
struct vm_area_struct {scalar_t__ vm_private_data; } ;
struct mlx5_ib_vma_private_data {int /*<<< orphan*/  list; int /*<<< orphan*/ * vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_ib_vma_private_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void  mlx5_ib_vma_close(struct vm_area_struct *area)
{
	struct mlx5_ib_vma_private_data *mlx5_ib_vma_priv_data;

	/* It's guaranteed that all VMAs opened on a FD are closed before the
	 * file itself is closed, therefore no sync is needed with the regular
	 * closing flow. (e.g. mlx5 ib_dealloc_ucontext)
	 * However need a sync with accessing the vma as part of
	 * mlx5_ib_disassociate_ucontext.
	 * The close operation is usually called under mm->mmap_sem except when
	 * process is exiting.
	 * The exiting case is handled explicitly as part of
	 * mlx5_ib_disassociate_ucontext.
	 */
	mlx5_ib_vma_priv_data = (struct mlx5_ib_vma_private_data *)area->vm_private_data;

	/* setting the vma context pointer to null in the mlx5_ib driver's
	 * private data, to protect a race condition in
	 * mlx5_ib_disassociate_ucontext().
	 */
	mlx5_ib_vma_priv_data->vma = NULL;
	list_del(&mlx5_ib_vma_priv_data->list);
	kfree(mlx5_ib_vma_priv_data);
}
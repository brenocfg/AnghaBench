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
struct mlx4_ib_vma_private_data {int /*<<< orphan*/ * vma; } ;

/* Variables and functions */

__attribute__((used)) static void  mlx4_ib_vma_close(struct vm_area_struct *area)
{
	struct mlx4_ib_vma_private_data *mlx4_ib_vma_priv_data;

	/* It's guaranteed that all VMAs opened on a FD are closed before the
	 * file itself is closed, therefore no sync is needed with the regular
	 * closing flow. (e.g. mlx4_ib_dealloc_ucontext) However need a sync
	 * with accessing the vma as part of mlx4_ib_disassociate_ucontext.
	 * The close operation is usually called under mm->mmap_sem except when
	 * process is exiting.  The exiting case is handled explicitly as part
	 * of mlx4_ib_disassociate_ucontext.
	 */
	mlx4_ib_vma_priv_data = (struct mlx4_ib_vma_private_data *)
				area->vm_private_data;

	/* set the vma context pointer to null in the mlx4_ib driver's private
	 * data to protect against a race condition in mlx4_ib_dissassociate_ucontext().
	 */
	mlx4_ib_vma_priv_data->vma = NULL;
}
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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; struct mlx5_ib_vma_private_data* vm_private_data; } ;
struct mlx5_ib_vma_private_data {int /*<<< orphan*/  list; struct vm_area_struct* vma; } ;
struct list_head {int dummy; } ;
struct mlx5_ib_ucontext {struct list_head vma_private_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_ib_vma_private_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mlx5_ib_vm_ops ; 

__attribute__((used)) static int mlx5_ib_set_vma_data(struct vm_area_struct *vma,
				struct mlx5_ib_ucontext *ctx)
{
	struct mlx5_ib_vma_private_data *vma_prv;
	struct list_head *vma_head = &ctx->vma_private_list;

	vma_prv = kzalloc(sizeof(*vma_prv), GFP_KERNEL);
	if (!vma_prv)
		return -ENOMEM;

	vma_prv->vma = vma;
	vma->vm_private_data = vma_prv;
	vma->vm_ops =  &mlx5_ib_vm_ops;

	list_add(&vma_prv->list, vma_head);

	return 0;
}
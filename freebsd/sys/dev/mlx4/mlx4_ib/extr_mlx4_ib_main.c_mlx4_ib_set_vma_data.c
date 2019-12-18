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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; struct mlx4_ib_vma_private_data* vm_private_data; } ;
struct mlx4_ib_vma_private_data {struct vm_area_struct* vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_ib_vm_ops ; 

__attribute__((used)) static void mlx4_ib_set_vma_data(struct vm_area_struct *vma,
				 struct mlx4_ib_vma_private_data *vma_private_data)
{
	vma_private_data->vma = vma;
	vma->vm_private_data = vma_private_data;
	vma->vm_ops =  &mlx4_ib_vm_ops;
}
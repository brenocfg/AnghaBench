#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_comp_vectors; } ;
struct TYPE_6__ {int disable_irqs; TYPE_2__* msix_arr; TYPE_1__ eq_table; } ;
struct mlx5_core_dev {TYPE_3__ priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int MLX5_EQ_VEC_COMP_BASE ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_disable_interrupts(struct mlx5_core_dev *mdev)
{
	int nvec = mdev->priv.eq_table.num_comp_vectors + MLX5_EQ_VEC_COMP_BASE;
	int x;

	mdev->priv.disable_irqs = 1;

	/* wait for all IRQ handlers to finish processing */
	for (x = 0; x != nvec; x++)
		synchronize_irq(mdev->priv.msix_arr[x].vector);
}
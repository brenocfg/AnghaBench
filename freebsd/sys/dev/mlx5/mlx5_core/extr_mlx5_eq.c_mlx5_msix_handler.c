#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_eq {struct mlx5_core_dev* dev; } ;
struct TYPE_2__ {scalar_t__ disable_irqs; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx5_eq_int (struct mlx5_core_dev*,struct mlx5_eq*) ; 

__attribute__((used)) static irqreturn_t mlx5_msix_handler(int irq, void *eq_ptr)
{
	struct mlx5_eq *eq = eq_ptr;
	struct mlx5_core_dev *dev = eq->dev;

	/* check if IRQs are not disabled */
	if (likely(dev->priv.disable_irqs == 0))
		mlx5_eq_int(dev, eq);

	/* MSI-X vectors always belong to us */
	return IRQ_HANDLED;
}
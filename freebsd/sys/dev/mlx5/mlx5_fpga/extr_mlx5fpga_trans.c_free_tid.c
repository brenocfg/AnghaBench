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
struct mlx5_fpga_trans_priv {int /*<<< orphan*/  list_item; } ;
struct mlx5_fpga_device {TYPE_1__* trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_tid(struct mlx5_fpga_device *fdev,
		     struct mlx5_fpga_trans_priv *trans_priv)
{
	unsigned long flags;

	spin_lock_irqsave(&fdev->trans->lock, flags);
	list_add_tail(&trans_priv->list_item, &fdev->trans->free_queue);
	spin_unlock_irqrestore(&fdev->trans->lock, flags);
}
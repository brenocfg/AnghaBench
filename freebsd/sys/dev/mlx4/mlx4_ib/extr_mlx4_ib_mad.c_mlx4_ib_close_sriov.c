#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int is_going_down; TYPE_2__* demux; int /*<<< orphan*/ ** sqps; int /*<<< orphan*/  going_down_lock; } ;
struct mlx4_ib_dev {int num_ports; TYPE_1__ sriov; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ud_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_cm_paravirt_clean (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx4_ib_destroy_alias_guid_service (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_device_unregister_sysfs (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_free_demux_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx4_ib_free_sqp_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_is_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_is_mfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx4_ib_close_sriov(struct mlx4_ib_dev *dev)
{
	int i;
	unsigned long flags;

	if (!mlx4_is_mfunc(dev->dev))
		return;

	spin_lock_irqsave(&dev->sriov.going_down_lock, flags);
	dev->sriov.is_going_down = 1;
	spin_unlock_irqrestore(&dev->sriov.going_down_lock, flags);
	if (mlx4_is_master(dev->dev)) {
		for (i = 0; i < dev->num_ports; i++) {
			flush_workqueue(dev->sriov.demux[i].ud_wq);
			mlx4_ib_free_sqp_ctx(dev->sriov.sqps[i]);
			kfree(dev->sriov.sqps[i]);
			dev->sriov.sqps[i] = NULL;
			mlx4_ib_free_demux_ctx(&dev->sriov.demux[i]);
		}

		mlx4_ib_cm_paravirt_clean(dev, -1);
		mlx4_ib_destroy_alias_guid_service(dev);
		mlx4_ib_device_unregister_sysfs(dev);
	}
}
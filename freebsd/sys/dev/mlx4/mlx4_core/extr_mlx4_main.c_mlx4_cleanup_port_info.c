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
struct mlx4_port_info {scalar_t__ port; int /*<<< orphan*/ * rmap; int /*<<< orphan*/  port_mtu_attr; TYPE_2__* dev; int /*<<< orphan*/  port_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* persist; } ;
struct TYPE_4__ {TYPE_3__* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_cleanup_port_info(struct mlx4_port_info *info)
{
	if (info->port < 0)
		return;

	device_remove_file(&info->dev->persist->pdev->dev, &info->port_attr);
	device_remove_file(&info->dev->persist->pdev->dev,
			   &info->port_mtu_attr);
#ifdef CONFIG_RFS_ACCEL
	free_irq_cpu_rmap(info->rmap);
	info->rmap = NULL;
#endif
}
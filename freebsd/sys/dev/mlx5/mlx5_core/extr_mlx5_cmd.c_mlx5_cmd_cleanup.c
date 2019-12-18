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
struct TYPE_3__ {int /*<<< orphan*/  wq_cmd; } ;
struct TYPE_4__ {TYPE_1__ health; } ;
struct mlx5_cmd {int dummy; } ;
struct mlx5_core_dev {TYPE_2__ priv; struct mlx5_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_debug_files (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  destroy_msg_cache (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd_page (struct mlx5_core_dev*,struct mlx5_cmd*) ; 

void mlx5_cmd_cleanup(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd *cmd = &dev->cmd;

	clean_debug_files(dev);
	flush_workqueue(dev->priv.health.wq_cmd);
	destroy_msg_cache(dev);
	free_cmd_page(dev, cmd);
}
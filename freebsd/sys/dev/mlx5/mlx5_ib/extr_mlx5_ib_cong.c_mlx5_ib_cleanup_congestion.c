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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctx; int /*<<< orphan*/  dwork; } ;
struct mlx5_ib_dev {TYPE_1__ congestion; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

void
mlx5_ib_cleanup_congestion(struct mlx5_ib_dev *dev)
{

	while (cancel_delayed_work_sync(&dev->congestion.dwork))
		;
	sysctl_ctx_free(&dev->congestion.ctx);
	sx_destroy(&dev->congestion.lock);
}
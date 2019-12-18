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
struct skd_device {char const* skcomp_ix; struct skd_device* skcomp_cycle; TYPE_1__* pdev; int /*<<< orphan*/  queue_low_water_mark; int /*<<< orphan*/  dev_max_queue_depth; int /*<<< orphan*/  cur_max_queue_depth; int /*<<< orphan*/  state; int /*<<< orphan*/  drive_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct skd_device*,char const*,...) ; 
 int /*<<< orphan*/  skd_drive_state_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skd_in_flight (struct skd_device*) ; 
 int /*<<< orphan*/  skd_skdev_state_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skd_log_skdev(struct skd_device *skdev, const char *event)
{
	dev_dbg(&skdev->pdev->dev, "skdev=%p event='%s'\n", skdev, event);
	dev_dbg(&skdev->pdev->dev, "  drive_state=%s(%d) driver_state=%s(%d)\n",
		skd_drive_state_to_str(skdev->drive_state), skdev->drive_state,
		skd_skdev_state_to_str(skdev->state), skdev->state);
	dev_dbg(&skdev->pdev->dev, "  busy=%d limit=%d dev=%d lowat=%d\n",
		skd_in_flight(skdev), skdev->cur_max_queue_depth,
		skdev->dev_max_queue_depth, skdev->queue_low_water_mark);
	dev_dbg(&skdev->pdev->dev, "  cycle=%d cycle_ix=%d\n",
		skdev->skcomp_cycle, skdev->skcomp_ix);
}
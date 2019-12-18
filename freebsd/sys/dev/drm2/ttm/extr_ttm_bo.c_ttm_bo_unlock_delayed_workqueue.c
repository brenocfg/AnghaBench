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
struct ttm_bo_device {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int hz ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void ttm_bo_unlock_delayed_workqueue(struct ttm_bo_device *bdev, int resched)
{
	if (resched) {
		taskqueue_enqueue_timeout(taskqueue_thread, &bdev->wq,
		    ((hz / 100) < 1) ? 1 : hz / 100);
	}
}
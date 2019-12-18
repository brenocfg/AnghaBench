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
struct gnss_device {int disconnected; int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  rwsem; TYPE_1__* ops; int /*<<< orphan*/  read_queue; scalar_t__ count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct gnss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gnss_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void gnss_deregister_device(struct gnss_device *gdev)
{
	down_write(&gdev->rwsem);
	gdev->disconnected = true;
	if (gdev->count) {
		wake_up_interruptible(&gdev->read_queue);
		gdev->ops->close(gdev);
	}
	up_write(&gdev->rwsem);

	cdev_device_del(&gdev->cdev, &gdev->dev);
}
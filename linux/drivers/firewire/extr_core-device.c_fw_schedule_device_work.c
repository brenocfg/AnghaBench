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
struct fw_device {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fw_schedule_device_work(struct fw_device *device,
				    unsigned long delay)
{
	queue_delayed_work(fw_workqueue, &device->work, delay);
}
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
struct gnss_device {int /*<<< orphan*/  read_queue; int /*<<< orphan*/  read_fifo; } ;

/* Variables and functions */
 int kfifo_in (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int gnss_insert_raw(struct gnss_device *gdev, const unsigned char *buf,
				size_t count)
{
	int ret;

	ret = kfifo_in(&gdev->read_fifo, buf, count);

	wake_up_interruptible(&gdev->read_queue);

	return ret;
}
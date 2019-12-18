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
struct gnss_device {scalar_t__ disconnected; int /*<<< orphan*/  read_fifo; int /*<<< orphan*/  read_queue; } ;
struct file {struct gnss_device* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t gnss_poll(struct file *file, poll_table *wait)
{
	struct gnss_device *gdev = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &gdev->read_queue, wait);

	if (!kfifo_is_empty(&gdev->read_fifo))
		mask |= EPOLLIN | EPOLLRDNORM;
	if (gdev->disconnected)
		mask |= EPOLLHUP;

	return mask;
}
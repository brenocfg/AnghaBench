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
struct ipmb_dev {int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  request_queue_len; int /*<<< orphan*/  wait_queue; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipmb_dev* to_ipmb_dev (struct file*) ; 

__attribute__((used)) static unsigned int ipmb_poll(struct file *file, poll_table *wait)
{
	struct ipmb_dev *ipmb_dev = to_ipmb_dev(file);
	unsigned int mask = POLLOUT;

	mutex_lock(&ipmb_dev->file_mutex);
	poll_wait(file, &ipmb_dev->wait_queue, wait);

	if (atomic_read(&ipmb_dev->request_queue_len))
		mask |= POLLIN;
	mutex_unlock(&ipmb_dev->file_mutex);

	return mask;
}
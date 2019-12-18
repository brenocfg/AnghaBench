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
struct file {struct client* private_data; } ;
struct client {int /*<<< orphan*/  event_list; int /*<<< orphan*/  device; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ fw_device_is_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t fw_device_op_poll(struct file *file, poll_table * pt)
{
	struct client *client = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &client->wait, pt);

	if (fw_device_is_shutdown(client->device))
		mask |= EPOLLHUP | EPOLLERR;
	if (!list_empty(&client->event_list))
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}
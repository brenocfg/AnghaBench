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
struct port {int /*<<< orphan*/  host_connected; int /*<<< orphan*/  guest_connected; int /*<<< orphan*/  waitqueue; } ;
struct file {struct port* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  will_read_block (struct port*) ; 
 int /*<<< orphan*/  will_write_block (struct port*) ; 

__attribute__((used)) static __poll_t port_fops_poll(struct file *filp, poll_table *wait)
{
	struct port *port;
	__poll_t ret;

	port = filp->private_data;
	poll_wait(filp, &port->waitqueue, wait);

	if (!port->guest_connected) {
		/* Port got unplugged */
		return EPOLLHUP;
	}
	ret = 0;
	if (!will_read_block(port))
		ret |= EPOLLIN | EPOLLRDNORM;
	if (!will_write_block(port))
		ret |= EPOLLOUT;
	if (!port->host_connected)
		ret |= EPOLLHUP;

	return ret;
}
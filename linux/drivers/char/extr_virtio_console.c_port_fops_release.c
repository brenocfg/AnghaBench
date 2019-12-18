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
struct port {int guest_connected; int /*<<< orphan*/  kref; int /*<<< orphan*/  outvq_lock; int /*<<< orphan*/  inbuf_lock; } ;
struct inode {int dummy; } ;
struct file {struct port* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONSOLE_PORT_OPEN ; 
 int /*<<< orphan*/  discard_port_data (struct port*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reclaim_consumed_buffers (struct port*) ; 
 int /*<<< orphan*/  reclaim_dma_bufs () ; 
 int /*<<< orphan*/  remove_port ; 
 int /*<<< orphan*/  send_control_msg (struct port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_fops_release(struct inode *inode, struct file *filp)
{
	struct port *port;

	port = filp->private_data;

	/* Notify host of port being closed */
	send_control_msg(port, VIRTIO_CONSOLE_PORT_OPEN, 0);

	spin_lock_irq(&port->inbuf_lock);
	port->guest_connected = false;

	discard_port_data(port);

	spin_unlock_irq(&port->inbuf_lock);

	spin_lock_irq(&port->outvq_lock);
	reclaim_consumed_buffers(port);
	spin_unlock_irq(&port->outvq_lock);

	reclaim_dma_bufs();
	/*
	 * Locks aren't necessary here as a port can't be opened after
	 * unplug, and if a port isn't unplugged, a kref would already
	 * exist for the port.  Plus, taking ports_lock here would
	 * create a dependency on other locks taken by functions
	 * inside remove_port if we're the last holder of the port,
	 * creating many problems.
	 */
	kref_put(&port->kref, remove_port);

	return 0;
}
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
struct mcast_port {int port_num; int /*<<< orphan*/  refcount; int /*<<< orphan*/  comp; int /*<<< orphan*/  table; int /*<<< orphan*/  lock; struct mcast_device* dev; } ;
struct mcast_device {int start_port; int end_port; int /*<<< orphan*/  event_handler; struct ib_device* device; struct mcast_port* port; } ;
struct ib_device {int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct mcast_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_device*) ; 
 struct mcast_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcast_client ; 
 int /*<<< orphan*/  mcast_event_handler ; 
 int /*<<< orphan*/  rdma_cap_ib_mcast (struct ib_device*,int) ; 
 int rdma_end_port (struct ib_device*) ; 
 int rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcast_add_one(struct ib_device *device)
{
	struct mcast_device *dev;
	struct mcast_port *port;
	int i;
	int count = 0;

	dev = kmalloc(sizeof *dev + device->phys_port_cnt * sizeof *port,
		      GFP_KERNEL);
	if (!dev)
		return;

	dev->start_port = rdma_start_port(device);
	dev->end_port = rdma_end_port(device);

	for (i = 0; i <= dev->end_port - dev->start_port; i++) {
		if (!rdma_cap_ib_mcast(device, dev->start_port + i))
			continue;
		port = &dev->port[i];
		port->dev = dev;
		port->port_num = dev->start_port + i;
		spin_lock_init(&port->lock);
		port->table = RB_ROOT;
		init_completion(&port->comp);
		atomic_set(&port->refcount, 1);
		++count;
	}

	if (!count) {
		kfree(dev);
		return;
	}

	dev->device = device;
	ib_set_client_data(device, &mcast_client, dev);

	INIT_IB_EVENT_HANDLER(&dev->event_handler, device, mcast_event_handler);
	ib_register_event_handler(&dev->event_handler);
}
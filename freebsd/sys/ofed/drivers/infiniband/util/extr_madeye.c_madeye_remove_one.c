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
struct madeye_port {int /*<<< orphan*/  gsi_agent; int /*<<< orphan*/  smi_agent; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 scalar_t__ ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct madeye_port*) ; 
 int /*<<< orphan*/  madeye_client ; 

__attribute__((used)) static void madeye_remove_one(struct ib_device *device)
{
	struct madeye_port *port;
	int i, s, e;

	port = (struct madeye_port *)
		ib_get_client_data(device, &madeye_client);
	if (!port)
		return;

	if (device->node_type == RDMA_NODE_IB_SWITCH) {
		s = 0;
		e = 0;
	} else {
		s = 1;
		e = device->phys_port_cnt;
	}

	for (i = 0; i <= e - s; i++) {
		if (!IS_ERR(port[i].smi_agent))
			ib_unregister_mad_agent(port[i].smi_agent);
		if (!IS_ERR(port[i].gsi_agent))
			ib_unregister_mad_agent(port[i].gsi_agent);
	}
	kfree(port);
}
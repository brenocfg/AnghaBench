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
typedef  int u8 ;
struct madeye_port {void* gsi_agent; void* smi_agent; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_MAD_SNOOP_RECVS ; 
 int IB_MAD_SNOOP_SEND_COMPLETIONS ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_QPT_SMI ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 void* ib_register_mad_snoop (struct ib_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct madeye_port*) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct madeye_port*) ; 
 struct madeye_port* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madeye_client ; 
 int /*<<< orphan*/  recv_gsi_handler ; 
 int /*<<< orphan*/  recv_smi_handler ; 
 int /*<<< orphan*/  snoop_gsi_handler ; 
 int /*<<< orphan*/  snoop_smi_handler ; 

__attribute__((used)) static void madeye_add_one(struct ib_device *device)
{
	struct madeye_port *port;
	int reg_flags;
	u8 i, s, e;

	if (device->node_type == RDMA_NODE_IB_SWITCH) {
		s = 0;
		e = 0;
	} else {
		s = 1;
		e = device->phys_port_cnt;
	}

	port = kmalloc(sizeof *port * (e - s + 1), GFP_KERNEL);
	if (!port)
		goto out;

	reg_flags = IB_MAD_SNOOP_SEND_COMPLETIONS | IB_MAD_SNOOP_RECVS;
	for (i = 0; i <= e - s; i++) {
		port[i].smi_agent = ib_register_mad_snoop(device, i + s,
							  IB_QPT_SMI,
							  reg_flags,
							  snoop_smi_handler,
							  recv_smi_handler,
							  &port[i]);
		port[i].gsi_agent = ib_register_mad_snoop(device, i + s,
							  IB_QPT_GSI,
							  reg_flags,
							  snoop_gsi_handler,
							  recv_gsi_handler,
							  &port[i]);
	}

out:
	ib_set_client_data(device, &madeye_client, port);
}
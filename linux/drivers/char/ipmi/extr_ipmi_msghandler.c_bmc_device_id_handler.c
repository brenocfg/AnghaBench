#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipmi_smi {int /*<<< orphan*/  waitq; TYPE_3__* bmc; int /*<<< orphan*/  si_dev; } ;
struct TYPE_5__ {scalar_t__ netfn; scalar_t__ cmd; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ addr_type; } ;
struct ipmi_recv_msg {TYPE_2__ msg; TYPE_1__ addr; } ;
struct TYPE_6__ {int dyn_id_set; int /*<<< orphan*/  fetch_id; } ;

/* Variables and functions */
 scalar_t__ IPMI_GET_DEVICE_ID_CMD ; 
 scalar_t__ IPMI_NETFN_APP_RESPONSE ; 
 scalar_t__ IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,...) ; 
 int ipmi_demangle_device_id (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bmc_device_id_handler(struct ipmi_smi *intf,
				  struct ipmi_recv_msg *msg)
{
	int rv;

	if ((msg->addr.addr_type != IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
			|| (msg->msg.netfn != IPMI_NETFN_APP_RESPONSE)
			|| (msg->msg.cmd != IPMI_GET_DEVICE_ID_CMD)) {
		dev_warn(intf->si_dev,
			 "invalid device_id msg: addr_type=%d netfn=%x cmd=%x\n",
			 msg->addr.addr_type, msg->msg.netfn, msg->msg.cmd);
		return;
	}

	rv = ipmi_demangle_device_id(msg->msg.netfn, msg->msg.cmd,
			msg->msg.data, msg->msg.data_len, &intf->bmc->fetch_id);
	if (rv) {
		dev_warn(intf->si_dev, "device id demangle failed: %d\n", rv);
		intf->bmc->dyn_id_set = 0;
	} else {
		/*
		 * Make sure the id data is available before setting
		 * dyn_id_set.
		 */
		smp_wmb();
		intf->bmc->dyn_id_set = 1;
	}

	wake_up(&intf->waitq);
}
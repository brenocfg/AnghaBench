#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kernel_ipmi_msg {int netfn; unsigned char* data; int data_len; int /*<<< orphan*/  cmd; } ;
struct ipmi_user {int dummy; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_ipmb_addr {unsigned char slave_addr; unsigned char lun; scalar_t__ channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;
struct TYPE_3__ {int* data; } ;
struct TYPE_4__ {TYPE_1__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_CMD_GET_EVENT_RECEIVER ; 
 int /*<<< orphan*/  IPMI_IPMB_ADDR_TYPE ; 
 int IPMI_NETFN_OEM_1 ; 
 int IPMI_NETFN_OEM_8 ; 
 int IPMI_NETFN_SENSOR_EVT ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  OEM_GRP_CMD_GET_SLOT_GA ; 
 int /*<<< orphan*/  OEM_GRP_CMD_REQUEST_HOTSWAP_CTRL ; 
 int /*<<< orphan*/  OEM_GRP_CMD_SET_POWER_STATE ; 
 int /*<<< orphan*/  OEM_GRP_CMD_SET_RESET_STATE ; 
 TYPE_2__ halt_recv_msg ; 
 int ipmi_request_in_rc_mode (struct ipmi_user*,struct ipmi_addr*,struct kernel_ipmi_msg*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void ipmi_poweroff_cpi1(struct ipmi_user *user)
{
	struct ipmi_system_interface_addr smi_addr;
	struct ipmi_ipmb_addr             ipmb_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;
	unsigned char                     data[1];
	int                               slot;
	unsigned char                     hotswap_ipmb;
	unsigned char                     aer_addr;
	unsigned char                     aer_lun;

	/*
	 * Configure IPMI address for local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	pr_info("Powering down via CPI1 power command\n");

	/*
	 * Get IPMI ipmb address
	 */
	send_msg.netfn = IPMI_NETFN_OEM_8 >> 2;
	send_msg.cmd = OEM_GRP_CMD_GET_SLOT_GA;
	send_msg.data = NULL;
	send_msg.data_len = 0;
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	if (rv)
		goto out;
	slot = halt_recv_msg.msg.data[1];
	hotswap_ipmb = (slot > 9) ? (0xb0 + 2 * slot) : (0xae + 2 * slot);

	/*
	 * Get active event receiver
	 */
	send_msg.netfn = IPMI_NETFN_SENSOR_EVT >> 2;
	send_msg.cmd = IPMI_CMD_GET_EVENT_RECEIVER;
	send_msg.data = NULL;
	send_msg.data_len = 0;
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	if (rv)
		goto out;
	aer_addr = halt_recv_msg.msg.data[1];
	aer_lun = halt_recv_msg.msg.data[2];

	/*
	 * Setup IPMB address target instead of local target
	 */
	ipmb_addr.addr_type = IPMI_IPMB_ADDR_TYPE;
	ipmb_addr.channel = 0;
	ipmb_addr.slave_addr = aer_addr;
	ipmb_addr.lun = aer_lun;

	/*
	 * Send request hotswap control to remove blade from dpv
	 */
	send_msg.netfn = IPMI_NETFN_OEM_8 >> 2;
	send_msg.cmd = OEM_GRP_CMD_REQUEST_HOTSWAP_CTRL;
	send_msg.data = &hotswap_ipmb;
	send_msg.data_len = 1;
	ipmi_request_in_rc_mode(user,
				(struct ipmi_addr *) &ipmb_addr,
				&send_msg);

	/*
	 * Set reset asserted
	 */
	send_msg.netfn = IPMI_NETFN_OEM_1 >> 2;
	send_msg.cmd = OEM_GRP_CMD_SET_RESET_STATE;
	send_msg.data = data;
	data[0] = 1; /* Reset asserted state */
	send_msg.data_len = 1;
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	if (rv)
		goto out;

	/*
	 * Power down
	 */
	send_msg.netfn = IPMI_NETFN_OEM_1 >> 2;
	send_msg.cmd = OEM_GRP_CMD_SET_POWER_STATE;
	send_msg.data = data;
	data[0] = 1; /* Power down state */
	send_msg.data_len = 1;
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	if (rv)
		goto out;

 out:
	return;
}
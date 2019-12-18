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
struct kernel_ipmi_msg {unsigned char* data; int data_len; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct ipmi_user {int dummy; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_ATCA_SET_POWER_CMD ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_NETFN_ATCA ; 
 unsigned char IPMI_PICMG_ID ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int IPMI_UNKNOWN_ERR_COMPLETION_CODE ; 
 int /*<<< orphan*/  atca_oem_poweroff_hook (struct ipmi_user*) ; 
 int ipmi_request_in_rc_mode (struct ipmi_user*,struct ipmi_addr*,struct kernel_ipmi_msg*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void ipmi_poweroff_atca(struct ipmi_user *user)
{
	struct ipmi_system_interface_addr smi_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;
	unsigned char                     data[4];

	/*
	 * Configure IPMI address for local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	pr_info("Powering down via ATCA power command\n");

	/*
	 * Power down
	 */
	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_SET_POWER_CMD;
	data[0] = IPMI_PICMG_ID;
	data[1] = 0; /* FRU id */
	data[2] = 0; /* Power Level */
	data[3] = 0; /* Don't change saved presets */
	send_msg.data = data;
	send_msg.data_len = sizeof(data);
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	/*
	 * At this point, the system may be shutting down, and most
	 * serial drivers (if used) will have interrupts turned off
	 * it may be better to ignore IPMI_UNKNOWN_ERR_COMPLETION_CODE
	 * return code
	 */
	if (rv && rv != IPMI_UNKNOWN_ERR_COMPLETION_CODE) {
		pr_err("Unable to send ATCA powerdown message, IPMI error 0x%x\n",
		       rv);
		goto out;
	}

	if (atca_oem_poweroff_hook)
		atca_oem_poweroff_hook(user);
 out:
	return;
}
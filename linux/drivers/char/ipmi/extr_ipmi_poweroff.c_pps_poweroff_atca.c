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
struct kernel_ipmi_msg {int data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct ipmi_user {int dummy; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_ATCA_PPS_GRACEFUL_RESTART ; 
 int /*<<< orphan*/  IPMI_ATCA_PPS_IANA ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_NETFN_OEM ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int IPMI_UNKNOWN_ERR_COMPLETION_CODE ; 
 int ipmi_request_in_rc_mode (struct ipmi_user*,struct ipmi_addr*,struct kernel_ipmi_msg*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void pps_poweroff_atca(struct ipmi_user *user)
{
	struct ipmi_system_interface_addr smi_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;
	/*
	 * Configure IPMI address for local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	pr_info("PPS powerdown hook used\n");

	send_msg.netfn = IPMI_NETFN_OEM;
	send_msg.cmd = IPMI_ATCA_PPS_GRACEFUL_RESTART;
	send_msg.data = IPMI_ATCA_PPS_IANA;
	send_msg.data_len = 3;
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	if (rv && rv != IPMI_UNKNOWN_ERR_COMPLETION_CODE)
		pr_err("Unable to send ATCA, IPMI error 0x%x\n", rv);

	return;
}
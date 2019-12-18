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
 int /*<<< orphan*/  IPMI_ATCA_GET_ADDR_INFO_CMD ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 scalar_t__ IPMI_MOTOROLA_MANUFACTURER_ID ; 
 scalar_t__ IPMI_MOTOROLA_PPS_IPMC_PRODUCT_ID ; 
 int /*<<< orphan*/  IPMI_NETFN_ATCA ; 
 unsigned char IPMI_PICMG_ID ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  atca_oem_poweroff_hook ; 
 int ipmi_request_wait_for_response (struct ipmi_user*,struct ipmi_addr*,struct kernel_ipmi_msg*) ; 
 scalar_t__ mfg_id ; 
 int /*<<< orphan*/  pps_poweroff_atca ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__ prod_id ; 

__attribute__((used)) static int ipmi_atca_detect(struct ipmi_user *user)
{
	struct ipmi_system_interface_addr smi_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;
	unsigned char                     data[1];

	/*
	 * Configure IPMI address for local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	/*
	 * Use get address info to check and see if we are ATCA
	 */
	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_GET_ADDR_INFO_CMD;
	data[0] = IPMI_PICMG_ID;
	send_msg.data = data;
	send_msg.data_len = sizeof(data);
	rv = ipmi_request_wait_for_response(user,
					    (struct ipmi_addr *) &smi_addr,
					    &send_msg);

	pr_info("ATCA Detect mfg 0x%X prod 0x%X\n", mfg_id, prod_id);
	if ((mfg_id == IPMI_MOTOROLA_MANUFACTURER_ID)
	    && (prod_id == IPMI_MOTOROLA_PPS_IPMC_PRODUCT_ID)) {
		pr_info("Installing Pigeon Point Systems Poweroff Hook\n");
		atca_oem_poweroff_hook = pps_poweroff_atca;
	}
	return !rv;
}
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
struct kernel_ipmi_msg {scalar_t__ data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int data_len; int* data; } ;
struct TYPE_6__ {TYPE_1__ msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  poweroff_func; int /*<<< orphan*/  platform_type; scalar_t__ (* detect ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_GET_DEVICE_ID_CMD ; 
 int /*<<< orphan*/  IPMI_NETFN_APP_REQUEST ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int NUM_PO_FUNCS ; 
 int capabilities ; 
 TYPE_3__ halt_recv_msg ; 
 int ifnum_to_use ; 
 int ipmi_create_user (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int ipmi_ifnum ; 
 int /*<<< orphan*/  ipmi_poweroff_function ; 
 int /*<<< orphan*/  ipmi_poweroff_handler ; 
 int ipmi_request_wait_for_response (int /*<<< orphan*/ ,struct ipmi_addr*,struct kernel_ipmi_msg*) ; 
 int /*<<< orphan*/  ipmi_user ; 
 int ipmi_version ; 
 int mfg_id ; 
 int /*<<< orphan*/  old_poweroff_func ; 
 int /*<<< orphan*/  pm_power_off ; 
 TYPE_2__* poweroff_functions ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int prod_id ; 
 int ready ; 
 int /*<<< orphan*/  specific_poweroff_func ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmi_po_new_smi(int if_num, struct device *device)
{
	struct ipmi_system_interface_addr smi_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;
	int                               i;

	if (ready)
		return;

	if ((ifnum_to_use >= 0) && (ifnum_to_use != if_num))
		return;

	rv = ipmi_create_user(if_num, &ipmi_poweroff_handler, NULL,
			      &ipmi_user);
	if (rv) {
		pr_err("could not create IPMI user, error %d\n", rv);
		return;
	}

	ipmi_ifnum = if_num;

	/*
	 * Do a get device ide and store some results, since this is
	 * used by several functions.
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	send_msg.netfn = IPMI_NETFN_APP_REQUEST;
	send_msg.cmd = IPMI_GET_DEVICE_ID_CMD;
	send_msg.data = NULL;
	send_msg.data_len = 0;
	rv = ipmi_request_wait_for_response(ipmi_user,
					    (struct ipmi_addr *) &smi_addr,
					    &send_msg);
	if (rv) {
		pr_err("Unable to send IPMI get device id info, IPMI error 0x%x\n",
		       rv);
		goto out_err;
	}

	if (halt_recv_msg.msg.data_len < 12) {
		pr_err("(chassis) IPMI get device id info too short, was %d bytes, needed %d bytes\n",
		       halt_recv_msg.msg.data_len, 12);
		goto out_err;
	}

	mfg_id = (halt_recv_msg.msg.data[7]
		  | (halt_recv_msg.msg.data[8] << 8)
		  | (halt_recv_msg.msg.data[9] << 16));
	prod_id = (halt_recv_msg.msg.data[10]
		   | (halt_recv_msg.msg.data[11] << 8));
	capabilities = halt_recv_msg.msg.data[6];
	ipmi_version = halt_recv_msg.msg.data[5];


	/* Scan for a poweroff method */
	for (i = 0; i < NUM_PO_FUNCS; i++) {
		if (poweroff_functions[i].detect(ipmi_user))
			goto found;
	}

 out_err:
	pr_err("Unable to find a poweroff function that will work, giving up\n");
	ipmi_destroy_user(ipmi_user);
	return;

 found:
	pr_info("Found a %s style poweroff function\n",
		poweroff_functions[i].platform_type);
	specific_poweroff_func = poweroff_functions[i].poweroff_func;
	old_poweroff_func = pm_power_off;
	pm_power_off = ipmi_poweroff_function;
	ready = 1;
}
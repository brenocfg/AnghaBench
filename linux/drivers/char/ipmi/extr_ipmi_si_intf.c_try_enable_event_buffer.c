#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smi_info {int supports_event_msg_buff; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; } ;
struct TYPE_2__ {unsigned long (* get_result ) (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char IPMI_BMC_EVT_MSG_BUFF ; 
 unsigned char IPMI_GET_BMC_GLOBAL_ENABLES_CMD ; 
 int /*<<< orphan*/  IPMI_MAX_MSG_LENGTH ; 
 int IPMI_NETFN_APP_REQUEST ; 
 unsigned char IPMI_SET_BMC_GLOBAL_ENABLES_CMD ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned long stub2 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned long stub4 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int wait_for_msg_done (struct smi_info*) ; 

__attribute__((used)) static int try_enable_event_buffer(struct smi_info *smi_info)
{
	unsigned char         msg[3];
	unsigned char         *resp;
	unsigned long         resp_len;
	int                   rv = 0;

	resp = kmalloc(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	if (!resp)
		return -ENOMEM;

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_BMC_GLOBAL_ENABLES_CMD;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 2);

	rv = wait_for_msg_done(smi_info);
	if (rv) {
		pr_warn("Error getting response from get global enables command, the event buffer is not enabled\n");
		goto out;
	}

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	if (resp_len < 4 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_GET_BMC_GLOBAL_ENABLES_CMD   ||
			resp[2] != 0) {
		pr_warn("Invalid return from get global enables command, cannot enable the event buffer\n");
		rv = -EINVAL;
		goto out;
	}

	if (resp[3] & IPMI_BMC_EVT_MSG_BUFF) {
		/* buffer is already enabled, nothing to do. */
		smi_info->supports_event_msg_buff = true;
		goto out;
	}

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
	msg[2] = resp[3] | IPMI_BMC_EVT_MSG_BUFF;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 3);

	rv = wait_for_msg_done(smi_info);
	if (rv) {
		pr_warn("Error getting response from set global, enables command, the event buffer is not enabled\n");
		goto out;
	}

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	if (resp_len < 3 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_SET_BMC_GLOBAL_ENABLES_CMD) {
		pr_warn("Invalid return from get global, enables command, not enable the event buffer\n");
		rv = -EINVAL;
		goto out;
	}

	if (resp[2] != 0)
		/*
		 * An error when setting the event buffer bit means
		 * that the event buffer is not supported.
		 */
		rv = -ENOENT;
	else
		smi_info->supports_event_msg_buff = true;

out:
	kfree(resp);
	return rv;
}
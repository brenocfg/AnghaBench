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
struct smi_info {int /*<<< orphan*/  device_id; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; } ;
struct TYPE_2__ {unsigned long (* get_result ) (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char IPMI_GET_DEVICE_ID_CMD ; 
 int /*<<< orphan*/  IPMI_MAX_MSG_LENGTH ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int ipmi_demangle_device_id (unsigned char,unsigned char,unsigned char*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned long stub2 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int wait_for_msg_done (struct smi_info*) ; 

__attribute__((used)) static int try_get_dev_id(struct smi_info *smi_info)
{
	unsigned char         msg[2];
	unsigned char         *resp;
	unsigned long         resp_len;
	int                   rv = 0;

	resp = kmalloc(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	if (!resp)
		return -ENOMEM;

	/*
	 * Do a Get Device ID command, since it comes back with some
	 * useful info.
	 */
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_DEVICE_ID_CMD;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 2);

	rv = wait_for_msg_done(smi_info);
	if (rv)
		goto out;

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	/* Check and record info from the get device id, in case we need it. */
	rv = ipmi_demangle_device_id(resp[0] >> 2, resp[1],
			resp + 2, resp_len - 2, &smi_info->device_id);

out:
	kfree(resp);
	return rv;
}
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
typedef  unsigned char u8 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct smi_info {TYPE_2__ io; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; } ;
struct TYPE_3__ {unsigned long (* get_result ) (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPMI_MAX_MSG_LENGTH ; 
 int IPMI_NETFN_APP_REQUEST ; 
 unsigned char IPMI_SET_BMC_GLOBAL_ENABLES_CMD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned long stub2 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int wait_for_msg_done (struct smi_info*) ; 

__attribute__((used)) static int set_global_enables(struct smi_info *smi_info, u8 enables)
{
	unsigned char         msg[3];
	unsigned char         *resp;
	unsigned long         resp_len;
	int                   rv;

	resp = kmalloc(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	if (!resp)
		return -ENOMEM;

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
	msg[2] = enables;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 3);

	rv = wait_for_msg_done(smi_info);
	if (rv) {
		dev_warn(smi_info->io.dev,
			 "Error getting response from set global enables command: %d\n",
			 rv);
		goto out;
	}

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	if (resp_len < 3 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_SET_BMC_GLOBAL_ENABLES_CMD) {
		dev_warn(smi_info->io.dev,
			 "Invalid return from set global enables command: %ld %x %x\n",
			 resp_len, resp[0], resp[1]);
		rv = -EINVAL;
		goto out;
	}

	if (resp[2] != 0)
		rv = 1;

out:
	kfree(resp);
	return rv;
}
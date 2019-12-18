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
struct kernel_ipmi_msg {int data_len; struct ipmi_addr* data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct ipmi_user {int dummy; } ;
struct TYPE_2__ {int data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct ipmi_req {int addr_len; int /*<<< orphan*/  msgid; TYPE_1__ msg; int /*<<< orphan*/ * addr; } ;
struct ipmi_addr {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPMI_MAX_MSG_LENGTH ; 
 scalar_t__ copy_from_user (struct ipmi_addr*,int /*<<< orphan*/ *,int) ; 
 int ipmi_request_settime (struct ipmi_user*,struct ipmi_addr*,int /*<<< orphan*/ ,struct kernel_ipmi_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int) ; 
 int ipmi_validate_addr (struct ipmi_addr*,int) ; 
 int /*<<< orphan*/  kfree (struct ipmi_addr*) ; 
 struct ipmi_addr* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_send_req(struct ipmi_user *user,
			   struct ipmi_req *req,
			   int             retries,
			   unsigned int    retry_time_ms)
{
	int              rv;
	struct ipmi_addr addr;
	struct kernel_ipmi_msg msg;

	if (req->addr_len > sizeof(struct ipmi_addr))
		return -EINVAL;

	if (copy_from_user(&addr, req->addr, req->addr_len))
		return -EFAULT;

	msg.netfn = req->msg.netfn;
	msg.cmd = req->msg.cmd;
	msg.data_len = req->msg.data_len;
	msg.data = kmalloc(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	if (!msg.data)
		return -ENOMEM;

	/* From here out we cannot return, we must jump to "out" for
	   error exits to free msgdata. */

	rv = ipmi_validate_addr(&addr, req->addr_len);
	if (rv)
		goto out;

	if (req->msg.data != NULL) {
		if (req->msg.data_len > IPMI_MAX_MSG_LENGTH) {
			rv = -EMSGSIZE;
			goto out;
		}

		if (copy_from_user(msg.data,
				   req->msg.data,
				   req->msg.data_len)) {
			rv = -EFAULT;
			goto out;
		}
	} else {
		msg.data_len = 0;
	}

	rv = ipmi_request_settime(user,
				  &addr,
				  req->msgid,
				  &msg,
				  NULL,
				  0,
				  retries,
				  retry_time_ms);
 out:
	kfree(msg.data);
	return rv;
}
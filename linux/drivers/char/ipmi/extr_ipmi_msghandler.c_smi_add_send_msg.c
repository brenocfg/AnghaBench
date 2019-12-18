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
struct ipmi_smi_msg {int /*<<< orphan*/  link; } ;
struct ipmi_smi {struct ipmi_smi_msg* curr_msg; int /*<<< orphan*/  xmit_msgs; int /*<<< orphan*/  hp_xmit_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipmi_smi_msg *smi_add_send_msg(struct ipmi_smi *intf,
					     struct ipmi_smi_msg *smi_msg,
					     int priority)
{
	if (intf->curr_msg) {
		if (priority > 0)
			list_add_tail(&smi_msg->link, &intf->hp_xmit_msgs);
		else
			list_add_tail(&smi_msg->link, &intf->xmit_msgs);
		smi_msg = NULL;
	} else {
		intf->curr_msg = smi_msg;
	}

	return smi_msg;
}
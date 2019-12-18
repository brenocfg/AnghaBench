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
struct ipmi_smi_msg {int dummy; } ;
struct ipmi_smi_handlers {int /*<<< orphan*/  (* sender ) (int /*<<< orphan*/ ,struct ipmi_smi_msg*) ;} ;
struct ipmi_smi {int run_to_completion; int /*<<< orphan*/  send_info; int /*<<< orphan*/  xmit_msgs_lock; } ;

/* Variables and functions */
 struct ipmi_smi_msg* smi_add_send_msg (struct ipmi_smi*,struct ipmi_smi_msg*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ipmi_smi_msg*) ; 

__attribute__((used)) static void smi_send(struct ipmi_smi *intf,
		     const struct ipmi_smi_handlers *handlers,
		     struct ipmi_smi_msg *smi_msg, int priority)
{
	int run_to_completion = intf->run_to_completion;
	unsigned long flags = 0;

	if (!run_to_completion)
		spin_lock_irqsave(&intf->xmit_msgs_lock, flags);
	smi_msg = smi_add_send_msg(intf, smi_msg, priority);

	if (!run_to_completion)
		spin_unlock_irqrestore(&intf->xmit_msgs_lock, flags);

	if (smi_msg)
		handlers->sender(intf->send_info, smi_msg);
}
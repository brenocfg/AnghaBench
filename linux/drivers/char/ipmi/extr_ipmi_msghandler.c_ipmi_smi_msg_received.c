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
struct ipmi_smi {int run_to_completion; int /*<<< orphan*/  recv_tasklet; int /*<<< orphan*/  xmit_msgs_lock; struct ipmi_smi_msg* curr_msg; int /*<<< orphan*/  waiting_rcv_msgs_lock; int /*<<< orphan*/  waiting_rcv_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smi_recv_tasklet (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void ipmi_smi_msg_received(struct ipmi_smi *intf,
			   struct ipmi_smi_msg *msg)
{
	unsigned long flags = 0; /* keep us warning-free. */
	int run_to_completion = intf->run_to_completion;

	/*
	 * To preserve message order, we keep a queue and deliver from
	 * a tasklet.
	 */
	if (!run_to_completion)
		spin_lock_irqsave(&intf->waiting_rcv_msgs_lock, flags);
	list_add_tail(&msg->link, &intf->waiting_rcv_msgs);
	if (!run_to_completion)
		spin_unlock_irqrestore(&intf->waiting_rcv_msgs_lock,
				       flags);

	if (!run_to_completion)
		spin_lock_irqsave(&intf->xmit_msgs_lock, flags);
	/*
	 * We can get an asynchronous event or receive message in addition
	 * to commands we send.
	 */
	if (msg == intf->curr_msg)
		intf->curr_msg = NULL;
	if (!run_to_completion)
		spin_unlock_irqrestore(&intf->xmit_msgs_lock, flags);

	if (run_to_completion)
		smi_recv_tasklet((unsigned long) intf);
	else
		tasklet_schedule(&intf->recv_tasklet);
}
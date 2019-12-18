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
typedef  int u32 ;
struct ccp_device {unsigned int cmd_q_count; struct ccp_cmd_queue* cmd_q; } ;
struct ccp_cmd_queue {int int_status; int int_rcvd; int /*<<< orphan*/  int_queue; int /*<<< orphan*/  reg_interrupt_status; void* q_status; scalar_t__ cmd_error; int /*<<< orphan*/  reg_int_status; void* q_int_status; int /*<<< orphan*/  reg_status; } ;

/* Variables and functions */
 scalar_t__ CMD_Q_ERROR (void*) ; 
 int INT_ERROR ; 
 int /*<<< orphan*/  ccp5_enable_queue_interrupts (struct ccp_device*) ; 
 void* ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp5_irq_bh(unsigned long data)
{
	struct ccp_device *ccp = (struct ccp_device *)data;
	u32 status;
	unsigned int i;

	for (i = 0; i < ccp->cmd_q_count; i++) {
		struct ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		status = ioread32(cmd_q->reg_interrupt_status);

		if (status) {
			cmd_q->int_status = status;
			cmd_q->q_status = ioread32(cmd_q->reg_status);
			cmd_q->q_int_status = ioread32(cmd_q->reg_int_status);

			/* On error, only save the first error value */
			if ((status & INT_ERROR) && !cmd_q->cmd_error)
				cmd_q->cmd_error = CMD_Q_ERROR(cmd_q->q_status);

			cmd_q->int_rcvd = 1;

			/* Acknowledge the interrupt and wake the kthread */
			iowrite32(status, cmd_q->reg_interrupt_status);
			wake_up_interruptible(&cmd_q->int_queue);
		}
	}
	ccp5_enable_queue_interrupts(ccp);
}
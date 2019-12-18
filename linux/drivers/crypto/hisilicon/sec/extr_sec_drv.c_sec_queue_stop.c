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
struct sec_queue {scalar_t__ regs; int /*<<< orphan*/  task_irq; } ;

/* Variables and functions */
 scalar_t__ SEC_QUEUE_ENB_REG ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_queue_irq_disable (struct sec_queue*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sec_queue_stop(struct sec_queue *queue)
{
	disable_irq(queue->task_irq);
	sec_queue_irq_disable(queue);
	writel_relaxed(0x0, queue->regs + SEC_QUEUE_ENB_REG);
}
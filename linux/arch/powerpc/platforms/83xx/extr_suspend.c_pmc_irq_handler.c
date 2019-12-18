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
typedef  scalar_t__ u32 ;
typedef  int irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 scalar_t__ in_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ mpc83xx_change_state () ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* pmc_regs ; 

__attribute__((used)) static irqreturn_t pmc_irq_handler(int irq, void *dev_id)
{
	u32 event = in_be32(&pmc_regs->event);
	int ret = IRQ_NONE;

	if (mpc83xx_change_state())
		ret = IRQ_HANDLED;

	if (event) {
		out_be32(&pmc_regs->event, event);
		ret = IRQ_HANDLED;
	}

	return ret;
}
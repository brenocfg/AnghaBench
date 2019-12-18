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
struct mfptimerbase {int mfptimer_irq; unsigned char int_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 

__attribute__((used)) static irqreturn_t mfp_timer_d_handler(int irq, void *dev_id)
{
	struct mfptimerbase *base = dev_id;
	int mach_irq;
	unsigned char ints;

	mach_irq = base->mfptimer_irq;
	ints = base->int_mask;
	for (; ints; mach_irq++, ints >>= 1) {
		if (ints & 1)
			generic_handle_irq(mach_irq);
	}
	return IRQ_HANDLED;
}
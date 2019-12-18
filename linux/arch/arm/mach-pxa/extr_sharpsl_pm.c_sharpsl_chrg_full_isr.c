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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  chrg_full_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SHARPSL_SUSPENDED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 TYPE_1__ sharpsl_pm ; 

__attribute__((used)) static irqreturn_t sharpsl_chrg_full_isr(int irq, void *dev_id)
{
	if (sharpsl_pm.flags & SHARPSL_SUSPENDED)
		return IRQ_HANDLED;

	/* delay until after any ac interrupt */
	mod_timer(&sharpsl_pm.chrg_full_timer, jiffies + msecs_to_jiffies(500));

	return IRQ_HANDLED;
}
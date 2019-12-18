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
struct TYPE_2__ {int /*<<< orphan*/  ac_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 TYPE_1__ sharpsl_pm ; 

__attribute__((used)) static irqreturn_t sharpsl_ac_isr(int irq, void *dev_id)
{
	/* Delay the event slightly to debounce */
	/* Must be a smaller delay than the chrg_full_isr below */
	mod_timer(&sharpsl_pm.ac_timer, jiffies + msecs_to_jiffies(250));

	return IRQ_HANDLED;
}
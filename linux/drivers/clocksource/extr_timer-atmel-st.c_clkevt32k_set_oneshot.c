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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ST_ALMS ; 
 int /*<<< orphan*/  AT91_ST_IER ; 
 int /*<<< orphan*/  AT91_ST_RTAR ; 
 int /*<<< orphan*/  clkdev32k_disable_and_flush_irq () ; 
 int /*<<< orphan*/  irqmask ; 
 int /*<<< orphan*/  last_crtr ; 
 int /*<<< orphan*/  regmap_st ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clkevt32k_set_oneshot(struct clock_event_device *dev)
{
	clkdev32k_disable_and_flush_irq();

	/*
	 * ALM for oneshot irqs, set by next_event()
	 * before 32 seconds have passed.
	 */
	irqmask = AT91_ST_ALMS;
	regmap_write(regmap_st, AT91_ST_RTAR, last_crtr);
	regmap_write(regmap_st, AT91_ST_IER, irqmask);
	return 0;
}
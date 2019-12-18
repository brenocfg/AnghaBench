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
typedef  int u16 ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MCFPIT_PCSR ; 
 int MCFPIT_PCSR_PIF ; 
 scalar_t__ PIT_CYCLES_PER_JIFFY ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 struct clock_event_device cf_pit_clockevent ; 
 int /*<<< orphan*/  pit_cnt ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t pit_tick(int irq, void *dummy)
{
	struct clock_event_device *evt = &cf_pit_clockevent;
	u16 pcsr;

	/* Reset the ColdFire timer */
	pcsr = __raw_readw(TA(MCFPIT_PCSR));
	__raw_writew(pcsr | MCFPIT_PCSR_PIF, TA(MCFPIT_PCSR));

	pit_cnt += PIT_CYCLES_PER_JIFFY;
	evt->event_handler(evt);
	return IRQ_HANDLED;
}
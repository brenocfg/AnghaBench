#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_4__ {int max_delta_ticks; int min_delta_ticks; void* min_delta_ns; void* max_delta_ns; int /*<<< orphan*/  mult; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ ; 
 int /*<<< orphan*/  MCF_IRQ_PIT1 ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 TYPE_1__ cf_pit_clockevent ; 
 void* clockevent_delta2ns (int,TYPE_1__*) ; 
 int /*<<< orphan*/  clockevents_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  clocksource_register_hz (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_sc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pit_clk ; 
 int /*<<< orphan*/  pit_irq ; 
 int /*<<< orphan*/  setup_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void hw_timer_init(irq_handler_t handler)
{
	cf_pit_clockevent.cpumask = cpumask_of(smp_processor_id());
	cf_pit_clockevent.mult = div_sc(FREQ, NSEC_PER_SEC, 32);
	cf_pit_clockevent.max_delta_ns =
		clockevent_delta2ns(0xFFFF, &cf_pit_clockevent);
	cf_pit_clockevent.max_delta_ticks = 0xFFFF;
	cf_pit_clockevent.min_delta_ns =
		clockevent_delta2ns(0x3f, &cf_pit_clockevent);
	cf_pit_clockevent.min_delta_ticks = 0x3f;
	clockevents_register_device(&cf_pit_clockevent);

	setup_irq(MCF_IRQ_PIT1, &pit_irq);

	clocksource_register_hz(&pit_clk, FREQ);
}
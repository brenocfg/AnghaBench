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
struct clock_event_device {char* name; int features; int rating; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_frequency ; 
 int /*<<< orphan*/  gic_next_event ; 
 int /*<<< orphan*/  gic_timer_irq ; 

__attribute__((used)) static void gic_clockevent_cpu_init(unsigned int cpu,
				    struct clock_event_device *cd)
{
	cd->name		= "MIPS GIC";
	cd->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_C3STOP;

	cd->rating		= 350;
	cd->irq			= gic_timer_irq;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= gic_next_event;

	clockevents_config_and_register(cd, gic_frequency, 0x300, 0x7fffffff);

	enable_percpu_irq(gic_timer_irq, IRQ_TYPE_NONE);
}
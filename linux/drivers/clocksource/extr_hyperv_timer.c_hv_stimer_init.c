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
struct clock_event_device {char* name; int rating; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  set_state_oneshot; int /*<<< orphan*/  set_state_shutdown; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  features; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  HV_CLOCK_HZ ; 
 int /*<<< orphan*/  HV_MAX_MAX_DELTA_TICKS ; 
 int /*<<< orphan*/  HV_MIN_DELTA_TICKS ; 
 int HV_MSR_SYNTIMER_AVAILABLE ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  hv_ce_set_next_event ; 
 int /*<<< orphan*/  hv_ce_set_oneshot ; 
 int /*<<< orphan*/  hv_ce_shutdown ; 
 int /*<<< orphan*/  hv_clock_event ; 
 TYPE_1__ ms_hyperv ; 
 struct clock_event_device* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

void hv_stimer_init(unsigned int cpu)
{
	struct clock_event_device *ce;

	/*
	 * Synthetic timers are always available except on old versions of
	 * Hyper-V on x86.  In that case, just return as Linux will use a
	 * clocksource based on emulated PIT or LAPIC timer hardware.
	 */
	if (!(ms_hyperv.features & HV_MSR_SYNTIMER_AVAILABLE))
		return;

	ce = per_cpu_ptr(hv_clock_event, cpu);
	ce->name = "Hyper-V clockevent";
	ce->features = CLOCK_EVT_FEAT_ONESHOT;
	ce->cpumask = cpumask_of(cpu);
	ce->rating = 1000;
	ce->set_state_shutdown = hv_ce_shutdown;
	ce->set_state_oneshot = hv_ce_set_oneshot;
	ce->set_next_event = hv_ce_set_next_event;

	clockevents_config_and_register(ce,
					HV_CLOCK_HZ,
					HV_MIN_DELTA_TICKS,
					HV_MAX_MAX_DELTA_TICKS);
}
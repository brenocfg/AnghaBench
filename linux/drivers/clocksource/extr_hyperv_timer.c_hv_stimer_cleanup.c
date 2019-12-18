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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int HV_MSR_SYNTIMER_AVAILABLE ; 
 int /*<<< orphan*/  hv_ce_shutdown (struct clock_event_device*) ; 
 int /*<<< orphan*/  hv_clock_event ; 
 TYPE_1__ ms_hyperv ; 
 struct clock_event_device* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

void hv_stimer_cleanup(unsigned int cpu)
{
	struct clock_event_device *ce;

	/* Turn off clockevent device */
	if (ms_hyperv.features & HV_MSR_SYNTIMER_AVAILABLE) {
		ce = per_cpu_ptr(hv_clock_event, cpu);
		hv_ce_shutdown(ce);
	}
}
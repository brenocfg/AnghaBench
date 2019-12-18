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
struct clock_event_device {char* name; int features; int rating; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_DUMMY ; 
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int CLOCK_EVT_FEAT_PERIODIC ; 
 int /*<<< orphan*/  clockevents_register_device (struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  dummy_timer_evt ; 
 struct clock_event_device* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int dummy_timer_starting_cpu(unsigned int cpu)
{
	struct clock_event_device *evt = per_cpu_ptr(&dummy_timer_evt, cpu);

	evt->name	= "dummy_timer";
	evt->features	= CLOCK_EVT_FEAT_PERIODIC |
			  CLOCK_EVT_FEAT_ONESHOT |
			  CLOCK_EVT_FEAT_DUMMY;
	evt->rating	= 100;
	evt->cpumask	= cpumask_of(cpu);

	clockevents_register_device(evt);
	return 0;
}
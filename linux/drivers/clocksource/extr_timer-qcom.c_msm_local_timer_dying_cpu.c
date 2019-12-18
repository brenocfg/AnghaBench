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
struct clock_event_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  (* set_state_shutdown ) (struct clock_event_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_evt ; 
 struct clock_event_device* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static int msm_local_timer_dying_cpu(unsigned int cpu)
{
	struct clock_event_device *evt = per_cpu_ptr(msm_evt, cpu);

	evt->set_state_shutdown(evt);
	disable_percpu_irq(evt->irq);
	return 0;
}
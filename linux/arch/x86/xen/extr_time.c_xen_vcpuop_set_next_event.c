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
struct vcpu_set_singleshot_timer {scalar_t__ flags; int /*<<< orphan*/  timeout_abs_ns; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vcpu_set_singleshot_timer*) ; 
 int /*<<< orphan*/  VCPUOP_set_singleshot_timer ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clockevent_state_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  get_abs_timeout (unsigned long) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  xen_vcpu_nr (int) ; 

__attribute__((used)) static int xen_vcpuop_set_next_event(unsigned long delta,
				     struct clock_event_device *evt)
{
	int cpu = smp_processor_id();
	struct vcpu_set_singleshot_timer single;
	int ret;

	WARN_ON(!clockevent_state_oneshot(evt));

	single.timeout_abs_ns = get_abs_timeout(delta);
	/* Get an event anyway, even if the timeout is already expired */
	single.flags = 0;

	ret = HYPERVISOR_vcpu_op(VCPUOP_set_singleshot_timer, xen_vcpu_nr(cpu),
				 &single);
	BUG_ON(ret != 0);

	return ret;
}
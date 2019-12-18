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
typedef  int /*<<< orphan*/  uint64_t ;
struct vcpu_set_singleshot_timer {scalar_t__ flags; int /*<<< orphan*/  timeout_abs_ns; } ;

/* Variables and functions */
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int,struct vcpu_set_singleshot_timer*) ; 
 int /*<<< orphan*/  VCPUOP_set_singleshot_timer ; 

__attribute__((used)) static int
xentimer_vcpu_start_timer(int vcpu, uint64_t next_time)
{
	struct vcpu_set_singleshot_timer single;

	single.timeout_abs_ns = next_time;
	/* Get an event anyway, even if the timeout is already expired */
	single.flags          = 0;
	return (HYPERVISOR_vcpu_op(VCPUOP_set_singleshot_timer, vcpu, &single));
}
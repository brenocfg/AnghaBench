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
typedef  scalar_t__ dtrace_id_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_2__ {int t_dtrace_inprobe; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 scalar_t__ dtrace_probeid_error ; 

__attribute__((used)) static dtrace_icookie_t
dtrace_probe_enter(dtrace_id_t id)
{
	dtrace_icookie_t cookie;

	cookie = dtrace_interrupt_disable();

	/*
	 * Unless this is an ERROR probe, we are not allowed to recurse in
	 * dtrace_probe(). Recursing into DTrace probe usually means that a
	 * function is instrumented that should not have been instrumented or
	 * that the ordering guarantee of the records will be violated,
	 * resulting in unexpected output. If there is an exception to this
	 * assertion, a new case should be added.
	 */
	ASSERT(curthread->t_dtrace_inprobe == 0 ||
	    id == dtrace_probeid_error);
	curthread->t_dtrace_inprobe = 1;

	return (cookie);
}
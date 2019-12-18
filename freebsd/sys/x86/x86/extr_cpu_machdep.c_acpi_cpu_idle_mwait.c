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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int idle_state; } ;

/* Variables and functions */
 int IA32_SPEC_CTRL_IBRS ; 
 int IA32_SPEC_CTRL_SSBD ; 
 int IA32_SPEC_CTRL_STIBP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MSR_IA32_SPEC_CTRL ; 
 int /*<<< orphan*/  MWAIT_INTRBREAK ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_1__* PCPU_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_MWAIT ; 
 scalar_t__ STATE_RUNNING ; 
 scalar_t__ STATE_SLEEPING ; 
 scalar_t__ atomic_load_int (int*) ; 
 int /*<<< orphan*/  atomic_store_int (int*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_monitor (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hw_ssb_active ; 
 int /*<<< orphan*/  ibpb_set ; 
 int /*<<< orphan*/  monitorbuf ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

void
acpi_cpu_idle_mwait(uint32_t mwait_hint)
{
	int *state;
	uint64_t v;

	/*
	 * A comment in Linux patch claims that 'CPUs run faster with
	 * speculation protection disabled. All CPU threads in a core
	 * must disable speculation protection for it to be
	 * disabled. Disable it while we are idle so the other
	 * hyperthread can run fast.'
	 *
	 * XXXKIB.  Software coordination mode should be supported,
	 * but all Intel CPUs provide hardware coordination.
	 */

	state = &PCPU_PTR(monitorbuf)->idle_state;
	KASSERT(atomic_load_int(state) == STATE_SLEEPING,
	    ("cpu_mwait_cx: wrong monitorbuf state"));
	atomic_store_int(state, STATE_MWAIT);
	if (PCPU_GET(ibpb_set) || hw_ssb_active) {
		v = rdmsr(MSR_IA32_SPEC_CTRL);
		wrmsr(MSR_IA32_SPEC_CTRL, v & ~(IA32_SPEC_CTRL_IBRS |
		    IA32_SPEC_CTRL_STIBP | IA32_SPEC_CTRL_SSBD));
	} else {
		v = 0;
	}
	cpu_monitor(state, 0, 0);
	if (atomic_load_int(state) == STATE_MWAIT)
		cpu_mwait(MWAIT_INTRBREAK, mwait_hint);

	/*
	 * SSB cannot be disabled while we sleep, or rather, if it was
	 * disabled, the sysctl thread will bind to our cpu to tweak
	 * MSR.
	 */
	if (v != 0)
		wrmsr(MSR_IA32_SPEC_CTRL, v);

	/*
	 * We should exit on any event that interrupts mwait, because
	 * that event might be a wanted interrupt.
	 */
	atomic_store_int(state, STATE_RUNNING);
}
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
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_2__ {int idle_state; } ;

/* Variables and functions */
 TYPE_1__* PCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  STATE_SLEEPING ; 
 int /*<<< orphan*/  acpi_cpu_c1 () ; 
 int /*<<< orphan*/  atomic_store_int (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_intr () ; 
 int /*<<< orphan*/  enable_intr () ; 
 int /*<<< orphan*/  monitorbuf ; 
 scalar_t__ sched_runnable () ; 

__attribute__((used)) static void
cpu_idle_hlt(sbintime_t sbt)
{
	int *state;

	state = &PCPU_PTR(monitorbuf)->idle_state;
	atomic_store_int(state, STATE_SLEEPING);

	/*
	 * Since we may be in a critical section from cpu_idle(), if
	 * an interrupt fires during that critical section we may have
	 * a pending preemption.  If the CPU halts, then that thread
	 * may not execute until a later interrupt awakens the CPU.
	 * To handle this race, check for a runnable thread after
	 * disabling interrupts and immediately return if one is
	 * found.  Also, we must absolutely guarentee that hlt is
	 * the next instruction after sti.  This ensures that any
	 * interrupt that fires after the call to disable_intr() will
	 * immediately awaken the CPU from hlt.  Finally, please note
	 * that on x86 this works fine because of interrupts enabled only
	 * after the instruction following sti takes place, while IF is set
	 * to 1 immediately, allowing hlt instruction to acknowledge the
	 * interrupt.
	 */
	disable_intr();
	if (sched_runnable())
		enable_intr();
	else
		acpi_cpu_c1();
	atomic_store_int(state, STATE_RUNNING);
}
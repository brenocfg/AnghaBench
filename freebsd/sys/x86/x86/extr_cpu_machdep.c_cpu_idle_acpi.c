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
 int /*<<< orphan*/  cpu_idle_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_intr () ; 
 int /*<<< orphan*/  enable_intr () ; 
 int /*<<< orphan*/  monitorbuf ; 
 scalar_t__ sched_runnable () ; 

__attribute__((used)) static void
cpu_idle_acpi(sbintime_t sbt)
{
	int *state;

	state = &PCPU_PTR(monitorbuf)->idle_state;
	atomic_store_int(state, STATE_SLEEPING);

	/* See comments in cpu_idle_hlt(). */
	disable_intr();
	if (sched_runnable())
		enable_intr();
	else if (cpu_idle_hook)
		cpu_idle_hook(sbt);
	else
		acpi_cpu_c1();
	atomic_store_int(state, STATE_RUNNING);
}
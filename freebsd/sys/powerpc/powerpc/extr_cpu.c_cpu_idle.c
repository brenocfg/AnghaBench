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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {scalar_t__ md_saved_msr; } ;
struct thread {TYPE_1__ td_md; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 int PSL_EE ; 
 int /*<<< orphan*/  cpu_activeclock () ; 
 int /*<<< orphan*/  cpu_idle_hook (int) ; 
 int cpu_idleclock () ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  curcpu ; 
 struct thread* curthread ; 
 int mfmsr () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

void
cpu_idle(int busy)
{
	sbintime_t sbt = -1;

#ifdef INVARIANTS
	if ((mfmsr() & PSL_EE) != PSL_EE) {
		struct thread *td = curthread;
		printf("td msr %#lx\n", (u_long)td->td_md.md_saved_msr);
		panic("ints disabled in idleproc!");
	}
#endif

	CTR2(KTR_SPARE2, "cpu_idle(%d) at %d",
	    busy, curcpu);

	if (cpu_idle_hook != NULL) {
		if (!busy) {
			critical_enter();
			sbt = cpu_idleclock();
		}
		cpu_idle_hook(sbt);
		if (!busy) {
			cpu_activeclock();
			critical_exit();
		}
	}

	CTR2(KTR_SPARE2, "cpu_idle(%d) at %d done",
	    busy, curcpu);
}
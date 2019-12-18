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

/* Variables and functions */
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  runq ; 
 int runq_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * runq_pcpu ; 

int
sched_runnable(void)
{
#ifdef SMP
	return runq_check(&runq) + runq_check(&runq_pcpu[PCPU_GET(cpuid)]);
#else
	return runq_check(&runq);
#endif
}
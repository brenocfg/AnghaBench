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
struct pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmuint_rwlock ; 
 int /*<<< orphan*/  resume_local_counters () ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mipspmu_enable(struct pmu *pmu)
{
#ifdef CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	write_unlock(&pmuint_rwlock);
#endif
	resume_local_counters();
}
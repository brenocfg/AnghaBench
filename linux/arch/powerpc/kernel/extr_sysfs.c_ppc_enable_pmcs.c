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
struct TYPE_2__ {int /*<<< orphan*/  (* enable_pmcs ) () ;} ;

/* Variables and functions */
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmcs_enabled ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  ppc_set_pmu_inuse (int) ; 
 int /*<<< orphan*/  stub1 () ; 

void ppc_enable_pmcs(void)
{
	ppc_set_pmu_inuse(1);

	/* Only need to enable them once */
	if (__this_cpu_read(pmcs_enabled))
		return;

	__this_cpu_write(pmcs_enabled, 1);

	if (ppc_md.enable_pmcs)
		ppc_md.enable_pmcs();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct pmc_hw {struct pmc* phw_pmc; } ;
struct TYPE_4__ {size_t pm_mips_evsel; } ;
struct pmc {TYPE_1__ pm_md; } ;
typedef  int /*<<< orphan*/  pmc_value_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_func ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * stop_values; struct pmc_hw* pc_beripmcs; } ;

/* Variables and functions */
 TYPE_3__* beri_event_codes ; 
 TYPE_2__** beri_pcpu ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int
beri_stop_pmc(int cpu, int ri)
{
	uint32_t config;
        struct pmc *pm;
        struct pmc_hw *phw;
	pmc_value_t v;

	phw = &beri_pcpu[cpu]->pc_beripmcs[ri];
	pm = phw->phw_pmc;
	config = pm->pm_md.pm_mips_evsel;

	v = beri_event_codes[config].get_func();
	beri_pcpu[cpu]->stop_values[config] = v;

	return (0);
}
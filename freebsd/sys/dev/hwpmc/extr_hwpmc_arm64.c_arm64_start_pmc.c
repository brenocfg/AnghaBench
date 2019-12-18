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
typedef  int uint32_t ;
struct pmc_hw {struct pmc* phw_pmc; } ;
struct TYPE_4__ {int pm_arm64_evsel; } ;
struct TYPE_5__ {TYPE_1__ pm_arm64; } ;
struct pmc {TYPE_2__ pm_md; } ;
struct TYPE_6__ {struct pmc_hw* pc_arm64pmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_SPECIALREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arm64_counter_enable (int) ; 
 int /*<<< orphan*/  arm64_interrupt_enable (int) ; 
 TYPE_3__** arm64_pcpu ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  pmselr_el0 ; 
 int /*<<< orphan*/  pmxevtyper_el0 ; 

__attribute__((used)) static int
arm64_start_pmc(int cpu, int ri)
{
	struct pmc_hw *phw;
	uint32_t config;
	struct pmc *pm;

	phw    = &arm64_pcpu[cpu]->pc_arm64pmcs[ri];
	pm     = phw->phw_pmc;
	config = pm->pm_md.pm_arm64.pm_arm64_evsel;

	/*
	 * Configure the event selection.
	 */
	WRITE_SPECIALREG(pmselr_el0, ri);
	WRITE_SPECIALREG(pmxevtyper_el0, config);

	isb();

	/*
	 * Enable the PMC.
	 */
	arm64_interrupt_enable(ri);
	arm64_counter_enable(ri);

	return 0;
}
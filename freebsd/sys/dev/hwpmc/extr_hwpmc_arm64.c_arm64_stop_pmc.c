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
struct pmc_hw {struct pmc* phw_pmc; } ;
struct pmc {int dummy; } ;
struct TYPE_2__ {struct pmc_hw* pc_arm64pmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm64_counter_disable (int) ; 
 int /*<<< orphan*/  arm64_interrupt_disable (int) ; 
 TYPE_1__** arm64_pcpu ; 

__attribute__((used)) static int
arm64_stop_pmc(int cpu, int ri)
{
	struct pmc_hw *phw;
	struct pmc *pm;

	phw    = &arm64_pcpu[cpu]->pc_arm64pmcs[ri];
	pm     = phw->phw_pmc;

	/*
	 * Disable the PMCs.
	 */
	arm64_counter_disable(ri);
	arm64_interrupt_disable(ri);

	return 0;
}
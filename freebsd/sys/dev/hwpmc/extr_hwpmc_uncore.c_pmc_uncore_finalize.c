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
struct pmc_mdep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INI ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  M_PMC ; 
 int /*<<< orphan*/  PMCDBG0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uncore_pcpu ; 

void
pmc_uncore_finalize(struct pmc_mdep *md)
{
	PMCDBG0(MDP,INI,1, "uncore-finalize");

	free(uncore_pcpu, M_PMC);
	uncore_pcpu = NULL;
}
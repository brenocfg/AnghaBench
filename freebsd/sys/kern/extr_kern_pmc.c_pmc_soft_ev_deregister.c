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
struct TYPE_2__ {scalar_t__ pm_ev_code; } ;
struct pmc_soft {TYPE_1__ ps_ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PMC_EV_SOFT_FIRST ; 
 int PMC_EV_SOFT_LAST ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ pmc_softevents ; 
 int /*<<< orphan*/ ** pmc_softs ; 
 int /*<<< orphan*/  pmc_softs_mtx ; 

void
pmc_soft_ev_deregister(struct pmc_soft *ps)
{

	KASSERT(ps != NULL, ("pmc_soft_deregister: called with NULL"));

	mtx_lock_spin(&pmc_softs_mtx);

	if (ps->ps_ev.pm_ev_code != 0 &&
	    (ps->ps_ev.pm_ev_code - PMC_EV_SOFT_FIRST) < pmc_softevents) {
		KASSERT((int)ps->ps_ev.pm_ev_code >= PMC_EV_SOFT_FIRST &&
		    (int)ps->ps_ev.pm_ev_code <= PMC_EV_SOFT_LAST,
		    ("pmc_soft_deregister: invalid event value"));
		pmc_softs[ps->ps_ev.pm_ev_code - PMC_EV_SOFT_FIRST] = NULL;
	}

	mtx_unlock_spin(&pmc_softs_mtx);
}
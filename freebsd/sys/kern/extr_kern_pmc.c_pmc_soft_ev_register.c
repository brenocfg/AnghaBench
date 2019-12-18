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
struct TYPE_2__ {int pm_ev_code; int /*<<< orphan*/  pm_ev_name; } ;
struct pmc_soft {TYPE_1__ ps_ev; scalar_t__ ps_running; } ;

/* Variables and functions */
 int PMC_EV_SOFT_FIRST ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_soft_namecleanup (int /*<<< orphan*/ ) ; 
 int pmc_softevents ; 
 struct pmc_soft** pmc_softs ; 
 int pmc_softs_count ; 
 int /*<<< orphan*/  pmc_softs_mtx ; 
 int /*<<< orphan*/  printf (char*) ; 

void
pmc_soft_ev_register(struct pmc_soft *ps)
{
	static int warned = 0;
	int n;

	ps->ps_running  = 0;
	ps->ps_ev.pm_ev_code = 0; /* invalid */
	pmc_soft_namecleanup(ps->ps_ev.pm_ev_name);

	mtx_lock_spin(&pmc_softs_mtx);

	if (pmc_softs_count >= pmc_softevents) {
		/*
		 * XXX Reusing events can enter a race condition where
		 * new allocated event will be used as an old one.
		 */
		for (n = 0; n < pmc_softevents; n++)
			if (pmc_softs[n] == NULL)
				break;
		if (n == pmc_softevents) {
			mtx_unlock_spin(&pmc_softs_mtx);
			if (!warned) {
				printf("hwpmc: too many soft events, "
				    "increase kern.hwpmc.softevents tunable\n");
				warned = 1;
			}
			return;
		}

		ps->ps_ev.pm_ev_code = PMC_EV_SOFT_FIRST + n;
		pmc_softs[n] = ps;
	} else {
		ps->ps_ev.pm_ev_code = PMC_EV_SOFT_FIRST + pmc_softs_count;
		pmc_softs[pmc_softs_count++] = ps;
	}

	mtx_unlock_spin(&pmc_softs_mtx);
}
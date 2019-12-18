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
struct pmc_soft {int dummy; } ;
typedef  enum pmc_event { ____Placeholder_pmc_event } pmc_event ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PMC_EV_SOFT_FIRST ; 
 int PMC_EV_SOFT_LAST ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int pmc_softevents ; 
 struct pmc_soft** pmc_softs ; 
 int /*<<< orphan*/  pmc_softs_mtx ; 

struct pmc_soft *
pmc_soft_ev_acquire(enum pmc_event ev)
{
	struct pmc_soft *ps;

	if (ev == 0 || (ev - PMC_EV_SOFT_FIRST) >= pmc_softevents)
		return NULL;

	KASSERT((int)ev >= PMC_EV_SOFT_FIRST &&
	    (int)ev <= PMC_EV_SOFT_LAST,
	    ("event out of range"));

	mtx_lock_spin(&pmc_softs_mtx);

	ps = pmc_softs[ev - PMC_EV_SOFT_FIRST];
	if (ps == NULL)
		mtx_unlock_spin(&pmc_softs_mtx);

	return ps;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_5__ {unsigned int swPortalId; uintptr_t irq; int /*<<< orphan*/  h_Bm; void* ciBaseAddress; void* ceBaseAddress; } ;
typedef  TYPE_2__ t_BmPortalParam ;
struct dpaa_portals_softc {TYPE_1__* sc_dp; int /*<<< orphan*/ * sc_rres; } ;
struct bman_softc {int /*<<< orphan*/  sc_bh; } ;
struct TYPE_4__ {int /*<<< orphan*/  dp_ph; scalar_t__ dp_ires; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BM_PORTAL_Config (TYPE_2__*) ; 
 int /*<<< orphan*/  BM_PORTAL_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ BM_PORTAL_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ E_OK ; 
 unsigned int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_VOL ; 
 scalar_t__ atomic_cmpset_acq_ptr (uintptr_t*,int /*<<< orphan*/ ,int) ; 
 uintptr_t atomic_load_acq_ptr (uintptr_t*) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t*,uintptr_t) ; 
 struct dpaa_portals_softc* bp_sc ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dpaa_portal_map_registers (struct dpaa_portals_softc*) ; 
 int /*<<< orphan*/  mi_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

t_Handle
bman_portal_setup(struct bman_softc *bsc)
{
	struct dpaa_portals_softc *sc;
	t_BmPortalParam bpp;
	t_Handle portal;
	unsigned int cpu;
	uintptr_t p;

	/* Return NULL if we're not ready or while detach */
	if (bp_sc == NULL)
		return (NULL);

	sc = bp_sc;

	sched_pin();
	portal = NULL;
	cpu = PCPU_GET(cpuid);

	/* Check if portal is ready */
	while (atomic_cmpset_acq_ptr((uintptr_t *)&sc->sc_dp[cpu].dp_ph,
	    0, -1) == 0) {
		p = atomic_load_acq_ptr((uintptr_t *)&sc->sc_dp[cpu].dp_ph);

		/* Return if portal is already initialized */
		if (p != 0 && p != -1) {
			sched_unpin();
			return ((t_Handle)p);
		}

		/* Not inititialized and "owned" by another thread */
		thread_lock(curthread);
		mi_switch(SW_VOL, NULL);
		thread_unlock(curthread);
	}

	/* Map portal registers */
	dpaa_portal_map_registers(sc);

	/* Configure and initialize portal */
	bpp.ceBaseAddress = rman_get_bushandle(sc->sc_rres[0]);
	bpp.ciBaseAddress = rman_get_bushandle(sc->sc_rres[1]);
	bpp.h_Bm = bsc->sc_bh;
	bpp.swPortalId = cpu;
	bpp.irq = (uintptr_t)sc->sc_dp[cpu].dp_ires;

	portal = BM_PORTAL_Config(&bpp);
	if (portal == NULL)
		goto err;

	if (BM_PORTAL_Init(portal) != E_OK)
		goto err;

	atomic_store_rel_ptr((uintptr_t *)&sc->sc_dp[cpu].dp_ph, (uintptr_t)portal);
	
	sched_unpin();

	return (portal);

err:
	if (portal != NULL)
		BM_PORTAL_Free(portal);

	atomic_store_rel_ptr((uintptr_t *)&sc->sc_dp[cpu].dp_ph, 0);
	sched_unpin();

	return (NULL);
}
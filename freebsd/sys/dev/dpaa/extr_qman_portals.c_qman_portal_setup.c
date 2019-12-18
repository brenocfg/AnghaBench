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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {unsigned int swPortalId; uintptr_t irq; struct qman_softc* h_App; int /*<<< orphan*/  f_RejectedFrame; int /*<<< orphan*/  f_DfltFrame; scalar_t__ fdLiodnOffset; int /*<<< orphan*/  h_Qm; void* ciBaseAddress; void* ceBaseAddress; } ;
typedef  TYPE_2__ t_QmPortalParam ;
typedef  int /*<<< orphan*/ * t_Handle ;
struct qman_softc {int /*<<< orphan*/  sc_qh; } ;
struct dpaa_portals_softc {TYPE_1__* sc_dp; int /*<<< orphan*/ * sc_rres; } ;
struct TYPE_4__ {int /*<<< orphan*/  dp_ph; scalar_t__ dp_ires; } ;

/* Variables and functions */
 scalar_t__ E_OK ; 
 unsigned int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QMAN_COMMON_POOL_CHANNEL ; 
 scalar_t__ QM_PORTAL_AddPoolChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * QM_PORTAL_Config (TYPE_2__*) ; 
 int /*<<< orphan*/  QM_PORTAL_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ QM_PORTAL_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SW_VOL ; 
 scalar_t__ atomic_cmpset_acq_ptr (uintptr_t*,int /*<<< orphan*/ ,int) ; 
 uintptr_t atomic_load_acq_ptr (uintptr_t*) ; 
 int /*<<< orphan*/  atomic_store_rel_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t*,uintptr_t) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dpaa_portal_map_registers (struct dpaa_portals_softc*) ; 
 int /*<<< orphan*/  mi_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qman_received_frame_callback ; 
 int /*<<< orphan*/  qman_rejected_frame_callback ; 
 struct dpaa_portals_softc* qp_sc ; 
 void* rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

t_Handle
qman_portal_setup(struct qman_softc *qsc)
{
	struct dpaa_portals_softc *sc;
	t_QmPortalParam qpp;
	unsigned int cpu;
	uintptr_t p;
	t_Handle portal;

	/* Return NULL if we're not ready or while detach */
	if (qp_sc == NULL)
		return (NULL);

	sc = qp_sc;

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
	qpp.ceBaseAddress = rman_get_bushandle(sc->sc_rres[0]);
	qpp.ciBaseAddress = rman_get_bushandle(sc->sc_rres[1]);
	qpp.h_Qm = qsc->sc_qh;
	qpp.swPortalId = cpu;
	qpp.irq = (uintptr_t)sc->sc_dp[cpu].dp_ires;
	qpp.fdLiodnOffset = 0;
	qpp.f_DfltFrame = qman_received_frame_callback;
	qpp.f_RejectedFrame = qman_rejected_frame_callback;
	qpp.h_App = qsc;

	portal = QM_PORTAL_Config(&qpp);
	if (portal == NULL)
		goto err;

	if (QM_PORTAL_Init(portal) != E_OK)
		goto err;

	if (QM_PORTAL_AddPoolChannel(portal, QMAN_COMMON_POOL_CHANNEL) != E_OK)
		goto err;

	atomic_store_rel_ptr((uintptr_t *)&sc->sc_dp[cpu].dp_ph,
	    (uintptr_t)portal);
	sched_unpin();

	return (portal);

err:
	if (portal != NULL)
		QM_PORTAL_Free(portal);

	atomic_store_rel_32((uint32_t *)&sc->sc_dp[cpu].dp_ph, 0);
	sched_unpin();

	return (NULL);
}
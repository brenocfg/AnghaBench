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
struct lagg_softc {TYPE_1__* sc_ifp; struct lacp_softc* sc_psc; } ;
struct lacp_softc {int /*<<< orphan*/  lsc_mtx; int /*<<< orphan*/  lsc_callout; int /*<<< orphan*/  lsc_transit_callout; int /*<<< orphan*/  lsc_ports; int /*<<< orphan*/  lsc_aggregators; int /*<<< orphan*/  lsc_strict_mode; int /*<<< orphan*/ * lsc_active_aggregator; int /*<<< orphan*/  lsc_hashkey; struct lagg_softc* lsc_softc; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LACP_LOCK_INIT (struct lacp_softc*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_default_strict_mode ; 
 int /*<<< orphan*/  lacp_init (struct lagg_softc*) ; 
 int /*<<< orphan*/  m_ether_tcpip_hash_init () ; 
 struct lacp_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

void
lacp_attach(struct lagg_softc *sc)
{
	struct lacp_softc *lsc;

	lsc = malloc(sizeof(struct lacp_softc), M_DEVBUF, M_WAITOK | M_ZERO);

	sc->sc_psc = lsc;
	lsc->lsc_softc = sc;

	lsc->lsc_hashkey = m_ether_tcpip_hash_init();
	lsc->lsc_active_aggregator = NULL;
	lsc->lsc_strict_mode = VNET(lacp_default_strict_mode);
	LACP_LOCK_INIT(lsc);
	TAILQ_INIT(&lsc->lsc_aggregators);
	LIST_INIT(&lsc->lsc_ports);

	callout_init_mtx(&lsc->lsc_transit_callout, &lsc->lsc_mtx, 0);
	callout_init_mtx(&lsc->lsc_callout, &lsc->lsc_mtx, 0);

	/* if the lagg is already up then do the same */
	if (sc->sc_ifp->if_drv_flags & IFF_DRV_RUNNING)
		lacp_init(sc);
}
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
struct ifnet {int if_drv_flags; } ;
struct hn_softc {int hn_flags; int hn_tx_ring_inuse; scalar_t__ hn_pollhz; TYPE_1__* hn_tx_ring; struct ifnet* hn_ifp; } ;
struct TYPE_2__ {scalar_t__ hn_oactive; } ;

/* Variables and functions */
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  atomic_clear_int (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int) ; 
 int /*<<< orphan*/  hn_polling (struct hn_softc*,scalar_t__) ; 
 int /*<<< orphan*/  hn_resume_tx (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_rxfilter_config (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_xpnt_vf_init (struct hn_softc*) ; 
 scalar_t__ hn_xpnt_vf_isready (struct hn_softc*) ; 

__attribute__((used)) static void
hn_init_locked(struct hn_softc *sc)
{
	struct ifnet *ifp = sc->hn_ifp;
	int i;

	HN_LOCK_ASSERT(sc);

	if ((sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) == 0)
		return;

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	/* Configure RX filter */
	hn_rxfilter_config(sc);

	/* Clear OACTIVE bit. */
	atomic_clear_int(&ifp->if_drv_flags, IFF_DRV_OACTIVE);
	for (i = 0; i < sc->hn_tx_ring_inuse; ++i)
		sc->hn_tx_ring[i].hn_oactive = 0;

	/* Clear TX 'suspended' bit. */
	hn_resume_tx(sc, sc->hn_tx_ring_inuse);

	if (hn_xpnt_vf_isready(sc)) {
		/* Initialize transparent VF. */
		hn_xpnt_vf_init(sc);
	}

	/* Everything is ready; unleash! */
	atomic_set_int(&ifp->if_drv_flags, IFF_DRV_RUNNING);

	/* Re-enable polling if requested. */
	if (sc->hn_pollhz > 0)
		hn_polling(sc, sc->hn_pollhz);
}
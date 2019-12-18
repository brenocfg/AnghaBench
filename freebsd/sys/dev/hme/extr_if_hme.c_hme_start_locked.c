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
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; scalar_t__ if_softc; } ;
struct TYPE_2__ {int rb_td_nbusy; } ;
struct hme_softc {int sc_flags; int sc_wdog_timer; int /*<<< orphan*/  sc_cdmamap; int /*<<< orphan*/  sc_cdmatag; TYPE_1__ sc_rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int HME_LINK ; 
 int HME_NTXDESC ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hme_load_txmbuf (struct hme_softc*,struct mbuf**) ; 

__attribute__((used)) static void
hme_start_locked(struct ifnet *ifp)
{
	struct hme_softc *sc = (struct hme_softc *)ifp->if_softc;
	struct mbuf *m;
	int error, enq = 0;

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc->sc_flags & HME_LINK) == 0)
		return;

	for (; !IFQ_DRV_IS_EMPTY(&ifp->if_snd) &&
	    sc->sc_rb.rb_td_nbusy < HME_NTXDESC - 1;) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;

		error = hme_load_txmbuf(sc, &m);
		if (error != 0) {
			if (m == NULL)
				break;
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			IFQ_DRV_PREPEND(&ifp->if_snd, m);
			break;
		}
		enq++;
		BPF_MTAP(ifp, m);
	}

	if (enq > 0) {
		bus_dmamap_sync(sc->sc_cdmatag, sc->sc_cdmamap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		sc->sc_wdog_timer = 5;
	}
}
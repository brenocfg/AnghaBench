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
struct nf10bmac_softc {struct ifnet* nf10bmac_ifp; } ;
struct ifnet {int if_capenable; int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NF10BMAC_LOCK (struct nf10bmac_softc*) ; 
 int NF10BMAC_MAX_PKTS ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_CLEAR_DIS (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_ENABLE (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_UNLOCK (struct nf10bmac_softc*) ; 
 int nf10bmac_rx_locked (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
nf10bmac_intr(void *arg)
{
	struct nf10bmac_softc *sc;
	struct ifnet *ifp;
	int rx_npkts;

	sc = (struct nf10bmac_softc *)arg;
	ifp = sc->nf10bmac_ifp;

	NF10BMAC_LOCK(sc);
#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING) {
		NF10BMAC_UNLOCK(sc);
		return;
	} 
#endif

	/* NF10BMAC_RX_INTR_DISABLE(sc); */
	NF10BMAC_RX_INTR_CLEAR_DIS(sc);

	/* We only have an RX interrupt and no status information. */
	rx_npkts = 0;
	while (rx_npkts < NF10BMAC_MAX_PKTS) {
		int c;

		c = nf10bmac_rx_locked(sc);
		rx_npkts += c;
		if (c == 0)
			break;
	}

	if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
		/* Re-enable interrupts. */
		NF10BMAC_RX_INTR_ENABLE(sc);

		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			nf10bmac_start_locked(ifp);
	}
	NF10BMAC_UNLOCK(sc);
}
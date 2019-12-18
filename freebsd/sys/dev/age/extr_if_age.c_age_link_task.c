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
typedef  int uint32_t ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
struct age_softc {int age_flags; struct ifnet* age_ifp; int /*<<< orphan*/  age_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_DMA_CFG ; 
 int AGE_FLAG_LINK ; 
 int /*<<< orphan*/  AGE_LOCK (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_MAC_CFG ; 
 int /*<<< orphan*/  AGE_UNLOCK (struct age_softc*) ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int DMA_CFG_RD_ENB ; 
 int DMA_CFG_WR_ENB ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_AVALID ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int MAC_CFG_RX_ENB ; 
 int MAC_CFG_TX_ENB ; 
 int /*<<< orphan*/  age_mac_config (struct age_softc*) ; 
 int /*<<< orphan*/  age_stop_rxmac (struct age_softc*) ; 
 int /*<<< orphan*/  age_stop_txmac (struct age_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
age_link_task(void *arg, int pending)
{
	struct age_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint32_t reg;

	sc = (struct age_softc *)arg;

	AGE_LOCK(sc);
	mii = device_get_softc(sc->age_miibus);
	ifp = sc->age_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		AGE_UNLOCK(sc);
		return;
	}

	sc->age_flags &= ~AGE_FLAG_LINK;
	if ((mii->mii_media_status & IFM_AVALID) != 0) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
		case IFM_1000_T:
			sc->age_flags |= AGE_FLAG_LINK;
			break;
		default:
			break;
		}
	}

	/* Stop Rx/Tx MACs. */
	age_stop_rxmac(sc);
	age_stop_txmac(sc);

	/* Program MACs with resolved speed/duplex/flow-control. */
	if ((sc->age_flags & AGE_FLAG_LINK) != 0) {
		age_mac_config(sc);
		reg = CSR_READ_4(sc, AGE_MAC_CFG);
		/* Restart DMA engine and Tx/Rx MAC. */
		CSR_WRITE_4(sc, AGE_DMA_CFG, CSR_READ_4(sc, AGE_DMA_CFG) |
		    DMA_CFG_RD_ENB | DMA_CFG_WR_ENB);
		reg |= MAC_CFG_TX_ENB | MAC_CFG_RX_ENB;
		CSR_WRITE_4(sc, AGE_MAC_CFG, reg);
	}

	AGE_UNLOCK(sc);
}
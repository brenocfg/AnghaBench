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
struct alc_softc {int alc_flags; struct ifnet* alc_ifp; int /*<<< orphan*/  alc_miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALC_FLAG_FASTETHER ; 
 int ALC_FLAG_LINK ; 
 int /*<<< orphan*/  ALC_MAC_CFG ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int MAC_CFG_RX_ENB ; 
 int MAC_CFG_TX_ENB ; 
 int /*<<< orphan*/  alc_aspm (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alc_dsp_fixup (struct alc_softc*,int) ; 
 int /*<<< orphan*/  alc_mac_config (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_start_queue (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_stop_mac (struct alc_softc*) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alc_miibus_statchg(device_t dev)
{
	struct alc_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint32_t reg;

	sc = device_get_softc(dev);

	mii = device_get_softc(sc->alc_miibus);
	ifp = sc->alc_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	sc->alc_flags &= ~ALC_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->alc_flags |= ALC_FLAG_LINK;
			break;
		case IFM_1000_T:
			if ((sc->alc_flags & ALC_FLAG_FASTETHER) == 0)
				sc->alc_flags |= ALC_FLAG_LINK;
			break;
		default:
			break;
		}
	}
	/* Stop Rx/Tx MACs. */
	alc_stop_mac(sc);

	/* Program MACs with resolved speed/duplex/flow-control. */
	if ((sc->alc_flags & ALC_FLAG_LINK) != 0) {
		alc_start_queue(sc);
		alc_mac_config(sc);
		/* Re-enable Tx/Rx MACs. */
		reg = CSR_READ_4(sc, ALC_MAC_CFG);
		reg |= MAC_CFG_TX_ENB | MAC_CFG_RX_ENB;
		CSR_WRITE_4(sc, ALC_MAC_CFG, reg);
	}
	alc_aspm(sc, 0, IFM_SUBTYPE(mii->mii_media_active));
	alc_dsp_fixup(sc, IFM_SUBTYPE(mii->mii_media_active));
}
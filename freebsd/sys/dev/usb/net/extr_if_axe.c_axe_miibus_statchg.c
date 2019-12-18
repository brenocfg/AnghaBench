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
typedef  int uint16_t ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
struct axe_softc {int sc_flags; int /*<<< orphan*/  sc_ue; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AXE_178_MEDIA_100TX ; 
 int AXE_178_MEDIA_ENCK ; 
 int AXE_178_MEDIA_GMII ; 
 int AXE_178_MEDIA_MAGIC ; 
 int AXE_178_MEDIA_RXFLOW_CONTROL_EN ; 
 int AXE_178_MEDIA_RX_EN ; 
 int AXE_178_MEDIA_TXFLOW_CONTROL_EN ; 
 int /*<<< orphan*/  AXE_CMD_WRITE_MEDIA ; 
 int AXE_FLAG_178 ; 
 int AXE_FLAG_LINK ; 
 scalar_t__ AXE_IS_178_FAMILY (struct axe_softc*) ; 
 int /*<<< orphan*/  AXE_LOCK (struct axe_softc*) ; 
 int AXE_MEDIA_FULL_DUPLEX ; 
 int /*<<< orphan*/  AXE_UNLOCK (struct axe_softc*) ; 
 struct mii_data* GET_MII (struct axe_softc*) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct axe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
axe_miibus_statchg(device_t dev)
{
	struct axe_softc *sc = device_get_softc(dev);
	struct mii_data *mii = GET_MII(sc);
	struct ifnet *ifp;
	uint16_t val;
	int err, locked;

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		AXE_LOCK(sc);

	ifp = uether_getifp(&sc->sc_ue);
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		goto done;

	sc->sc_flags &= ~AXE_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->sc_flags |= AXE_FLAG_LINK;
			break;
		case IFM_1000_T:
			if ((sc->sc_flags & AXE_FLAG_178) == 0)
				break;
			sc->sc_flags |= AXE_FLAG_LINK;
			break;
		default:
			break;
		}
	}

	/* Lost link, do nothing. */
	if ((sc->sc_flags & AXE_FLAG_LINK) == 0)
		goto done;

	val = 0;
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		val |= AXE_MEDIA_FULL_DUPLEX;
		if (AXE_IS_178_FAMILY(sc)) {
			if ((IFM_OPTIONS(mii->mii_media_active) &
			    IFM_ETH_TXPAUSE) != 0)
				val |= AXE_178_MEDIA_TXFLOW_CONTROL_EN;
			if ((IFM_OPTIONS(mii->mii_media_active) &
			    IFM_ETH_RXPAUSE) != 0)
				val |= AXE_178_MEDIA_RXFLOW_CONTROL_EN;
		}
	}
	if (AXE_IS_178_FAMILY(sc)) {
		val |= AXE_178_MEDIA_RX_EN | AXE_178_MEDIA_MAGIC;
		if ((sc->sc_flags & AXE_FLAG_178) != 0)
			val |= AXE_178_MEDIA_ENCK;
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_1000_T:
			val |= AXE_178_MEDIA_GMII | AXE_178_MEDIA_ENCK;
			break;
		case IFM_100_TX:
			val |= AXE_178_MEDIA_100TX;
			break;
		case IFM_10_T:
			/* doesn't need to be handled */
			break;
		}
	}
	err = axe_cmd(sc, AXE_CMD_WRITE_MEDIA, 0, val, NULL);
	if (err)
		device_printf(dev, "media change failed, error %d\n", err);
done:
	if (!locked)
		AXE_UNLOCK(sc);
}
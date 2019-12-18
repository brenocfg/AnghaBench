#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  ue_udev; } ;
struct muge_softc {int sc_flags; TYPE_1__ sc_ue; int /*<<< orphan*/  sc_mtx; } ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_FCT_FLOW ; 
 int /*<<< orphan*/  ETH_FLOW ; 
 int ETH_FLOW_CR_RX_FCEN_ ; 
 int ETH_FLOW_CR_TX_FCEN_ ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 132 
#define  IFM_100_TX 131 
#define  IFM_10_T 130 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int MUGE_FLAG_LINK ; 
 int /*<<< orphan*/  MUGE_LOCK (struct muge_softc*) ; 
 int /*<<< orphan*/  MUGE_UNLOCK (struct muge_softc*) ; 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_SUPER 128 
 struct muge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int lan78xx_read_reg (struct muge_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*,int) ; 
 struct ifnet* uether_getifp (TYPE_1__*) ; 
 struct mii_data* uether_getmii (TYPE_1__*) ; 
 int usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lan78xx_miibus_statchg(device_t dev)
{
	struct muge_softc *sc = device_get_softc(dev);
	struct mii_data *mii = uether_getmii(&sc->sc_ue);
	struct ifnet *ifp;
	int locked;
	int err;
	uint32_t flow = 0;
	uint32_t fct_flow = 0;

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		MUGE_LOCK(sc);

	ifp = uether_getifp(&sc->sc_ue);
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		goto done;

	/* Use the MII status to determine link status */
	sc->sc_flags &= ~MUGE_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		muge_dbg_printf(sc, "media is active\n");
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->sc_flags |= MUGE_FLAG_LINK;
			muge_dbg_printf(sc, "10/100 ethernet\n");
			break;
		case IFM_1000_T:
			sc->sc_flags |= MUGE_FLAG_LINK;
			muge_dbg_printf(sc, "Gigabit ethernet\n");
			break;
		default:
			break;
		}
	}
	/* Lost link, do nothing. */
	if ((sc->sc_flags & MUGE_FLAG_LINK) == 0) {
		muge_dbg_printf(sc, "link flag not set\n");
		goto done;
	}

	err = lan78xx_read_reg(sc, ETH_FCT_FLOW, &fct_flow);
	if (err) {
		muge_warn_printf(sc,
		   "failed to read initial flow control thresholds, error %d\n",
		    err);
		goto done;
	}

	/* Enable/disable full duplex operation and TX/RX pause. */
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		muge_dbg_printf(sc, "full duplex operation\n");

		/* Enable transmit MAC flow control function. */
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_ETH_TXPAUSE) != 0)
			flow |= ETH_FLOW_CR_TX_FCEN_ | 0xFFFF;

		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_ETH_RXPAUSE) != 0)
			flow |= ETH_FLOW_CR_RX_FCEN_;
	}

	/* XXX Flow control settings obtained from Microchip's driver. */
	switch(usbd_get_speed(sc->sc_ue.ue_udev)) {
	case USB_SPEED_SUPER:
		fct_flow = 0x817;
		break;
	case USB_SPEED_HIGH:
		fct_flow = 0x211;
		break;
	default:
		break;
	}

	err += lan78xx_write_reg(sc, ETH_FLOW, flow);
	err += lan78xx_write_reg(sc, ETH_FCT_FLOW, fct_flow);
	if (err)
		muge_warn_printf(sc, "media change failed, error %d\n", err);

done:
	if (!locked)
		MUGE_UNLOCK(sc);
}
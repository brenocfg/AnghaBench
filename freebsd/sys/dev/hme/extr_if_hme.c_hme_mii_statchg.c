#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hme_softc {int sc_flags; int /*<<< orphan*/  sc_dev; TYPE_2__* sc_ifp; TYPE_1__* sc_mii; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int if_flags; int if_drv_flags; } ;
struct TYPE_3__ {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;

/* Variables and functions */
 int HME_LINK ; 
 int /*<<< orphan*/  HME_MACI_RXCFG ; 
 int /*<<< orphan*/  HME_MACI_TXCFG ; 
 int /*<<< orphan*/  HME_MAC_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MAC_RXCFG_ENABLE ; 
 int /*<<< orphan*/  HME_MAC_TXCFG_ENABLE ; 
 int /*<<< orphan*/  HME_MAC_TXCFG_FULLDPLX ; 
 int /*<<< orphan*/  HME_MAC_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_DEBUG ; 
 int IFF_DRV_RUNNING ; 
 int IFM_ACTIVE ; 
 int IFM_FDX ; 
 scalar_t__ IFM_NONE ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 struct hme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hme_mac_bitflip (struct hme_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
hme_mii_statchg(device_t dev)
{
	struct hme_softc *sc;
	uint32_t rxcfg, txcfg;

	sc = device_get_softc(dev);

#ifdef HMEDEBUG
	if ((sc->sc_ifp->if_flags & IFF_DEBUG) != 0)
		device_printf(sc->sc_dev, "hme_mii_statchg: status change\n");
#endif

	if ((sc->sc_mii->mii_media_status & IFM_ACTIVE) != 0 &&
	    IFM_SUBTYPE(sc->sc_mii->mii_media_active) != IFM_NONE)
		sc->sc_flags |= HME_LINK;
	else
		sc->sc_flags &= ~HME_LINK;

	txcfg = HME_MAC_READ_4(sc, HME_MACI_TXCFG);
	if (!hme_mac_bitflip(sc, HME_MACI_TXCFG, txcfg,
	    HME_MAC_TXCFG_ENABLE, 0))
		device_printf(sc->sc_dev, "cannot disable TX MAC\n");
	rxcfg = HME_MAC_READ_4(sc, HME_MACI_RXCFG);
	if (!hme_mac_bitflip(sc, HME_MACI_RXCFG, rxcfg,
	    HME_MAC_RXCFG_ENABLE, 0))
		device_printf(sc->sc_dev, "cannot disable RX MAC\n");

	/* Set the MAC Full Duplex bit appropriately. */
	if ((IFM_OPTIONS(sc->sc_mii->mii_media_active) & IFM_FDX) != 0)
		txcfg |= HME_MAC_TXCFG_FULLDPLX;
	else
		txcfg &= ~HME_MAC_TXCFG_FULLDPLX;
	HME_MAC_WRITE_4(sc, HME_MACI_TXCFG, txcfg);

	if ((sc->sc_ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
	    (sc->sc_flags & HME_LINK) != 0) {
		if (!hme_mac_bitflip(sc, HME_MACI_TXCFG, txcfg, 0,
		    HME_MAC_TXCFG_ENABLE))
			device_printf(sc->sc_dev, "cannot enable TX MAC\n");
		if (!hme_mac_bitflip(sc, HME_MACI_RXCFG, rxcfg, 0,
		    HME_MAC_RXCFG_ENABLE))
			device_printf(sc->sc_dev, "cannot enable RX MAC\n");
	}
}
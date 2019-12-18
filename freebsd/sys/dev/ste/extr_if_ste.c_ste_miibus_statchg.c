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
struct ste_softc {int ste_flags; struct ifnet* ste_ifp; int /*<<< orphan*/  ste_miibus; } ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_2 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_100_FX 131 
#define  IFM_100_T4 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int STE_FLAG_LINK ; 
 int /*<<< orphan*/  STE_MACCTL0 ; 
 int STE_MACCTL0_FLOWCTL_ENABLE ; 
 int STE_MACCTL0_FULLDUPLEX ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ste_miibus_statchg(device_t dev)
{
	struct ste_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint16_t cfg;

	sc = device_get_softc(dev);

	mii = device_get_softc(sc->ste_miibus);
	ifp = sc->ste_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	sc->ste_flags &= ~STE_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
		case IFM_100_FX:
		case IFM_100_T4:
			sc->ste_flags |= STE_FLAG_LINK;
		default:
			break;
		}
	}

	/* Program MACs with resolved speed/duplex/flow-control. */
	if ((sc->ste_flags & STE_FLAG_LINK) != 0) {
		cfg = CSR_READ_2(sc, STE_MACCTL0);
		cfg &= ~(STE_MACCTL0_FLOWCTL_ENABLE | STE_MACCTL0_FULLDUPLEX);
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
			/*
			 * ST201 data sheet says driver should enable receiving
			 * MAC control frames bit of receive mode register to
			 * receive flow-control frames but the register has no
			 * such bits. In addition the controller has no ability
			 * to send pause frames so it should be handled in
			 * driver. Implementing pause timer handling in driver
			 * layer is not trivial, so don't enable flow-control
			 * here.
			 */
			cfg |= STE_MACCTL0_FULLDUPLEX;
		}
		CSR_WRITE_2(sc, STE_MACCTL0, cfg);
	}
}
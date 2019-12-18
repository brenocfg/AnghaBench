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
struct emac_softc {int emac_link; struct ifnet* emac_ifp; int /*<<< orphan*/  emac_miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_CTL ; 
 int EMAC_CTL_RST ; 
 int EMAC_CTL_RX_EN ; 
 int EMAC_CTL_TX_EN ; 
 int /*<<< orphan*/  EMAC_MAC_IPGT ; 
 int EMAC_MAC_IPGT_FD ; 
 int EMAC_MAC_IPGT_HD ; 
 int EMAC_READ_REG (struct emac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_WRITE_REG (struct emac_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emac_miibus_statchg(device_t dev)
{
	struct emac_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint32_t reg_val;

	sc = device_get_softc(dev);

	mii = device_get_softc(sc->emac_miibus);
	ifp = sc->emac_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	sc->emac_link = 0;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->emac_link = 1;
			break;
		default:
			break;
		}
	}
	/* Program MACs with resolved speed/duplex. */
	if (sc->emac_link != 0) {
		reg_val = EMAC_READ_REG(sc, EMAC_MAC_IPGT);
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
			reg_val &= ~EMAC_MAC_IPGT_HD;
			reg_val |= EMAC_MAC_IPGT_FD;
		} else {
			reg_val &= ~EMAC_MAC_IPGT_FD;
			reg_val |= EMAC_MAC_IPGT_HD;
		}
		EMAC_WRITE_REG(sc, EMAC_MAC_IPGT, reg_val);
		/* Enable RX/TX */
		reg_val = EMAC_READ_REG(sc, EMAC_CTL);
		reg_val |= EMAC_CTL_RST | EMAC_CTL_TX_EN | EMAC_CTL_RX_EN;
		EMAC_WRITE_REG(sc, EMAC_CTL, reg_val);
	} else {
		/* Disable RX/TX */
		reg_val = EMAC_READ_REG(sc, EMAC_CTL);
		reg_val &= ~(EMAC_CTL_RST | EMAC_CTL_TX_EN | EMAC_CTL_RX_EN);
		EMAC_WRITE_REG(sc, EMAC_CTL, reg_val);
	}
}
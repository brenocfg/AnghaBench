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
struct sis_softc {int sis_flags; scalar_t__ sis_type; scalar_t__ sis_srr; int /*<<< orphan*/  sis_dev; struct ifnet* sis_ifp; int /*<<< orphan*/  sis_miibus; } ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int const IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_PHY_DSPCFG ; 
 int /*<<< orphan*/  NS_PHY_PAGE ; 
 int /*<<< orphan*/  NS_PHY_TDATA ; 
 scalar_t__ NS_SRR_16A ; 
 int /*<<< orphan*/  SIS_CLRBIT (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIS_CSR ; 
 int SIS_CSR_RX_DISABLE ; 
 int SIS_CSR_RX_ENABLE ; 
 int SIS_CSR_TX_DISABLE ; 
 int SIS_CSR_TX_ENABLE ; 
 int SIS_FLAG_LINK ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int SIS_RXCFG_RX_TXPKTS ; 
 int /*<<< orphan*/  SIS_RX_CFG ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int SIS_TXCFG_10 ; 
 int SIS_TXCFG_100 ; 
 int SIS_TXCFG_IGN_CARR ; 
 int SIS_TXCFG_IGN_HBEAT ; 
 int SIS_TXCFG_MPII03D ; 
 int /*<<< orphan*/  SIS_TX_CFG ; 
 scalar_t__ SIS_TYPE_83815 ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
sis_miibus_statchg(device_t dev)
{
	struct sis_softc	*sc;
	struct mii_data		*mii;
	struct ifnet		*ifp;
	uint32_t		reg;

	sc = device_get_softc(dev);
	SIS_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->sis_miibus);
	ifp = sc->sis_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	sc->sis_flags &= ~SIS_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
			CSR_WRITE_4(sc, SIS_TX_CFG, SIS_TXCFG_10);
			sc->sis_flags |= SIS_FLAG_LINK;
			break;
		case IFM_100_TX:
			CSR_WRITE_4(sc, SIS_TX_CFG, SIS_TXCFG_100);
			sc->sis_flags |= SIS_FLAG_LINK;
			break;
		default:
			break;
		}
	}

	if ((sc->sis_flags & SIS_FLAG_LINK) == 0) {
		/*
		 * Stopping MACs seem to reset SIS_TX_LISTPTR and
		 * SIS_RX_LISTPTR which in turn requires resetting
		 * TX/RX buffers.  So just don't do anything for
		 * lost link.
		 */
		return;
	}

	/* Set full/half duplex mode. */
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		SIS_SETBIT(sc, SIS_TX_CFG,
		    (SIS_TXCFG_IGN_HBEAT | SIS_TXCFG_IGN_CARR));
		SIS_SETBIT(sc, SIS_RX_CFG, SIS_RXCFG_RX_TXPKTS);
	} else {
		SIS_CLRBIT(sc, SIS_TX_CFG,
		    (SIS_TXCFG_IGN_HBEAT | SIS_TXCFG_IGN_CARR));
		SIS_CLRBIT(sc, SIS_RX_CFG, SIS_RXCFG_RX_TXPKTS);
	}

	if (sc->sis_type == SIS_TYPE_83815 && sc->sis_srr >= NS_SRR_16A) {
		/*
		 * MPII03.D: Half Duplex Excessive Collisions.
		 * Also page 49 in 83816 manual
		 */
		SIS_SETBIT(sc, SIS_TX_CFG, SIS_TXCFG_MPII03D);
	}

	if (sc->sis_type == SIS_TYPE_83815 && sc->sis_srr < NS_SRR_16A &&
	    IFM_SUBTYPE(mii->mii_media_active) == IFM_100_TX) {
		/*
		 * Short Cable Receive Errors (MP21.E)
		 */
		CSR_WRITE_4(sc, NS_PHY_PAGE, 0x0001);
		reg = CSR_READ_4(sc, NS_PHY_DSPCFG) & 0xfff;
		CSR_WRITE_4(sc, NS_PHY_DSPCFG, reg | 0x1000);
		DELAY(100);
		reg = CSR_READ_4(sc, NS_PHY_TDATA) & 0xff;
		if ((reg & 0x0080) == 0 || (reg > 0xd8 && reg <= 0xff)) {
			device_printf(sc->sis_dev,
			    "Applying short cable fix (reg=%x)\n", reg);
			CSR_WRITE_4(sc, NS_PHY_TDATA, 0x00e8);
			SIS_SETBIT(sc, NS_PHY_DSPCFG, 0x20);
		}
		CSR_WRITE_4(sc, NS_PHY_PAGE, 0);
	}
	/* Enable TX/RX MACs. */
	SIS_CLRBIT(sc, SIS_CSR, SIS_CSR_TX_DISABLE | SIS_CSR_RX_DISABLE);
	SIS_SETBIT(sc, SIS_CSR, SIS_CSR_TX_ENABLE | SIS_CSR_RX_ENABLE);
}
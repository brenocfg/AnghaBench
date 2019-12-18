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
typedef  scalar_t__ u_int ;
struct mii_softc {int mii_flags; struct mii_data* mii_pdata; } ;
struct mii_data {scalar_t__ mii_media_active; int /*<<< orphan*/  mii_media_status; } ;
struct brgphy_softc {int serdes_flags; } ;

/* Variables and functions */
 int BRGPHY_1000STS_MSR ; 
 int BRGPHY_5706S ; 
 int BRGPHY_5708S ; 
 int /*<<< orphan*/  BRGPHY_5708S_BLOCK_ADDR ; 
 int /*<<< orphan*/  BRGPHY_5708S_DIG_PG0 ; 
 int /*<<< orphan*/  BRGPHY_5708S_PG0_1000X_STAT1 ; 
 int BRGPHY_5708S_PG0_1000X_STAT1_FDX ; 
#define  BRGPHY_5708S_PG0_1000X_STAT1_SPEED_10 142 
#define  BRGPHY_5708S_PG0_1000X_STAT1_SPEED_100 141 
#define  BRGPHY_5708S_PG0_1000X_STAT1_SPEED_1G 140 
#define  BRGPHY_5708S_PG0_1000X_STAT1_SPEED_25G 139 
 int BRGPHY_5708S_PG0_1000X_STAT1_SPEED_MASK ; 
 int BRGPHY_5709S ; 
 int BRGPHY_AUXSTS_AN_RES ; 
 int BRGPHY_AUXSTS_LINK ; 
 int /*<<< orphan*/  BRGPHY_BLOCK_ADDR ; 
 int /*<<< orphan*/  BRGPHY_BLOCK_ADDR_COMBO_IEEE0 ; 
 int /*<<< orphan*/  BRGPHY_BLOCK_ADDR_GP_STATUS ; 
 int BRGPHY_BMCR_AUTOEN ; 
 int BRGPHY_BMCR_LOOP ; 
 int BRGPHY_BMSR_ACOMP ; 
 int BRGPHY_BMSR_LINK ; 
 int BRGPHY_GP_STATUS_TOP_ANEG_FDX ; 
#define  BRGPHY_GP_STATUS_TOP_ANEG_SPEED_10 138 
#define  BRGPHY_GP_STATUS_TOP_ANEG_SPEED_100 137 
#define  BRGPHY_GP_STATUS_TOP_ANEG_SPEED_1G 136 
#define  BRGPHY_GP_STATUS_TOP_ANEG_SPEED_25G 135 
 int BRGPHY_GP_STATUS_TOP_ANEG_SPEED_MASK ; 
 int /*<<< orphan*/  BRGPHY_GP_STATUS_TOP_ANEG_STATUS ; 
 int /*<<< orphan*/  BRGPHY_MII_1000STS ; 
 int /*<<< orphan*/  BRGPHY_MII_AUXSTS ; 
 int /*<<< orphan*/  BRGPHY_MII_BMCR ; 
 int /*<<< orphan*/  BRGPHY_MII_BMSR ; 
 int BRGPHY_NOANWAIT ; 
#define  BRGPHY_RES_1000FD 134 
#define  BRGPHY_RES_1000HD 133 
#define  BRGPHY_RES_100FD 132 
#define  BRGPHY_RES_100HD 131 
#define  BRGPHY_RES_100T4 130 
#define  BRGPHY_RES_10FD 129 
#define  BRGPHY_RES_10HD 128 
 int /*<<< orphan*/  BRGPHY_SERDES_ANAR ; 
 int BRGPHY_SERDES_ANAR_FDX ; 
 int /*<<< orphan*/  BRGPHY_SERDES_ANLPAR ; 
 scalar_t__ IFM_1000_SX ; 
 scalar_t__ IFM_1000_T ; 
 scalar_t__ IFM_100_FX ; 
 scalar_t__ IFM_100_T4 ; 
 scalar_t__ IFM_100_TX ; 
 scalar_t__ IFM_10_FL ; 
 scalar_t__ IFM_10_T ; 
 scalar_t__ IFM_2500_SX ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_ETH_MASTER ; 
 scalar_t__ IFM_FDX ; 
 scalar_t__ IFM_HDX ; 
 scalar_t__ IFM_LOOP ; 
 scalar_t__ IFM_NONE ; 
 scalar_t__ IFM_SUBTYPE (scalar_t__) ; 
 int MIIF_HAVEFIBER ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
brgphy_status(struct mii_softc *sc)
{
	struct brgphy_softc *bsc = (struct brgphy_softc *)sc;
	struct mii_data *mii = sc->mii_pdata;
	int aux, bmcr, bmsr, val, xstat;
	u_int flowstat;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	bmsr = PHY_READ(sc, BRGPHY_MII_BMSR) | PHY_READ(sc, BRGPHY_MII_BMSR);
	bmcr = PHY_READ(sc, BRGPHY_MII_BMCR);

	if (bmcr & BRGPHY_BMCR_LOOP) {
		mii->mii_media_active |= IFM_LOOP;
	}

	if ((bmcr & BRGPHY_BMCR_AUTOEN) &&
	    (bmsr & BRGPHY_BMSR_ACOMP) == 0 &&
	    (bsc->serdes_flags & BRGPHY_NOANWAIT) == 0) {
		/* Erg, still trying, I guess... */
		mii->mii_media_active |= IFM_NONE;
		return;
	}

	if ((sc->mii_flags & MIIF_HAVEFIBER) == 0) {
		/*
		 * NB: reading the ANAR, ANLPAR or 1000STS after the AUXSTS
		 * wedges at least the PHY of BCM5704 (but not others).
		 */
		flowstat = mii_phy_flowstatus(sc);
		xstat = PHY_READ(sc, BRGPHY_MII_1000STS);
		aux = PHY_READ(sc, BRGPHY_MII_AUXSTS);

		/* If copper link is up, get the negotiated speed/duplex. */
		if (aux & BRGPHY_AUXSTS_LINK) {
			mii->mii_media_status |= IFM_ACTIVE;
			switch (aux & BRGPHY_AUXSTS_AN_RES) {
			case BRGPHY_RES_1000FD:
				mii->mii_media_active |= IFM_1000_T | IFM_FDX; 	break;
			case BRGPHY_RES_1000HD:
				mii->mii_media_active |= IFM_1000_T | IFM_HDX; 	break;
			case BRGPHY_RES_100FD:
				mii->mii_media_active |= IFM_100_TX | IFM_FDX; break;
			case BRGPHY_RES_100T4:
				mii->mii_media_active |= IFM_100_T4; break;
			case BRGPHY_RES_100HD:
				mii->mii_media_active |= IFM_100_TX | IFM_HDX; 	break;
			case BRGPHY_RES_10FD:
				mii->mii_media_active |= IFM_10_T | IFM_FDX; break;
			case BRGPHY_RES_10HD:
				mii->mii_media_active |= IFM_10_T | IFM_HDX; break;
			default:
				mii->mii_media_active |= IFM_NONE; break;
			}

			if ((mii->mii_media_active & IFM_FDX) != 0)
				mii->mii_media_active |= flowstat;

			if (IFM_SUBTYPE(mii->mii_media_active) == IFM_1000_T &&
			    (xstat & BRGPHY_1000STS_MSR) != 0)
				mii->mii_media_active |= IFM_ETH_MASTER;
		}
	} else {
		/* Todo: Add support for flow control. */
		/* If serdes link is up, get the negotiated speed/duplex. */
		if (bmsr & BRGPHY_BMSR_LINK) {
			mii->mii_media_status |= IFM_ACTIVE;
		}

		/* Check the link speed/duplex based on the PHY type. */
		if (bsc->serdes_flags & BRGPHY_5706S) {
			mii->mii_media_active |= IFM_1000_SX;

			/* If autoneg enabled, read negotiated duplex settings */
			if (bmcr & BRGPHY_BMCR_AUTOEN) {
				val = PHY_READ(sc, BRGPHY_SERDES_ANAR) & PHY_READ(sc, BRGPHY_SERDES_ANLPAR);
				if (val & BRGPHY_SERDES_ANAR_FDX)
					mii->mii_media_active |= IFM_FDX;
				else
					mii->mii_media_active |= IFM_HDX;
			}
		} else if (bsc->serdes_flags & BRGPHY_5708S) {
			PHY_WRITE(sc, BRGPHY_5708S_BLOCK_ADDR, BRGPHY_5708S_DIG_PG0);
			xstat = PHY_READ(sc, BRGPHY_5708S_PG0_1000X_STAT1);

			/* Check for MRBE auto-negotiated speed results. */
			switch (xstat & BRGPHY_5708S_PG0_1000X_STAT1_SPEED_MASK) {
			case BRGPHY_5708S_PG0_1000X_STAT1_SPEED_10:
				mii->mii_media_active |= IFM_10_FL; break;
			case BRGPHY_5708S_PG0_1000X_STAT1_SPEED_100:
				mii->mii_media_active |= IFM_100_FX; break;
			case BRGPHY_5708S_PG0_1000X_STAT1_SPEED_1G:
				mii->mii_media_active |= IFM_1000_SX; break;
			case BRGPHY_5708S_PG0_1000X_STAT1_SPEED_25G:
				mii->mii_media_active |= IFM_2500_SX; break;
			}

			/* Check for MRBE auto-negotiated duplex results. */
			if (xstat & BRGPHY_5708S_PG0_1000X_STAT1_FDX)
				mii->mii_media_active |= IFM_FDX;
			else
				mii->mii_media_active |= IFM_HDX;
		} else if (bsc->serdes_flags & BRGPHY_5709S) {
			/* Select GP Status Block of the AN MMD, get autoneg results. */
			PHY_WRITE(sc, BRGPHY_BLOCK_ADDR, BRGPHY_BLOCK_ADDR_GP_STATUS);
			xstat = PHY_READ(sc, BRGPHY_GP_STATUS_TOP_ANEG_STATUS);

			/* Restore IEEE0 block (assumed in all brgphy(4) code). */
			PHY_WRITE(sc, BRGPHY_BLOCK_ADDR, BRGPHY_BLOCK_ADDR_COMBO_IEEE0);

			/* Check for MRBE auto-negotiated speed results. */
			switch (xstat & BRGPHY_GP_STATUS_TOP_ANEG_SPEED_MASK) {
				case BRGPHY_GP_STATUS_TOP_ANEG_SPEED_10:
					mii->mii_media_active |= IFM_10_FL; break;
				case BRGPHY_GP_STATUS_TOP_ANEG_SPEED_100:
					mii->mii_media_active |= IFM_100_FX; break;
				case BRGPHY_GP_STATUS_TOP_ANEG_SPEED_1G:
					mii->mii_media_active |= IFM_1000_SX; break;
				case BRGPHY_GP_STATUS_TOP_ANEG_SPEED_25G:
					mii->mii_media_active |= IFM_2500_SX; break;
			}

			/* Check for MRBE auto-negotiated duplex results. */
			if (xstat & BRGPHY_GP_STATUS_TOP_ANEG_FDX)
				mii->mii_media_active |= IFM_FDX;
			else
				mii->mii_media_active |= IFM_HDX;
		}
	}
}
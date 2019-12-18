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
typedef  int /*<<< orphan*/  uint32_t ;
struct mii_data {int mii_media_status; int mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
struct atse_softc {int atse_flags; struct ifnet* atse_ifp; int /*<<< orphan*/  atse_miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATSE_FLAGS_LINK ; 
 int /*<<< orphan*/  ATSE_LOCK_ASSERT (struct atse_softc*) ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG_ENA_10 ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG_ETH_SPEED ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG_HD_ENA ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG_RX_ENA ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG_TX_ENA ; 
 int /*<<< orphan*/  CSR_READ_4 (struct atse_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct atse_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_FDX ; 
 scalar_t__ IFM_OPTIONS (int) ; 
 int IFM_SUBTYPE (int) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

void
atse_miibus_statchg(device_t dev)
{
	struct atse_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint32_t val4;

	sc = device_get_softc(dev);
	ATSE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->atse_miibus);
	ifp = sc->atse_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		return;
	}

	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);

	/* Assume no link. */
	sc->atse_flags &= ~ATSE_FLAGS_LINK;

	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {

		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
			val4 |= BASE_CFG_COMMAND_CONFIG_ENA_10;
			val4 &= ~BASE_CFG_COMMAND_CONFIG_ETH_SPEED;
			sc->atse_flags |= ATSE_FLAGS_LINK;
			break;
		case IFM_100_TX:
			val4 &= ~BASE_CFG_COMMAND_CONFIG_ENA_10;
			val4 &= ~BASE_CFG_COMMAND_CONFIG_ETH_SPEED;
			sc->atse_flags |= ATSE_FLAGS_LINK;
			break;
		case IFM_1000_T:
			val4 &= ~BASE_CFG_COMMAND_CONFIG_ENA_10;
			val4 |= BASE_CFG_COMMAND_CONFIG_ETH_SPEED;
			sc->atse_flags |= ATSE_FLAGS_LINK;
			break;
		default:
			break;
		}
	}

	if ((sc->atse_flags & ATSE_FLAGS_LINK) == 0) {
		/* Need to stop the MAC? */
		return;
	}

	if (IFM_OPTIONS(mii->mii_media_active & IFM_FDX) != 0) {
		val4 &= ~BASE_CFG_COMMAND_CONFIG_HD_ENA;
	} else {
		val4 |= BASE_CFG_COMMAND_CONFIG_HD_ENA;
	}

	/* flow control? */

	/* Make sure the MAC is activated. */
	val4 |= BASE_CFG_COMMAND_CONFIG_TX_ENA;
	val4 |= BASE_CFG_COMMAND_CONFIG_RX_ENA;

	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);
}
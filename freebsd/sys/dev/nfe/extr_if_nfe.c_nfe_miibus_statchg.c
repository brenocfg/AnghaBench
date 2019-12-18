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
struct nfe_softc {int nfe_link; int /*<<< orphan*/  nfe_ifp; int /*<<< orphan*/  nfe_miibus; } ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_RX_CTL ; 
 int /*<<< orphan*/  NFE_RX_START ; 
 int /*<<< orphan*/  NFE_TX_CTL ; 
 int /*<<< orphan*/  NFE_TX_START ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_mac_config (struct nfe_softc*,struct mii_data*) ; 

__attribute__((used)) static void
nfe_miibus_statchg(device_t dev)
{
	struct nfe_softc *sc;
	struct mii_data *mii;
	if_t ifp;
	uint32_t rxctl, txctl;

	sc = device_get_softc(dev);

	mii = device_get_softc(sc->nfe_miibus);
	ifp = sc->nfe_ifp;

	sc->nfe_link = 0;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
		case IFM_1000_T:
			sc->nfe_link = 1;
			break;
		default:
			break;
		}
	}

	nfe_mac_config(sc, mii);
	txctl = NFE_READ(sc, NFE_TX_CTL);
	rxctl = NFE_READ(sc, NFE_RX_CTL);
	if (sc->nfe_link != 0 && (if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
		txctl |= NFE_TX_START;
		rxctl |= NFE_RX_START;
	} else {
		txctl &= ~NFE_TX_START;
		rxctl &= ~NFE_RX_START;
	}
	NFE_WRITE(sc, NFE_TX_CTL, txctl);
	NFE_WRITE(sc, NFE_RX_CTL, rxctl);
}
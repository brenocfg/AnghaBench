#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct bfe_softc {TYPE_1__* sc_mii; int /*<<< orphan*/  bfe_flags; int /*<<< orphan*/  bfe_miibus; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  mii_media_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_FLAG_LINK ; 
 int /*<<< orphan*/  BFE_FLOW_PAUSE_ENAB ; 
 int /*<<< orphan*/  BFE_MAC_FLOW ; 
 int /*<<< orphan*/  BFE_RXCONF ; 
 int /*<<< orphan*/  BFE_RXCONF_FLOW ; 
 int /*<<< orphan*/  BFE_TX_CTRL ; 
 int /*<<< orphan*/  BFE_TX_DUPLEX ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfe_miibus_statchg(device_t dev)
{
	struct bfe_softc *sc;
	struct mii_data *mii;
	u_int32_t val, flow;

	sc = device_get_softc(dev);
	mii = device_get_softc(sc->bfe_miibus);

	sc->bfe_flags &= ~BFE_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->bfe_flags |= BFE_FLAG_LINK;
			break;
		default:
			break;
		}
	}

	/* XXX Should stop Rx/Tx engine prior to touching MAC. */
	val = CSR_READ_4(sc, BFE_TX_CTRL);
	val &= ~BFE_TX_DUPLEX;
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		val |= BFE_TX_DUPLEX;
		flow = 0;
#ifdef notyet
		flow = CSR_READ_4(sc, BFE_RXCONF);
		flow &= ~BFE_RXCONF_FLOW;
		if ((IFM_OPTIONS(sc->sc_mii->mii_media_active) &
		    IFM_ETH_RXPAUSE) != 0)
			flow |= BFE_RXCONF_FLOW;
		CSR_WRITE_4(sc, BFE_RXCONF, flow);
		/*
		 * It seems that the hardware has Tx pause issues
		 * so enable only Rx pause.
		 */
		flow = CSR_READ_4(sc, BFE_MAC_FLOW);
		flow &= ~BFE_FLOW_PAUSE_ENAB;
		CSR_WRITE_4(sc, BFE_MAC_FLOW, flow);
#endif
	}
	CSR_WRITE_4(sc, BFE_TX_CTRL, val);
}
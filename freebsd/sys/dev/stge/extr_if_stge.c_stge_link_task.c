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
struct stge_softc {int sc_link; int sc_MACCtrl; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_miibus; } ;
struct mii_data {int mii_media_status; int mii_media_active; } ;

/* Variables and functions */
 int AC_ResetBusy ; 
 int AC_RxReset ; 
 int AC_TxReset ; 
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFM_ACTIVE ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 int IFM_GMASK ; 
 scalar_t__ IFM_NONE ; 
 scalar_t__ IFM_SUBTYPE (int) ; 
 int MC_DuplexSelect ; 
 int MC_MASK ; 
 int MC_RxFlowControlEnable ; 
 int MC_TxFlowControlEnable ; 
 int /*<<< orphan*/  STGE_AsicCtrl ; 
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_MACCtrl ; 
 int STGE_TIMEOUT ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
stge_link_task(void *arg, int pending)
{
	struct stge_softc *sc;
	struct mii_data *mii;
	uint32_t v, ac;
	int i;

	sc = (struct stge_softc *)arg;
	STGE_LOCK(sc);

	mii = device_get_softc(sc->sc_miibus);
	if (mii->mii_media_status & IFM_ACTIVE) {
		if (IFM_SUBTYPE(mii->mii_media_active) != IFM_NONE)
			sc->sc_link = 1;
	} else
		sc->sc_link = 0;

	sc->sc_MACCtrl = 0;
	if (((mii->mii_media_active & IFM_GMASK) & IFM_FDX) != 0)
		sc->sc_MACCtrl |= MC_DuplexSelect;
	if (((mii->mii_media_active & IFM_GMASK) & IFM_ETH_RXPAUSE) != 0)
		sc->sc_MACCtrl |= MC_RxFlowControlEnable;
	if (((mii->mii_media_active & IFM_GMASK) & IFM_ETH_TXPAUSE) != 0)
		sc->sc_MACCtrl |= MC_TxFlowControlEnable;
	/*
	 * Update STGE_MACCtrl register depending on link status.
	 * (duplex, flow control etc)
	 */
	v = ac = CSR_READ_4(sc, STGE_MACCtrl) & MC_MASK;
	v &= ~(MC_DuplexSelect|MC_RxFlowControlEnable|MC_TxFlowControlEnable);
	v |= sc->sc_MACCtrl;
	CSR_WRITE_4(sc, STGE_MACCtrl, v);
	if (((ac ^ sc->sc_MACCtrl) & MC_DuplexSelect) != 0) {
		/* Duplex setting changed, reset Tx/Rx functions. */
		ac = CSR_READ_4(sc, STGE_AsicCtrl);
		ac |= AC_TxReset | AC_RxReset;
		CSR_WRITE_4(sc, STGE_AsicCtrl, ac);
		for (i = 0; i < STGE_TIMEOUT; i++) {
			DELAY(100);
			if ((CSR_READ_4(sc, STGE_AsicCtrl) & AC_ResetBusy) == 0)
				break;
		}
		if (i == STGE_TIMEOUT)
			device_printf(sc->sc_dev, "reset failed to complete\n");
	}
	STGE_UNLOCK(sc);
}
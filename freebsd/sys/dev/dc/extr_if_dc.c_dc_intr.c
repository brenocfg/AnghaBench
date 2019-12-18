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
typedef  int uint32_t ;
struct ifnet {int if_capenable; int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct TYPE_2__ {scalar_t__ dc_tx_cnt; } ;
struct dc_softc {TYPE_1__ dc_cdata; struct ifnet* dc_ifp; scalar_t__ suspended; } ;

/* Variables and functions */
 int CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_FRAMESDISCARDED ; 
 int /*<<< orphan*/  DC_IMR ; 
 int DC_INTRS ; 
 int /*<<< orphan*/  DC_ISR ; 
 int DC_ISR_BUS_ERR ; 
 int DC_ISR_RX_NOBUF ; 
 int DC_ISR_RX_OK ; 
 int DC_ISR_RX_WATDOGTIMEO ; 
 int DC_ISR_TX_IDLE ; 
 int DC_ISR_TX_NOBUF ; 
 int DC_ISR_TX_OK ; 
 int DC_ISR_TX_UNDERRUN ; 
 int /*<<< orphan*/  DC_LOCK (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int /*<<< orphan*/  DC_NETCFG_TX_ON ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_TXSTART ; 
 int /*<<< orphan*/  DC_UNLOCK (struct dc_softc*) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_init_locked (struct dc_softc*) ; 
 scalar_t__ dc_rx_resync (struct dc_softc*) ; 
 scalar_t__ dc_rxeof (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  dc_tx_underrun (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_txeof (struct dc_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dc_intr(void *arg)
{
	struct dc_softc *sc;
	struct ifnet *ifp;
	uint32_t r, status;
	int n;

	sc = arg;

	if (sc->suspended)
		return;

	DC_LOCK(sc);
	status = CSR_READ_4(sc, DC_ISR);
	if (status == 0xFFFFFFFF || (status & DC_INTRS) == 0) {
		DC_UNLOCK(sc);
		return;
	}
	ifp = sc->dc_ifp;
#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING) {
		DC_UNLOCK(sc);
		return;
	}
#endif
	/* Disable interrupts. */
	CSR_WRITE_4(sc, DC_IMR, 0x00000000);

	for (n = 16; n > 0; n--) {
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		/* Ack interrupts. */
		CSR_WRITE_4(sc, DC_ISR, status);

		if (status & DC_ISR_RX_OK) {
			if (dc_rxeof(sc) == 0) {
				while (dc_rx_resync(sc))
					dc_rxeof(sc);
			}
		}

		if (status & (DC_ISR_TX_OK | DC_ISR_TX_NOBUF))
			dc_txeof(sc);

		if (status & DC_ISR_TX_IDLE) {
			dc_txeof(sc);
			if (sc->dc_cdata.dc_tx_cnt) {
				DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_TX_ON);
				CSR_WRITE_4(sc, DC_TXSTART, 0xFFFFFFFF);
			}
		}

		if (status & DC_ISR_TX_UNDERRUN)
			dc_tx_underrun(sc);

		if ((status & DC_ISR_RX_WATDOGTIMEO)
		    || (status & DC_ISR_RX_NOBUF)) {
			r = CSR_READ_4(sc, DC_FRAMESDISCARDED);
			if_inc_counter(ifp, IFCOUNTER_IERRORS, (r & 0xffff) + ((r >> 17) & 0x7ff));
			if (dc_rxeof(sc) == 0) {
				while (dc_rx_resync(sc))
					dc_rxeof(sc);
			}
		}

		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			dc_start_locked(ifp);

		if (status & DC_ISR_BUS_ERR) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			dc_init_locked(sc);
			DC_UNLOCK(sc);
			return;
		}
		status = CSR_READ_4(sc, DC_ISR);
		if (status == 0xFFFFFFFF || (status & DC_INTRS) == 0)
			break;
	}

	/* Re-enable interrupts. */
	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		CSR_WRITE_4(sc, DC_IMR, DC_INTRS);

	DC_UNLOCK(sc);
}
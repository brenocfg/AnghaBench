#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fxp_tx {TYPE_3__* tx_cb; int /*<<< orphan*/ * tx_mbuf; int /*<<< orphan*/  tx_map; } ;
struct TYPE_4__ {struct fxp_tx* tx_list; } ;
struct fxp_softc {scalar_t__ tx_queued; int /*<<< orphan*/  cbl_map; int /*<<< orphan*/  cbl_tag; int /*<<< orphan*/  fxp_txmtag; TYPE_1__ fxp_desc; int /*<<< orphan*/  stat_ch; scalar_t__ watchdog_timer; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_6__ {TYPE_2__* tbd; } ;
struct TYPE_5__ {scalar_t__ tb_addr; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FXP_CSR_PORT ; 
 int /*<<< orphan*/  FXP_CSR_SCB_INTRCNTL ; 
 int FXP_NTXCB ; 
 int /*<<< orphan*/  FXP_PORT_SELECTIVE_RESET ; 
 int /*<<< orphan*/  FXP_SCB_INTR_DISABLE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fxp_update_stats (struct fxp_softc*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fxp_stop(struct fxp_softc *sc)
{
	if_t ifp = sc->ifp;
	struct fxp_tx *txp;
	int i;

	if_setdrvflagbits(ifp, 0, (IFF_DRV_RUNNING | IFF_DRV_OACTIVE));
	sc->watchdog_timer = 0;

	/*
	 * Cancel stats updater.
	 */
	callout_stop(&sc->stat_ch);

	/*
	 * Preserve PCI configuration, configure, IA/multicast
	 * setup and put RU and CU into idle state.
	 */
	CSR_WRITE_4(sc, FXP_CSR_PORT, FXP_PORT_SELECTIVE_RESET);
	DELAY(50);
	/* Disable interrupts. */
	CSR_WRITE_1(sc, FXP_CSR_SCB_INTRCNTL, FXP_SCB_INTR_DISABLE);

	fxp_update_stats(sc);

	/*
	 * Release any xmit buffers.
	 */
	txp = sc->fxp_desc.tx_list;
	for (i = 0; i < FXP_NTXCB; i++) {
		if (txp[i].tx_mbuf != NULL) {
			bus_dmamap_sync(sc->fxp_txmtag, txp[i].tx_map,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->fxp_txmtag, txp[i].tx_map);
			m_freem(txp[i].tx_mbuf);
			txp[i].tx_mbuf = NULL;
			/* clear this to reset csum offload bits */
			txp[i].tx_cb->tbd[0].tb_addr = 0;
		}
	}
	bus_dmamap_sync(sc->cbl_tag, sc->cbl_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	sc->tx_queued = 0;
}
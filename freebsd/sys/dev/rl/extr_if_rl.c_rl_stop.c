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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ ** rl_tx_chain; int /*<<< orphan*/ * rl_tx_dmamap; int /*<<< orphan*/  rl_tx_tag; } ;
struct rl_softc {TYPE_1__ rl_cdata; int /*<<< orphan*/  rl_dev; int /*<<< orphan*/  rl_flags; int /*<<< orphan*/  rl_stat_callout; scalar_t__ rl_watchdog_timer; struct ifnet* rl_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int RL_CMD_RX_ENB ; 
 int RL_CMD_TX_ENB ; 
 int /*<<< orphan*/  RL_COMMAND ; 
 int /*<<< orphan*/  RL_FLAG_LINK ; 
 int /*<<< orphan*/  RL_IMR ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int RL_TIMEOUT ; 
 scalar_t__ RL_TXADDR0 ; 
 int RL_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rl_stop(struct rl_softc *sc)
{
	int			i;
	struct ifnet		*ifp = sc->rl_ifp;

	RL_LOCK_ASSERT(sc);

	sc->rl_watchdog_timer = 0;
	callout_stop(&sc->rl_stat_callout);
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->rl_flags &= ~RL_FLAG_LINK;

	CSR_WRITE_1(sc, RL_COMMAND, 0x00);
	CSR_WRITE_2(sc, RL_IMR, 0x0000);
	for (i = 0; i < RL_TIMEOUT; i++) {
		DELAY(10);
		if ((CSR_READ_1(sc, RL_COMMAND) &
		    (RL_CMD_RX_ENB | RL_CMD_TX_ENB)) == 0)
			break;
	}
	if (i == RL_TIMEOUT)
		device_printf(sc->rl_dev, "Unable to stop Tx/Rx MAC\n");

	/*
	 * Free the TX list buffers.
	 */
	for (i = 0; i < RL_TX_LIST_CNT; i++) {
		if (sc->rl_cdata.rl_tx_chain[i] != NULL) {
			bus_dmamap_sync(sc->rl_cdata.rl_tx_tag,
			    sc->rl_cdata.rl_tx_dmamap[i],
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->rl_cdata.rl_tx_tag,
			    sc->rl_cdata.rl_tx_dmamap[i]);
			m_freem(sc->rl_cdata.rl_tx_chain[i]);
			sc->rl_cdata.rl_tx_chain[i] = NULL;
			CSR_WRITE_4(sc, RL_TXADDR0 + (i * sizeof(uint32_t)),
			    0x0000000);
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * xl_tx_list; int /*<<< orphan*/ * xl_rx_list; } ;
struct TYPE_7__ {TYPE_2__* xl_tx_chain; TYPE_1__* xl_rx_chain; } ;
struct xl_softc {int xl_flags; TYPE_4__ xl_ldata; TYPE_3__ xl_cdata; int /*<<< orphan*/  xl_mtag; int /*<<< orphan*/  xl_tick_callout; int /*<<< orphan*/  xl_fhandle; int /*<<< orphan*/  xl_ftag; scalar_t__ xl_wdog_timer; struct ifnet* xl_ifp; } ;
struct ifnet {int if_drv_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/ * xl_mbuf; int /*<<< orphan*/  xl_map; } ;
struct TYPE_5__ {int /*<<< orphan*/ * xl_mbuf; int /*<<< orphan*/  xl_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int XL_CMD_COAX_STOP ; 
 int XL_CMD_INTR_ACK ; 
 int XL_CMD_INTR_ENB ; 
 int XL_CMD_RX_DISABLE ; 
 int XL_CMD_RX_DISCARD ; 
 int XL_CMD_RX_RESET ; 
 int XL_CMD_STATS_DISABLE ; 
 int XL_CMD_STAT_ENB ; 
 int XL_CMD_TX_DISABLE ; 
 int XL_CMD_TX_RESET ; 
 int /*<<< orphan*/  XL_COMMAND ; 
 int XL_FLAG_FUNCREG ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int XL_RX_LIST_CNT ; 
 int /*<<< orphan*/  XL_RX_LIST_SZ ; 
 int XL_STAT_INTLATCH ; 
 int XL_TX_LIST_CNT ; 
 int /*<<< orphan*/  XL_TX_LIST_SZ ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xl_wait (struct xl_softc*) ; 

__attribute__((used)) static void
xl_stop(struct xl_softc *sc)
{
	int			i;
	struct ifnet		*ifp = sc->xl_ifp;

	XL_LOCK_ASSERT(sc);

	sc->xl_wdog_timer = 0;

	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_RX_DISABLE);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_STATS_DISABLE);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_INTR_ENB);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_RX_DISCARD);
	xl_wait(sc);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_TX_DISABLE);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_COAX_STOP);
	DELAY(800);

#ifdef foo
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_RX_RESET);
	xl_wait(sc);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_TX_RESET);
	xl_wait(sc);
#endif

	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_INTR_ACK|XL_STAT_INTLATCH);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_STAT_ENB|0);
	CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_INTR_ENB|0);
	if (sc->xl_flags & XL_FLAG_FUNCREG)
		bus_space_write_4(sc->xl_ftag, sc->xl_fhandle, 4, 0x8000);

	/* Stop the stats updater. */
	callout_stop(&sc->xl_tick_callout);

	/*
	 * Free data in the RX lists.
	 */
	for (i = 0; i < XL_RX_LIST_CNT; i++) {
		if (sc->xl_cdata.xl_rx_chain[i].xl_mbuf != NULL) {
			bus_dmamap_unload(sc->xl_mtag,
			    sc->xl_cdata.xl_rx_chain[i].xl_map);
			bus_dmamap_destroy(sc->xl_mtag,
			    sc->xl_cdata.xl_rx_chain[i].xl_map);
			m_freem(sc->xl_cdata.xl_rx_chain[i].xl_mbuf);
			sc->xl_cdata.xl_rx_chain[i].xl_mbuf = NULL;
		}
	}
	if (sc->xl_ldata.xl_rx_list != NULL)
		bzero(sc->xl_ldata.xl_rx_list, XL_RX_LIST_SZ);
	/*
	 * Free the TX list buffers.
	 */
	for (i = 0; i < XL_TX_LIST_CNT; i++) {
		if (sc->xl_cdata.xl_tx_chain[i].xl_mbuf != NULL) {
			bus_dmamap_unload(sc->xl_mtag,
			    sc->xl_cdata.xl_tx_chain[i].xl_map);
			bus_dmamap_destroy(sc->xl_mtag,
			    sc->xl_cdata.xl_tx_chain[i].xl_map);
			m_freem(sc->xl_cdata.xl_tx_chain[i].xl_mbuf);
			sc->xl_cdata.xl_tx_chain[i].xl_mbuf = NULL;
		}
	}
	if (sc->xl_ldata.xl_tx_list != NULL)
		bzero(sc->xl_ldata.xl_tx_list, XL_TX_LIST_SZ);

	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
}
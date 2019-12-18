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
struct TYPE_7__ {TYPE_2__* my_tx_chain; TYPE_1__* my_rx_chain; } ;
struct my_softc {TYPE_4__* my_ldata; TYPE_3__ my_cdata; int /*<<< orphan*/  my_watchdog; int /*<<< orphan*/  my_autoneg_timer; struct ifnet* my_ifp; } ;
struct ifnet {int if_drv_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  my_tx_list; int /*<<< orphan*/  my_rx_list; } ;
struct TYPE_6__ {int /*<<< orphan*/ * my_mbuf; } ;
struct TYPE_5__ {int /*<<< orphan*/ * my_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MY_CLRBIT (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MY_IMR ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int MY_RE ; 
 int /*<<< orphan*/  MY_RXLBA ; 
 int MY_RX_LIST_CNT ; 
 int /*<<< orphan*/  MY_TCRRCR ; 
 int MY_TE ; 
 int /*<<< orphan*/  MY_TXLBA ; 
 int MY_TX_LIST_CNT ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
my_stop(struct my_softc * sc)
{
	int    i;
	struct ifnet   *ifp;

	MY_LOCK_ASSERT(sc);
	ifp = sc->my_ifp;

	callout_stop(&sc->my_autoneg_timer);
	callout_stop(&sc->my_watchdog);

	MY_CLRBIT(sc, MY_TCRRCR, (MY_RE | MY_TE));
	CSR_WRITE_4(sc, MY_IMR, 0x00000000);
	CSR_WRITE_4(sc, MY_TXLBA, 0x00000000);
	CSR_WRITE_4(sc, MY_RXLBA, 0x00000000);

	/*
	 * Free data in the RX lists.
	 */
	for (i = 0; i < MY_RX_LIST_CNT; i++) {
		if (sc->my_cdata.my_rx_chain[i].my_mbuf != NULL) {
			m_freem(sc->my_cdata.my_rx_chain[i].my_mbuf);
			sc->my_cdata.my_rx_chain[i].my_mbuf = NULL;
		}
	}
	bzero((char *)&sc->my_ldata->my_rx_list,
	    sizeof(sc->my_ldata->my_rx_list));
	/*
	 * Free the TX list buffers.
	 */
	for (i = 0; i < MY_TX_LIST_CNT; i++) {
		if (sc->my_cdata.my_tx_chain[i].my_mbuf != NULL) {
			m_freem(sc->my_cdata.my_tx_chain[i].my_mbuf);
			sc->my_cdata.my_tx_chain[i].my_mbuf = NULL;
		}
	}
	bzero((char *)&sc->my_ldata->my_tx_list,
	    sizeof(sc->my_ldata->my_tx_list));
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	return;
}
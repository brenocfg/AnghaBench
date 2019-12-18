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
struct TYPE_2__ {struct xl_chain* xl_tx_head; int /*<<< orphan*/ * xl_tx_tail; struct xl_chain* xl_tx_free; } ;
struct xl_softc {TYPE_1__ xl_cdata; scalar_t__ xl_wdog_timer; int /*<<< orphan*/  xl_mtag; struct ifnet* xl_ifp; } ;
struct xl_chain {int /*<<< orphan*/  xl_phys; struct xl_chain* xl_next; int /*<<< orphan*/ * xl_mbuf; int /*<<< orphan*/  xl_map; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_4 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  XL_CMD_DOWN_UNSTALL ; 
 int /*<<< orphan*/  XL_COMMAND ; 
 int /*<<< orphan*/  XL_DMACTL ; 
 int XL_DMACTL_DOWN_STALLED ; 
 int /*<<< orphan*/  XL_DOWNLIST_PTR ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xl_txeof(struct xl_softc *sc)
{
	struct xl_chain		*cur_tx;
	struct ifnet		*ifp = sc->xl_ifp;

	XL_LOCK_ASSERT(sc);

	/*
	 * Go through our tx list and free mbufs for those
	 * frames that have been uploaded. Note: the 3c905B
	 * sets a special bit in the status word to let us
	 * know that a frame has been downloaded, but the
	 * original 3c900/3c905 adapters don't do that.
	 * Consequently, we have to use a different test if
	 * xl_type != XL_TYPE_905B.
	 */
	while (sc->xl_cdata.xl_tx_head != NULL) {
		cur_tx = sc->xl_cdata.xl_tx_head;

		if (CSR_READ_4(sc, XL_DOWNLIST_PTR))
			break;

		sc->xl_cdata.xl_tx_head = cur_tx->xl_next;
		bus_dmamap_sync(sc->xl_mtag, cur_tx->xl_map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->xl_mtag, cur_tx->xl_map);
		m_freem(cur_tx->xl_mbuf);
		cur_tx->xl_mbuf = NULL;
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

		cur_tx->xl_next = sc->xl_cdata.xl_tx_free;
		sc->xl_cdata.xl_tx_free = cur_tx;
	}

	if (sc->xl_cdata.xl_tx_head == NULL) {
		sc->xl_wdog_timer = 0;
		sc->xl_cdata.xl_tx_tail = NULL;
	} else {
		if (CSR_READ_4(sc, XL_DMACTL) & XL_DMACTL_DOWN_STALLED ||
			!CSR_READ_4(sc, XL_DOWNLIST_PTR)) {
			CSR_WRITE_4(sc, XL_DOWNLIST_PTR,
				sc->xl_cdata.xl_tx_head->xl_phys);
			CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_DOWN_UNSTALL);
		}
	}
}
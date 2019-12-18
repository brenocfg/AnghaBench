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
struct mbuf {int dummy; } ;
struct fxp_softc {scalar_t__ tx_queued; int watchdog_timer; int /*<<< orphan*/  cbl_map; int /*<<< orphan*/  cbl_tag; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  FXP_LOCK_ASSERT (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int FXP_NTXCB ; 
 scalar_t__ FXP_NTXCB_HIWAT ; 
 int /*<<< orphan*/  FXP_SCB_COMMAND_CU_RESUME ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fxp_encap (struct fxp_softc*,struct mbuf**) ; 
 int /*<<< orphan*/  fxp_scb_cmd (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_scb_wait (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_txeof (struct fxp_softc*) ; 
 int /*<<< orphan*/  if_bpfmtap (int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* if_dequeue (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 struct fxp_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_prepend (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_start_body(if_t ifp)
{
	struct fxp_softc *sc = if_getsoftc(ifp);
	struct mbuf *mb_head;
	int txqueued;

	FXP_LOCK_ASSERT(sc, MA_OWNED);

	if ((if_getdrvflags(ifp) & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	if (sc->tx_queued > FXP_NTXCB_HIWAT)
		fxp_txeof(sc);
	/*
	 * We're finished if there is nothing more to add to the list or if
	 * we're all filled up with buffers to transmit.
	 * NOTE: One TxCB is reserved to guarantee that fxp_mc_setup() can add
	 *       a NOP command when needed.
	 */
	txqueued = 0;
	while (!if_sendq_empty(ifp) && sc->tx_queued < FXP_NTXCB - 1) {

		/*
		 * Grab a packet to transmit.
		 */
		mb_head = if_dequeue(ifp);
		if (mb_head == NULL)
			break;

		if (fxp_encap(sc, &mb_head)) {
			if (mb_head == NULL)
				break;
			if_sendq_prepend(ifp, mb_head);
			if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
		}
		txqueued++;
		/*
		 * Pass packet to bpf if there is a listener.
		 */
		if_bpfmtap(ifp, mb_head);
	}

	/*
	 * We're finished. If we added to the list, issue a RESUME to get DMA
	 * going again if suspended.
	 */
	if (txqueued > 0) {
		bus_dmamap_sync(sc->cbl_tag, sc->cbl_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		fxp_scb_wait(sc);
		fxp_scb_cmd(sc, FXP_SCB_COMMAND_CU_RESUME);
		/*
		 * Set a 5 second timer just in case we don't hear
		 * from the card again.
		 */
		sc->watchdog_timer = 5;
	}
}
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
struct mbuf {int dummy; } ;
struct bge_softc {int bge_txcnt; int /*<<< orphan*/  bge_tx_prodidx; int /*<<< orphan*/  bge_link; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 int BGE_TX_RING_CNT ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ bge_encap (struct bge_softc*,struct mbuf**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bge_start_tx (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_bpfmtap (int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* if_dequeue (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 struct bge_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_prepend (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_start_locked(if_t ifp)
{
	struct bge_softc *sc;
	struct mbuf *m_head;
	uint32_t prodidx;
	int count;

	sc = if_getsoftc(ifp);
	BGE_LOCK_ASSERT(sc);

	if (!sc->bge_link ||
	    (if_getdrvflags(ifp) & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	prodidx = sc->bge_tx_prodidx;

	for (count = 0; !if_sendq_empty(ifp);) {
		if (sc->bge_txcnt > BGE_TX_RING_CNT - 16) {
			if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
			break;
		}
		m_head = if_dequeue(ifp);
		if (m_head == NULL)
			break;

		/*
		 * Pack the data into the transmit ring. If we
		 * don't have room, set the OACTIVE flag and wait
		 * for the NIC to drain the ring.
		 */
		if (bge_encap(sc, &m_head, &prodidx)) {
			if (m_head == NULL)
				break;
			if_sendq_prepend(ifp, m_head);
			if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
			break;
		}
		++count;

		/*
		 * If there's a BPF listener, bounce a copy of this frame
		 * to him.
		 */
		if_bpfmtap(ifp, m_head);
	}

	if (count > 0)
		bge_start_tx(sc, prodidx);
}
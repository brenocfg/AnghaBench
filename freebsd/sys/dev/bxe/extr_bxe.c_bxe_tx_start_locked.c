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
typedef  scalar_t__ uint16_t ;
struct mbuf {int dummy; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queue_xoff; int /*<<< orphan*/  mbuf_alloc_tx; int /*<<< orphan*/  tx_encap_failures; } ;
struct bxe_fastpath {int /*<<< orphan*/  watchdog_timer; TYPE_1__ eth_q_stats; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_FP_TX_LOCK_ASSERT (struct bxe_fastpath*) ; 
 scalar_t__ BXE_TX_CLEANUP_THRESHOLD ; 
 int /*<<< orphan*/  BXE_TX_TIMEOUT ; 
 int IFF_DRV_OACTIVE ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 scalar_t__ bxe_tx_avail (struct bxe_softc*,struct bxe_fastpath*) ; 
 int /*<<< orphan*/  bxe_tx_encap (struct bxe_fastpath*,struct mbuf**) ; 
 int /*<<< orphan*/  bxe_txeof (struct bxe_softc*,struct bxe_fastpath*) ; 
 struct mbuf* if_dequeue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_etherbpfmtap (int /*<<< orphan*/ ,struct mbuf*) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_prepend (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_tx_start_locked(struct bxe_softc *sc,
                    if_t ifp,
                    struct bxe_fastpath *fp)
{
    struct mbuf *m = NULL;
    int tx_count = 0;
    uint16_t tx_bd_avail;

    BXE_FP_TX_LOCK_ASSERT(fp);

    /* keep adding entries while there are frames to send */
    while (!if_sendq_empty(ifp)) {

        /*
         * check for any frames to send
         * dequeue can still be NULL even if queue is not empty
         */
        m = if_dequeue(ifp);
        if (__predict_false(m == NULL)) {
            break;
        }

        /* the mbuf now belongs to us */
        fp->eth_q_stats.mbuf_alloc_tx++;

        /*
         * Put the frame into the transmit ring. If we don't have room,
         * place the mbuf back at the head of the TX queue, set the
         * OACTIVE flag, and wait for the NIC to drain the chain.
         */
        if (__predict_false(bxe_tx_encap(fp, &m))) {
            fp->eth_q_stats.tx_encap_failures++;
            if (m != NULL) {
                /* mark the TX queue as full and return the frame */
                if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
		if_sendq_prepend(ifp, m);
                fp->eth_q_stats.mbuf_alloc_tx--;
                fp->eth_q_stats.tx_queue_xoff++;
            }

            /* stop looking for more work */
            break;
        }

        /* the frame was enqueued successfully */
        tx_count++;

        /* send a copy of the frame to any BPF listeners. */
        if_etherbpfmtap(ifp, m);

        tx_bd_avail = bxe_tx_avail(sc, fp);

        /* handle any completions if we're running low */
        if (tx_bd_avail < BXE_TX_CLEANUP_THRESHOLD) {
            /* bxe_txeof will set IFF_DRV_OACTIVE appropriately */
            bxe_txeof(sc, fp);
            if (if_getdrvflags(ifp) & IFF_DRV_OACTIVE) {
                break;
            }
        }
    }

    /* all TX packets were dequeued and/or the tx ring is full */
    if (tx_count > 0) {
        /* reset the TX watchdog timeout timer */
        fp->watchdog_timer = BXE_TX_TIMEOUT;
    }
}
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
struct vmbus_chanpkt_hdr {int cph_type; } ;
struct vmbus_channel {int dummy; } ;
struct hn_softc {int dummy; } ;
struct hn_rx_ring {int hn_pktbuf_len; int /*<<< orphan*/  hn_txr; TYPE_1__* hn_ifp; struct vmbus_chanpkt_hdr* hn_pktbuf; } ;
struct TYPE_2__ {struct hn_softc* if_softc; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
#define  VMBUS_CHANPKT_TYPE_COMP 130 
#define  VMBUS_CHANPKT_TYPE_INBAND 129 
#define  VMBUS_CHANPKT_TYPE_RXBUF 128 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  free (struct vmbus_chanpkt_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_chan_rollup (struct hn_rx_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_nvs_handle_comp (struct hn_softc*,struct vmbus_channel*,struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  hn_nvs_handle_notify (struct hn_softc*,struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  hn_nvs_handle_rxbuf (struct hn_rx_ring*,struct vmbus_channel*,struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/  if_printf (TYPE_1__*,char*,int,...) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmbus_chan_recv_pkt (struct vmbus_channel*,struct vmbus_chanpkt_hdr*,int*) ; 

__attribute__((used)) static void
hn_chan_callback(struct vmbus_channel *chan, void *xrxr)
{
	struct hn_rx_ring *rxr = xrxr;
	struct hn_softc *sc = rxr->hn_ifp->if_softc;

	for (;;) {
		struct vmbus_chanpkt_hdr *pkt = rxr->hn_pktbuf;
		int error, pktlen;

		pktlen = rxr->hn_pktbuf_len;
		error = vmbus_chan_recv_pkt(chan, pkt, &pktlen);
		if (__predict_false(error == ENOBUFS)) {
			void *nbuf;
			int nlen;

			/*
			 * Expand channel packet buffer.
			 *
			 * XXX
			 * Use M_WAITOK here, since allocation failure
			 * is fatal.
			 */
			nlen = rxr->hn_pktbuf_len * 2;
			while (nlen < pktlen)
				nlen *= 2;
			nbuf = malloc(nlen, M_DEVBUF, M_WAITOK);

			if_printf(rxr->hn_ifp, "expand pktbuf %d -> %d\n",
			    rxr->hn_pktbuf_len, nlen);

			free(rxr->hn_pktbuf, M_DEVBUF);
			rxr->hn_pktbuf = nbuf;
			rxr->hn_pktbuf_len = nlen;
			/* Retry! */
			continue;
		} else if (__predict_false(error == EAGAIN)) {
			/* No more channel packets; done! */
			break;
		}
		KASSERT(!error, ("vmbus_chan_recv_pkt failed: %d", error));

		switch (pkt->cph_type) {
		case VMBUS_CHANPKT_TYPE_COMP:
			hn_nvs_handle_comp(sc, chan, pkt);
			break;

		case VMBUS_CHANPKT_TYPE_RXBUF:
			hn_nvs_handle_rxbuf(rxr, chan, pkt);
			break;

		case VMBUS_CHANPKT_TYPE_INBAND:
			hn_nvs_handle_notify(sc, pkt);
			break;

		default:
			if_printf(rxr->hn_ifp, "unknown chan pkt %u\n",
			    pkt->cph_type);
			break;
		}
	}
	hn_chan_rollup(rxr, rxr->hn_txr);
}
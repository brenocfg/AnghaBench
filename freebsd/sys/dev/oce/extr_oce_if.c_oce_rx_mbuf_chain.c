#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ frag_size; } ;
struct oce_rq {scalar_t__ islro; TYPE_1__ cfg; int /*<<< orphan*/  pending; TYPE_4__* ring; int /*<<< orphan*/  tag; struct oce_packet_desc* pckts; int /*<<< orphan*/  parent; } ;
struct oce_packet_desc {struct mbuf* mbuf; int /*<<< orphan*/  map; } ;
struct oce_common_cqe_info {scalar_t__ pkt_size; scalar_t__ num_frags; scalar_t__ ip_cksum_pass; int /*<<< orphan*/  ipv6_frame; scalar_t__ l4_cksum_pass; } ;
struct TYPE_7__ {int csum_flags; int csum_data; scalar_t__ len; } ;
struct mbuf {TYPE_2__ m_pkthdr; int /*<<< orphan*/ * m_nextpkt; struct mbuf* m_next; int /*<<< orphan*/  m_flags; scalar_t__ m_len; } ;
struct TYPE_9__ {size_t cidx; size_t pidx; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 scalar_t__ IF_CSUM_ENABLED (TYPE_3__*) ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  RING_GET (TYPE_4__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
oce_rx_mbuf_chain(struct oce_rq *rq, struct oce_common_cqe_info *cqe_info, struct mbuf **m)
{
	POCE_SOFTC sc = (POCE_SOFTC) rq->parent;
        uint32_t i = 0, frag_len = 0;
	uint32_t len = cqe_info->pkt_size;
        struct oce_packet_desc *pd;
        struct mbuf *tail = NULL;

        for (i = 0; i < cqe_info->num_frags; i++) {
                if (rq->ring->cidx == rq->ring->pidx) {
                        device_printf(sc->dev,
                                  "oce_rx_mbuf_chain: Invalid RX completion - Queue is empty\n");
                        return;
                }
                pd = &rq->pckts[rq->ring->cidx];

                bus_dmamap_sync(rq->tag, pd->map, BUS_DMASYNC_POSTWRITE);
                bus_dmamap_unload(rq->tag, pd->map);
		RING_GET(rq->ring, 1);
                rq->pending--;

                frag_len = (len > rq->cfg.frag_size) ? rq->cfg.frag_size : len;
                pd->mbuf->m_len = frag_len;

                if (tail != NULL) {
                        /* additional fragments */
                        pd->mbuf->m_flags &= ~M_PKTHDR;
                        tail->m_next = pd->mbuf;
			if(rq->islro)
                        	tail->m_nextpkt = NULL;
                        tail = pd->mbuf;
                } else {
                        /* first fragment, fill out much of the packet header */
                        pd->mbuf->m_pkthdr.len = len;
			if(rq->islro)
                        	pd->mbuf->m_nextpkt = NULL;
                        pd->mbuf->m_pkthdr.csum_flags = 0;
                        if (IF_CSUM_ENABLED(sc)) {
                                if (cqe_info->l4_cksum_pass) {
                                        if(!cqe_info->ipv6_frame) { /* IPV4 */
                                                pd->mbuf->m_pkthdr.csum_flags |=
                                                        (CSUM_DATA_VALID | CSUM_PSEUDO_HDR);
                                        }else { /* IPV6 frame */
						if(rq->islro) {
                                                	pd->mbuf->m_pkthdr.csum_flags |=
                                                        (CSUM_DATA_VALID | CSUM_PSEUDO_HDR);
						}
                                        }
                                        pd->mbuf->m_pkthdr.csum_data = 0xffff;
                                }
                                if (cqe_info->ip_cksum_pass) {
                                        pd->mbuf->m_pkthdr.csum_flags |=
                                               (CSUM_IP_CHECKED|CSUM_IP_VALID);
                                }
                        }
                        *m = tail = pd->mbuf;
               }
                pd->mbuf = NULL;
                len -= frag_len;
        }

        return;
}
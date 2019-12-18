#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_14__ {int req; int mask; int queue_active; int* send_go; int /*<<< orphan*/  activate; TYPE_6__* req_list; TYPE_2__* info; TYPE_7__* seg_list; int /*<<< orphan*/  dmat; int /*<<< orphan*/  defrag; } ;
struct mxge_slice_state {int /*<<< orphan*/  oerrors; TYPE_5__* sc; TYPE_4__ tx; } ;
struct mxge_pkt_info {scalar_t__ ip_off; scalar_t__ ip_hlen; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int csum_flags; scalar_t__ len; scalar_t__ csum_data; } ;
struct mbuf {int m_flags; TYPE_3__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
typedef  TYPE_4__ mxge_tx_ring_t ;
struct TYPE_11__ {int /*<<< orphan*/  bus_addr; } ;
struct TYPE_15__ {int num_slices; TYPE_1__ zeropad_dma; int /*<<< orphan*/  dev; struct ifnet* ifp; } ;
typedef  TYPE_5__ mxge_softc_t ;
struct TYPE_16__ {int cksum_offset; scalar_t__ flags; int length; int pseudo_hdr_offset; int rdma_count; void* addr_low; void* addr_high; scalar_t__ pad; } ;
typedef  TYPE_6__ mcp_kreq_ether_send_t ;
struct TYPE_17__ {int ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_7__ bus_dma_segment_t ;
struct TYPE_12__ {int flag; struct mbuf* m; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int CSUM_DELAY_DATA ; 
 int CSUM_DELAY_DATA_IPV6 ; 
 int CSUM_TSO ; 
 int EFBIG ; 
 int MXGEFW_FLAGS_ALIGN_ODD ; 
 scalar_t__ MXGEFW_FLAGS_CKSUM ; 
 scalar_t__ MXGEFW_FLAGS_FIRST ; 
 scalar_t__ MXGEFW_FLAGS_NO_TSO ; 
 scalar_t__ MXGEFW_FLAGS_SMALL ; 
 scalar_t__ MXGEFW_SEND_SMALL_SIZE ; 
 int /*<<< orphan*/  MXGE_HIGHPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MXGE_LOWPART_TO_U32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_VLANTAG ; 
 scalar_t__ __predict_false (int) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_7__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 void* htobe16 (int) ; 
 void* htobe32 (int /*<<< orphan*/ ) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mxge_encap_tso (struct mxge_slice_state*,struct mbuf*,int,struct mxge_pkt_info*) ; 
 scalar_t__ mxge_parse_tx (struct mxge_slice_state*,struct mbuf*,struct mxge_pkt_info*) ; 
 int /*<<< orphan*/  mxge_submit_req (TYPE_4__*,TYPE_6__*,int) ; 
 struct mbuf* mxge_vlan_tag_insert (struct mbuf*) ; 
 scalar_t__ ntohl (void*) ; 
 scalar_t__ ntohs (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
mxge_encap(struct mxge_slice_state *ss, struct mbuf *m)
{
	struct mxge_pkt_info pi = {0,0,0,0};
	mxge_softc_t *sc;
	mcp_kreq_ether_send_t *req;
	bus_dma_segment_t *seg;
	struct mbuf *m_tmp;
	struct ifnet *ifp;
	mxge_tx_ring_t *tx;
	int cnt, cum_len, err, i, idx, odd_flag;
	uint16_t pseudo_hdr_offset;
	uint8_t flags, cksum_offset;


	sc = ss->sc;
	ifp = sc->ifp;
	tx = &ss->tx;

#ifdef MXGE_NEW_VLAN_API
	if (m->m_flags & M_VLANTAG) {
		m = mxge_vlan_tag_insert(m);
		if (__predict_false(m == NULL))
			goto drop_without_m;
	}
#endif
	if (m->m_pkthdr.csum_flags &
	    (CSUM_TSO | CSUM_DELAY_DATA | CSUM_DELAY_DATA_IPV6)) {
		if (mxge_parse_tx(ss, m, &pi))
			goto drop;
	}

	/* (try to) map the frame for DMA */
	idx = tx->req & tx->mask;
	err = bus_dmamap_load_mbuf_sg(tx->dmat, tx->info[idx].map,
				      m, tx->seg_list, &cnt,
				      BUS_DMA_NOWAIT);
	if (__predict_false(err == EFBIG)) {
		/* Too many segments in the chain.  Try
		   to defrag */
		m_tmp = m_defrag(m, M_NOWAIT);
		if (m_tmp == NULL) {
			goto drop;
		}
		ss->tx.defrag++;
		m = m_tmp;
		err = bus_dmamap_load_mbuf_sg(tx->dmat,
					      tx->info[idx].map,
					      m, tx->seg_list, &cnt,
					      BUS_DMA_NOWAIT);
	}
	if (__predict_false(err != 0)) {
		device_printf(sc->dev, "bus_dmamap_load_mbuf_sg returned %d"
			      " packet len = %d\n", err, m->m_pkthdr.len);
		goto drop;
	}
	bus_dmamap_sync(tx->dmat, tx->info[idx].map,
			BUS_DMASYNC_PREWRITE);
	tx->info[idx].m = m;

#if IFCAP_TSO4
	/* TSO is different enough, we handle it in another routine */
	if (m->m_pkthdr.csum_flags & (CSUM_TSO)) {
		mxge_encap_tso(ss, m, cnt, &pi);
		return;
	}
#endif

	req = tx->req_list;
	cksum_offset = 0;
	pseudo_hdr_offset = 0;
	flags = MXGEFW_FLAGS_NO_TSO;

	/* checksum offloading? */
	if (m->m_pkthdr.csum_flags &
	    (CSUM_DELAY_DATA | CSUM_DELAY_DATA_IPV6)) {
		/* ensure ip header is in first mbuf, copy
		   it to a scratch buffer if not */
		cksum_offset = pi.ip_off + pi.ip_hlen;
		pseudo_hdr_offset = cksum_offset +  m->m_pkthdr.csum_data;
		pseudo_hdr_offset = htobe16(pseudo_hdr_offset);
		req->cksum_offset = cksum_offset;
		flags |= MXGEFW_FLAGS_CKSUM;
		odd_flag = MXGEFW_FLAGS_ALIGN_ODD;
	} else {
		odd_flag = 0;
	}
	if (m->m_pkthdr.len < MXGEFW_SEND_SMALL_SIZE)
		flags |= MXGEFW_FLAGS_SMALL;

	/* convert segments into a request list */
	cum_len = 0;
	seg = tx->seg_list;
	req->flags = MXGEFW_FLAGS_FIRST;
	for (i = 0; i < cnt; i++) {
		req->addr_low =
			htobe32(MXGE_LOWPART_TO_U32(seg->ds_addr));
		req->addr_high =
			htobe32(MXGE_HIGHPART_TO_U32(seg->ds_addr));
		req->length = htobe16(seg->ds_len);
		req->cksum_offset = cksum_offset;
		if (cksum_offset > seg->ds_len)
			cksum_offset -= seg->ds_len;
		else
			cksum_offset = 0;
		req->pseudo_hdr_offset = pseudo_hdr_offset;
		req->pad = 0; /* complete solid 16-byte block */
		req->rdma_count = 1;
		req->flags |= flags | ((cum_len & 1) * odd_flag);
		cum_len += seg->ds_len;
		seg++;
		req++;
		req->flags = 0;
	}
	req--;
	/* pad runts to 60 bytes */
	if (cum_len < 60) {
		req++;
		req->addr_low =
			htobe32(MXGE_LOWPART_TO_U32(sc->zeropad_dma.bus_addr));
		req->addr_high =
			htobe32(MXGE_HIGHPART_TO_U32(sc->zeropad_dma.bus_addr));
		req->length = htobe16(60 - cum_len);
		req->cksum_offset = 0;
		req->pseudo_hdr_offset = pseudo_hdr_offset;
		req->pad = 0; /* complete solid 16-byte block */
		req->rdma_count = 1;
		req->flags |= flags | ((cum_len & 1) * odd_flag);
		cnt++;
	}

	tx->req_list[0].rdma_count = cnt;
#if 0
	/* print what the firmware will see */
	for (i = 0; i < cnt; i++) {
		printf("%d: addr: 0x%x 0x%x len:%d pso%d,"
		    "cso:%d, flags:0x%x, rdma:%d\n",
		    i, (int)ntohl(tx->req_list[i].addr_high),
		    (int)ntohl(tx->req_list[i].addr_low),
		    (int)ntohs(tx->req_list[i].length),
		    (int)ntohs(tx->req_list[i].pseudo_hdr_offset),
		    tx->req_list[i].cksum_offset, tx->req_list[i].flags,
		    tx->req_list[i].rdma_count);
	}
	printf("--------------\n");
#endif
	tx->info[((cnt - 1) + tx->req) & tx->mask].flag = 1;
	mxge_submit_req(tx, tx->req_list, cnt);
#ifdef IFNET_BUF_RING
	if ((ss->sc->num_slices > 1) && tx->queue_active == 0) {
		/* tell the NIC to start polling this slice */
		*tx->send_go = 1;
		tx->queue_active = 1;
		tx->activate++;
		wmb();
	}
#endif
	return;

drop:
	m_freem(m);
drop_without_m:
	ss->oerrors++;
	return;
}
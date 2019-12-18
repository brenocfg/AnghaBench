#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_udma_q {int /*<<< orphan*/  qid; TYPE_3__* udma; } ;
struct al_eth_pkt {int flags; int tunnel_mode; int l3_proto_idx; int num_of_bufs; TYPE_2__* bufs; TYPE_1__* meta; int /*<<< orphan*/  vlan_mod_del_count; int /*<<< orphan*/  vlan_mod_add_count; int /*<<< orphan*/  source_vlan_count; int /*<<< orphan*/  outer_l3_proto_idx; int /*<<< orphan*/  l4_proto_idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; scalar_t__ addr; } ;
struct TYPE_4__ {int words_valid; int /*<<< orphan*/  outer_l3_len; int /*<<< orphan*/  outer_l3_offset; int /*<<< orphan*/  ts_index; int /*<<< orphan*/  mss_val; int /*<<< orphan*/  l4_header_len; int /*<<< orphan*/  l3_header_offset; int /*<<< orphan*/  l3_header_len; int /*<<< orphan*/  store; } ;

/* Variables and functions */
#define  AL_ETH_PROTO_ID_IPv4 131 
#define  AL_ETH_PROTO_ID_IPv6 130 
#define  AL_ETH_PROTO_ID_TCP 129 
#define  AL_ETH_PROTO_ID_UDP 128 
 int AL_ETH_TUNNEL_NO_UDP ; 
 int AL_ETH_TUNNEL_WITH_UDP ; 
 int AL_ETH_TX_FLAGS_IPV4_L3_CSUM ; 
 int AL_ETH_TX_FLAGS_L2_DIS_FCS ; 
 int AL_ETH_TX_FLAGS_L4_CSUM ; 
 int AL_ETH_TX_FLAGS_L4_PARTIAL_CSUM ; 
 int AL_ETH_TX_FLAGS_TS ; 
 int AL_ETH_TX_FLAGS_TSO ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
al_dump_tx_pkt(struct al_udma_q *tx_dma_q, struct al_eth_pkt *pkt)
{
	const char *tso = (pkt->flags & AL_ETH_TX_FLAGS_TSO) ? "TSO" : "";
	const char *l3_csum = (pkt->flags & AL_ETH_TX_FLAGS_IPV4_L3_CSUM) ? "L3 CSUM" : "";
	const char *l4_csum = (pkt->flags & AL_ETH_TX_FLAGS_L4_CSUM) ?
	  ((pkt->flags & AL_ETH_TX_FLAGS_L4_PARTIAL_CSUM) ? "L4 PARTIAL CSUM" : "L4 FULL CSUM") : "";
	const char *fcs = (pkt->flags & AL_ETH_TX_FLAGS_L2_DIS_FCS) ? "Disable FCS" : "";
	const char *ptp = (pkt->flags & AL_ETH_TX_FLAGS_TS) ? "TX_PTP" : "";
	const char *l3_proto_name = "unknown";
	const char *l4_proto_name = "unknown";
	const char *outer_l3_proto_name = "N/A";
	const char *tunnel_mode = (((pkt->tunnel_mode &
				AL_ETH_TUNNEL_WITH_UDP) == AL_ETH_TUNNEL_WITH_UDP) ?
				"TUNNEL_WITH_UDP" :
				(((pkt->tunnel_mode &
				AL_ETH_TUNNEL_NO_UDP) == AL_ETH_TUNNEL_NO_UDP) ?
				"TUNNEL_NO_UDP" : ""));
	uint32_t total_len = 0;
	int i;

	al_dbg("[%s %d]: flags: %s %s %s %s %s %s\n", tx_dma_q->udma->name, tx_dma_q->qid,
		 tso, l3_csum, l4_csum, fcs, ptp, tunnel_mode);

	switch (pkt->l3_proto_idx) {
	case AL_ETH_PROTO_ID_IPv4:
		l3_proto_name = "IPv4";
		break;
	case AL_ETH_PROTO_ID_IPv6:
		l3_proto_name = "IPv6";
		break;
	default:
		l3_proto_name = "unknown";
		break;
	}

	switch (pkt->l4_proto_idx) {
	case AL_ETH_PROTO_ID_TCP:
		l4_proto_name = "TCP";
		break;
	case AL_ETH_PROTO_ID_UDP:
		l4_proto_name = "UDP";
		break;
	default:
		l4_proto_name = "unknown";
		break;
	}

	switch (pkt->outer_l3_proto_idx) {
	case AL_ETH_PROTO_ID_IPv4:
		outer_l3_proto_name = "IPv4";
		break;
	case AL_ETH_PROTO_ID_IPv6:
		outer_l3_proto_name = "IPv6";
		break;
	default:
		outer_l3_proto_name = "N/A";
		break;
	}

	al_dbg("[%s %d]: L3 proto: %d (%s). L4 proto: %d (%s). Outer_L3 proto: %d (%s). vlan source count %d. mod add %d. mod del %d\n",
			tx_dma_q->udma->name, tx_dma_q->qid, pkt->l3_proto_idx,
			l3_proto_name, pkt->l4_proto_idx, l4_proto_name,
			pkt->outer_l3_proto_idx, outer_l3_proto_name,
			pkt->source_vlan_count, pkt->vlan_mod_add_count,
			pkt->vlan_mod_del_count);

	if (pkt->meta) {
		const char * store = pkt->meta->store ? "Yes" : "No";
		const char *ptp_val = (pkt->flags & AL_ETH_TX_FLAGS_TS) ? "Yes" : "No";

		al_dbg("[%s %d]: tx pkt with meta data. words valid %x\n",
			tx_dma_q->udma->name, tx_dma_q->qid,
			pkt->meta->words_valid);
		al_dbg("[%s %d]: meta: store to cache %s. l3 hdr len %d. l3 hdr offset %d. "
			"l4 hdr len %d. mss val %d ts_index %d ts_val:%s\n"
			, tx_dma_q->udma->name, tx_dma_q->qid, store,
			pkt->meta->l3_header_len, pkt->meta->l3_header_offset,
			pkt->meta->l4_header_len, pkt->meta->mss_val,
			pkt->meta->ts_index, ptp_val);
		al_dbg("outer_l3_hdr_offset %d. outer_l3_len %d.\n",
			pkt->meta->outer_l3_offset, pkt->meta->outer_l3_len);
	}

	al_dbg("[%s %d]: num of bufs: %d\n", tx_dma_q->udma->name, tx_dma_q->qid,
		pkt->num_of_bufs);
	for (i = 0; i < pkt->num_of_bufs; i++) {
		al_dbg("eth [%s %d]: buf[%d]: len 0x%08x. address 0x%016llx\n", tx_dma_q->udma->name, tx_dma_q->qid,
			i, pkt->bufs[i].len, (unsigned long long)pkt->bufs[i].addr);
		total_len += pkt->bufs[i].len;
	}
	al_dbg("[%s %d]: total len: 0x%08x\n", tx_dma_q->udma->name, tx_dma_q->qid, total_len);

}
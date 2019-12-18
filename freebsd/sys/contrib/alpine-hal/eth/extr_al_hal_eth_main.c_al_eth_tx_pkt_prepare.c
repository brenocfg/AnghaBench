#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  buf_ptr; void* meta_ctrl; void* len_ctrl; } ;
struct TYPE_8__ {void* meta2; void* meta1; void* meta_ctrl; void* len_ctrl; } ;
union al_udma_desc {TYPE_2__ tx; TYPE_1__ tx_meta; } ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct al_udma_q {scalar_t__ adapter_rev_id; int /*<<< orphan*/  qid; TYPE_4__* udma; } ;
struct al_eth_pkt {scalar_t__ flags; scalar_t__ num_of_bufs; scalar_t__ l3_proto_idx; scalar_t__ l4_proto_idx; scalar_t__ source_vlan_count; scalar_t__ vlan_mod_add_count; scalar_t__ vlan_mod_del_count; scalar_t__ vlan_mod_v1_ether_sel; scalar_t__ vlan_mod_v1_vid_sel; scalar_t__ vlan_mod_v1_pbits_sel; scalar_t__ tunnel_mode; scalar_t__ outer_l3_proto_idx; TYPE_3__* bufs; TYPE_6__* ext_meta_data; TYPE_5__* meta; scalar_t__ tgtid; } ;
struct TYPE_13__ {int /*<<< orphan*/ * tx_crypto_data; } ;
struct TYPE_12__ {int words_valid; scalar_t__ vlan1_cfi_sel; int vlan2_vid_sel; int vlan2_cfi_sel; int vlan2_pbits_sel; int vlan2_ether_sel; scalar_t__ vlan1_new_vid; int vlan1_new_cfi; int vlan1_new_pbits; int vlan2_new_vid; int vlan2_new_cfi; int vlan2_new_pbits; scalar_t__ l3_header_len; scalar_t__ l3_header_offset; int l4_header_len; scalar_t__ ts_index; int mss_val; int outer_l3_offset; int outer_l3_len; scalar_t__ store; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {scalar_t__ len; int addr; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_PROTO_ID_IPv4 ; 
 scalar_t__ AL_ETH_REV_ID_2 ; 
 scalar_t__ AL_ETH_TX_FLAGS_ENCRYPT ; 
 scalar_t__ AL_ETH_TX_FLAGS_INT ; 
 int AL_ETH_TX_FLAGS_L4_CSUM ; 
 int AL_ETH_TX_FLAGS_L4_PARTIAL_CSUM ; 
 scalar_t__ AL_ETH_TX_FLAGS_NO_SNOOP ; 
 int AL_ETH_TX_FLAGS_TS ; 
 int AL_ETH_TX_FLAGS_TSO ; 
 scalar_t__ AL_ETH_TX_L4_PROTO_IDX_SHIFT ; 
 scalar_t__ AL_ETH_TX_META_L3_LEN_MASK ; 
 scalar_t__ AL_ETH_TX_META_L3_OFF_MASK ; 
 scalar_t__ AL_ETH_TX_META_L3_OFF_SHIFT ; 
 int AL_ETH_TX_META_MSS_LSB_VAL_SHIFT ; 
 scalar_t__ AL_ETH_TX_META_MSS_MSB_TS_VAL_SHIFT ; 
 int AL_ETH_TX_META_OUTER_L3_LEN_MASK ; 
 int AL_ETH_TX_META_OUTER_L3_LEN_SHIFT ; 
 scalar_t__ AL_ETH_TX_META_OUTER_L3_OFF_HIGH_MASK ; 
 scalar_t__ AL_ETH_TX_META_OUTER_L3_OFF_HIGH_SHIFT ; 
 scalar_t__ AL_ETH_TX_META_OUTER_L3_OFF_LOW_MASK ; 
 scalar_t__ AL_ETH_TX_META_OUTER_L3_OFF_LOW_SHIFT ; 
 scalar_t__ AL_ETH_TX_META_STORE ; 
 int AL_ETH_TX_OUTER_L3_PROTO_SHIFT ; 
 scalar_t__ AL_ETH_TX_PKT_META_FLAGS ; 
 scalar_t__ AL_ETH_TX_PKT_UDMA_FLAGS ; 
 scalar_t__ AL_ETH_TX_SRC_VLAN_CNT_SHIFT ; 
 scalar_t__ AL_ETH_TX_TUNNEL_MODE_SHIFT ; 
 scalar_t__ AL_ETH_TX_VLAN_MOD_ADD_SHIFT ; 
 scalar_t__ AL_ETH_TX_VLAN_MOD_DEL_SHIFT ; 
 scalar_t__ AL_ETH_TX_VLAN_MOD_E_SEL_SHIFT ; 
 scalar_t__ AL_ETH_TX_VLAN_MOD_PBIT_SEL_SHIFT ; 
 scalar_t__ AL_ETH_TX_VLAN_MOD_VID_SEL_SHIFT ; 
 scalar_t__ AL_M2S_DESC_CONCAT ; 
 scalar_t__ AL_M2S_DESC_FIRST ; 
 scalar_t__ AL_M2S_DESC_LAST ; 
 scalar_t__ AL_M2S_DESC_LEN_MASK ; 
 scalar_t__ AL_M2S_DESC_META_DATA ; 
 scalar_t__ AL_M2S_DESC_RING_ID_SHIFT ; 
 int AL_UDMA_DESC_TGTID_SHIFT ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  al_dump_tx_desc (union al_udma_desc*) ; 
 int /*<<< orphan*/  al_dump_tx_pkt (struct al_udma_q*,struct al_eth_pkt*) ; 
 int /*<<< orphan*/  al_eth_ext_metadata_create (struct al_udma_q*,scalar_t__*,TYPE_6__*) ; 
 scalar_t__ al_eth_ext_metadata_needed_descs (TYPE_6__*) ; 
 scalar_t__ al_udma_available_get (struct al_udma_q*) ; 
 union al_udma_desc* al_udma_desc_get (struct al_udma_q*) ; 
 scalar_t__ al_udma_ring_id_get (struct al_udma_q*) ; 
 void* swap32_to_le (scalar_t__) ; 
 int /*<<< orphan*/  swap64_to_le (int) ; 
 scalar_t__ unlikely (int) ; 

int al_eth_tx_pkt_prepare(struct al_udma_q *tx_dma_q, struct al_eth_pkt *pkt)
{
	union al_udma_desc *tx_desc;
	uint32_t tx_descs;
	uint32_t flags = AL_M2S_DESC_FIRST |
			AL_M2S_DESC_CONCAT |
			(pkt->flags & AL_ETH_TX_FLAGS_INT);
	uint64_t tgtid = ((uint64_t)pkt->tgtid) << AL_UDMA_DESC_TGTID_SHIFT;
	uint32_t meta_ctrl;
	uint32_t ring_id;
	int buf_idx;

	al_dbg("[%s %d]: new tx pkt\n", tx_dma_q->udma->name, tx_dma_q->qid);

	al_dump_tx_pkt(tx_dma_q, pkt);

	tx_descs = pkt->num_of_bufs;
	if (pkt->meta) {
		tx_descs += 1;
	}
#ifdef AL_ETH_EX
	al_assert((pkt->ext_meta_data == NULL) || (tx_dma_q->adapter_rev_id > AL_ETH_REV_ID_2));

	tx_descs += al_eth_ext_metadata_needed_descs(pkt->ext_meta_data);
	al_dbg("[%s %d]: %d Descriptors: ext_meta (%d). meta (%d). buffer (%d) ",
			tx_dma_q->udma->name, tx_dma_q->qid, tx_descs,
			al_eth_ext_metadata_needed_descs(pkt->ext_meta_data),
			(pkt->meta != NULL), pkt->num_of_bufs);
#endif

	if (unlikely(al_udma_available_get(tx_dma_q) < tx_descs)) {
		al_dbg("[%s %d]: failed to allocate (%d) descriptors",
			 tx_dma_q->udma->name, tx_dma_q->qid, tx_descs);
		return 0;
	}

#ifdef AL_ETH_EX
	if (pkt->ext_meta_data != NULL) {
		al_eth_ext_metadata_create(tx_dma_q, &flags, pkt->ext_meta_data);
		flags &= ~(AL_M2S_DESC_FIRST | AL_ETH_TX_FLAGS_INT);
	}
#endif

	if (pkt->meta) {
		uint32_t meta_word_0 = 0;
		uint32_t meta_word_1 = 0;
		uint32_t meta_word_2 = 0;
		uint32_t meta_word_3 = 0;

		meta_word_0 |= flags | AL_M2S_DESC_META_DATA;
		meta_word_0 &=  ~AL_M2S_DESC_CONCAT;
		flags &= ~(AL_M2S_DESC_FIRST | AL_ETH_TX_FLAGS_INT);

		tx_desc = al_udma_desc_get(tx_dma_q);
		/* get ring id, and clear FIRST and Int flags */
		ring_id = al_udma_ring_id_get(tx_dma_q) <<
			AL_M2S_DESC_RING_ID_SHIFT;

		meta_word_0 |= ring_id;
		meta_word_0 |= pkt->meta->words_valid << 12;

		if (pkt->meta->store)
			meta_word_0 |= AL_ETH_TX_META_STORE;

		if (pkt->meta->words_valid & 1) {
			meta_word_0 |= pkt->meta->vlan1_cfi_sel;
			meta_word_0 |= pkt->meta->vlan2_vid_sel << 2;
			meta_word_0 |= pkt->meta->vlan2_cfi_sel << 4;
			meta_word_0 |= pkt->meta->vlan2_pbits_sel << 6;
			meta_word_0 |= pkt->meta->vlan2_ether_sel << 8;
		}

		if (pkt->meta->words_valid & 2) {
			meta_word_1 = pkt->meta->vlan1_new_vid;
			meta_word_1 |= pkt->meta->vlan1_new_cfi << 12;
			meta_word_1 |= pkt->meta->vlan1_new_pbits << 13;
			meta_word_1 |= pkt->meta->vlan2_new_vid << 16;
			meta_word_1 |= pkt->meta->vlan2_new_cfi << 28;
			meta_word_1 |= pkt->meta->vlan2_new_pbits << 29;
		}

		if (pkt->meta->words_valid & 4) {
			uint32_t l3_offset;

			meta_word_2 = pkt->meta->l3_header_len & AL_ETH_TX_META_L3_LEN_MASK;
			meta_word_2 |= (pkt->meta->l3_header_offset & AL_ETH_TX_META_L3_OFF_MASK) <<
				AL_ETH_TX_META_L3_OFF_SHIFT;
			meta_word_2 |= (pkt->meta->l4_header_len & 0x3f) << 16;

			if (unlikely(pkt->flags & AL_ETH_TX_FLAGS_TS))
				meta_word_0 |= pkt->meta->ts_index <<
					AL_ETH_TX_META_MSS_MSB_TS_VAL_SHIFT;
			else
				meta_word_0 |= (((pkt->meta->mss_val & 0x3c00) >> 10)
						<< AL_ETH_TX_META_MSS_MSB_TS_VAL_SHIFT);
			meta_word_2 |= ((pkt->meta->mss_val & 0x03ff)
					<< AL_ETH_TX_META_MSS_LSB_VAL_SHIFT);

			/*
			 * move from bytes to multiplication of 2 as the HW
			 * expect to get it
			 */
			l3_offset = (pkt->meta->outer_l3_offset >> 1);

			meta_word_0 |=
				(((l3_offset &
				   AL_ETH_TX_META_OUTER_L3_OFF_HIGH_MASK) >> 3)
				   << AL_ETH_TX_META_OUTER_L3_OFF_HIGH_SHIFT);

			meta_word_3 |=
				((l3_offset &
				   AL_ETH_TX_META_OUTER_L3_OFF_LOW_MASK)
				   << AL_ETH_TX_META_OUTER_L3_OFF_LOW_SHIFT);

			/*
			 * shift right 2 bits to work in multiplication of 4
			 * as the HW expect to get it
			 */
			meta_word_3 |=
				(((pkt->meta->outer_l3_len >> 2) &
				   AL_ETH_TX_META_OUTER_L3_LEN_MASK)
				   << AL_ETH_TX_META_OUTER_L3_LEN_SHIFT);
		}

		tx_desc->tx_meta.len_ctrl = swap32_to_le(meta_word_0);
		tx_desc->tx_meta.meta_ctrl = swap32_to_le(meta_word_1);
		tx_desc->tx_meta.meta1 = swap32_to_le(meta_word_2);
		tx_desc->tx_meta.meta2 = swap32_to_le(meta_word_3);
		al_dump_tx_desc(tx_desc);
	}

	meta_ctrl = pkt->flags & AL_ETH_TX_PKT_META_FLAGS;

	/* L4_PARTIAL_CSUM without L4_CSUM is invalid option  */
	al_assert((pkt->flags & (AL_ETH_TX_FLAGS_L4_CSUM|AL_ETH_TX_FLAGS_L4_PARTIAL_CSUM)) !=
		  AL_ETH_TX_FLAGS_L4_PARTIAL_CSUM);

	/* TSO packets can't have Timestamp enabled */
	al_assert((pkt->flags & (AL_ETH_TX_FLAGS_TSO|AL_ETH_TX_FLAGS_TS)) !=
		  (AL_ETH_TX_FLAGS_TSO|AL_ETH_TX_FLAGS_TS));

	meta_ctrl |= pkt->l3_proto_idx;
	meta_ctrl |= pkt->l4_proto_idx << AL_ETH_TX_L4_PROTO_IDX_SHIFT;
	meta_ctrl |= pkt->source_vlan_count << AL_ETH_TX_SRC_VLAN_CNT_SHIFT;
	meta_ctrl |= pkt->vlan_mod_add_count << AL_ETH_TX_VLAN_MOD_ADD_SHIFT;
	meta_ctrl |= pkt->vlan_mod_del_count << AL_ETH_TX_VLAN_MOD_DEL_SHIFT;
	meta_ctrl |= pkt->vlan_mod_v1_ether_sel << AL_ETH_TX_VLAN_MOD_E_SEL_SHIFT;
	meta_ctrl |= pkt->vlan_mod_v1_vid_sel << AL_ETH_TX_VLAN_MOD_VID_SEL_SHIFT;
	meta_ctrl |= pkt->vlan_mod_v1_pbits_sel << AL_ETH_TX_VLAN_MOD_PBIT_SEL_SHIFT;

#ifdef AL_ETH_EX
	if ((pkt->ext_meta_data != NULL) && (pkt->ext_meta_data->tx_crypto_data != NULL))
		meta_ctrl |= AL_ETH_TX_FLAGS_ENCRYPT;
#endif

	meta_ctrl |= pkt->tunnel_mode << AL_ETH_TX_TUNNEL_MODE_SHIFT;
	if (pkt->outer_l3_proto_idx == AL_ETH_PROTO_ID_IPv4)
		meta_ctrl |= 1 << AL_ETH_TX_OUTER_L3_PROTO_SHIFT;

	flags |= pkt->flags & AL_ETH_TX_PKT_UDMA_FLAGS;
	for(buf_idx = 0; buf_idx < pkt->num_of_bufs; buf_idx++ ) {
		uint32_t flags_len = flags;

		tx_desc = al_udma_desc_get(tx_dma_q);
		/* get ring id, and clear FIRST and Int flags */
		ring_id = al_udma_ring_id_get(tx_dma_q) <<
			AL_M2S_DESC_RING_ID_SHIFT;

		flags_len |= ring_id;

		if (buf_idx == (pkt->num_of_bufs - 1))
			flags_len |= AL_M2S_DESC_LAST;

		/* clear First and Int flags */
		flags &= AL_ETH_TX_FLAGS_NO_SNOOP;
		flags |= AL_M2S_DESC_CONCAT;

		flags_len |= pkt->bufs[buf_idx].len & AL_M2S_DESC_LEN_MASK;
		tx_desc->tx.len_ctrl = swap32_to_le(flags_len);
		if (buf_idx == 0)
			tx_desc->tx.meta_ctrl = swap32_to_le(meta_ctrl);
		tx_desc->tx.buf_ptr = swap64_to_le(
			pkt->bufs[buf_idx].addr | tgtid);
		al_dump_tx_desc(tx_desc);
	}

	al_dbg("[%s %d]: pkt descriptors written into the tx queue. descs num (%d)\n",
		tx_dma_q->udma->name, tx_dma_q->qid, tx_descs);

	return tx_descs;
}
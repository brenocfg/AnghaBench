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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  tx_pkt ;
struct unaligned_opaque_data {scalar_t__ first_mpa_offset; } ;
struct ecore_ll2_tx_pkt_info {int num_of_bds; int l4_hdr_offset_w; int first_frag_len; int enable_ip_cksum; int enable_l4_cksum; int calc_ip_len; TYPE_3__* cookie; scalar_t__ first_frag; int /*<<< orphan*/  vlan; int /*<<< orphan*/  tx_dest; } ;
struct ecore_iwarp_ll2_buff {scalar_t__ data_phys_addr; } ;
struct ecore_iwarp_fpdu {int pkt_hdr_size; scalar_t__ fpdu_length; scalar_t__ incomplete_bytes; scalar_t__ mpa_frag_len; scalar_t__ mpa_frag; TYPE_3__* mpa_buf; scalar_t__ pkt_hdr; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum ecore_iwarp_mpa_pkt_type { ____Placeholder_ecore_iwarp_mpa_pkt_type } ecore_iwarp_mpa_pkt_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {struct ecore_iwarp_ll2_buff* piggy_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  ll2_mpa_handle; } ;
struct TYPE_5__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,unsigned long,int,unsigned long,scalar_t__,scalar_t__,scalar_t__,TYPE_3__*,int) ; 
 int ECORE_IWARP_MPA_PKT_UNALIGNED ; 
 int /*<<< orphan*/  ECORE_LL2_TX_DEST_LB ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  IWARP_LL2_ALIGNED_TX_QUEUE ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_ll2_tx_pkt_info*,int) ; 
 int ecore_ll2_prepare_tx_packet (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_ll2_tx_pkt_info*,int) ; 
 int ecore_ll2_set_fragment_of_tx_packet (struct ecore_hwfn*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_iwarp_send_fpdu(struct ecore_hwfn *p_hwfn,
		      struct ecore_iwarp_fpdu *fpdu,
		      struct unaligned_opaque_data *curr_pkt,
		      struct ecore_iwarp_ll2_buff *buf,
		      u16 tcp_payload_size,
		      enum ecore_iwarp_mpa_pkt_type pkt_type)
{
	struct ecore_ll2_tx_pkt_info tx_pkt;
	enum _ecore_status_t rc;
	u8 ll2_handle;

	OSAL_MEM_ZERO(&tx_pkt, sizeof(tx_pkt));

	tx_pkt.num_of_bds = (pkt_type == ECORE_IWARP_MPA_PKT_UNALIGNED) ? 3 : 2;
	tx_pkt.tx_dest = ECORE_LL2_TX_DEST_LB;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2;

	/* Send the mpa_buf only with the last fpdu (in case of packed) */
	if ((pkt_type == ECORE_IWARP_MPA_PKT_UNALIGNED) ||
	    (tcp_payload_size <= fpdu->fpdu_length))
		tx_pkt.cookie = fpdu->mpa_buf;

	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	tx_pkt.enable_ip_cksum = true;
	tx_pkt.enable_l4_cksum = true;
	tx_pkt.calc_ip_len = true;
	/* vlan overload with enum iwarp_ll2_tx_queues */
	tx_pkt.vlan = IWARP_LL2_ALIGNED_TX_QUEUE;

	/* special case of unaligned packet and not packed, need to send
	 * both buffers as cookie to release.
	 */
	if (tcp_payload_size == fpdu->incomplete_bytes) {
		fpdu->mpa_buf->piggy_buf = buf;
	}

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	rc = ecore_ll2_prepare_tx_packet(p_hwfn,
					 ll2_handle,
					 &tx_pkt, true);
	if (rc)
		goto err;

	rc = ecore_ll2_set_fragment_of_tx_packet(p_hwfn, ll2_handle,
						 fpdu->mpa_frag,
						 fpdu->mpa_frag_len);
	if (rc)
		goto err;

	if (fpdu->incomplete_bytes) {
		rc = ecore_ll2_set_fragment_of_tx_packet(
			p_hwfn, ll2_handle,
			buf->data_phys_addr + curr_pkt->first_mpa_offset,
			fpdu->incomplete_bytes);

		if (rc)
			goto err;
	}

err:
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
		   "MPA_ALIGN: Sent FPDU num_bds=%d [%lx, 0x%x], [0x%lx, 0x%x], [0x%lx, 0x%x] (cookie %p) rc=%d\n",
		   tx_pkt.num_of_bds, (long unsigned int)tx_pkt.first_frag,
		   tx_pkt.first_frag_len, (long unsigned int)fpdu->mpa_frag,
		   fpdu->mpa_frag_len, (long unsigned int)buf->data_phys_addr +
		   curr_pkt->first_mpa_offset, fpdu->incomplete_bytes,
		   tx_pkt.cookie, rc);

	return rc;
}
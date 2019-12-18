#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tx_pkt ;
struct ecore_ll2_tx_pkt_info {int num_of_bds; int l4_hdr_offset_w; int first_frag_len; scalar_t__ first_frag; struct ecore_iwarp_ll2_buff* cookie; int /*<<< orphan*/  tx_dest; } ;
struct ecore_iwarp_ll2_buff {int /*<<< orphan*/  piggy_buf; } ;
struct ecore_iwarp_fpdu {int pkt_hdr_size; scalar_t__ pkt_hdr; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_mpa_handle; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ECORE_LL2_TX_DEST_DROP ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_ll2_tx_pkt_info*,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int ecore_ll2_prepare_tx_packet (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_ll2_tx_pkt_info*,int) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_iwarp_recycle_pkt(struct ecore_hwfn *p_hwfn,
			struct ecore_iwarp_fpdu *fpdu,
			struct ecore_iwarp_ll2_buff *buf)
{
	struct ecore_ll2_tx_pkt_info tx_pkt;
	enum _ecore_status_t rc;
	u8 ll2_handle;

	OSAL_MEM_ZERO(&tx_pkt, sizeof(tx_pkt));
	tx_pkt.num_of_bds = 1;
	tx_pkt.tx_dest = ECORE_LL2_TX_DEST_DROP;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2;
	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	buf->piggy_buf = OSAL_NULL;
	tx_pkt.cookie = buf;

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	rc = ecore_ll2_prepare_tx_packet(p_hwfn,
					 ll2_handle,
					 &tx_pkt, true);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
		   "MPA_ALIGN: send drop tx packet [%lx, 0x%x], buf=%p, rc=%d\n",
		   (long unsigned int)tx_pkt.first_frag,
		   tx_pkt.first_frag_len, buf, rc);

	if (rc)
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Can't drop packet rc=%d\n", rc);

	return rc;
}
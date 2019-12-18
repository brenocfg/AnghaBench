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
struct unaligned_opaque_data {int cid; int first_mpa_offset; } ;
struct ecore_iwarp_ll2_mpa_buf {int placement_offset; int tcp_payload_len; struct unaligned_opaque_data data; struct ecore_iwarp_ll2_buff* ll2_buf; } ;
struct ecore_iwarp_ll2_buff {scalar_t__ data; } ;
struct ecore_iwarp_fpdu {int fpdu_length; int incomplete_bytes; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum ecore_iwarp_mpa_pkt_type { ____Placeholder_ecore_iwarp_mpa_pkt_type } ecore_iwarp_mpa_pkt_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_mpa_handle; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_IWARP_IS_RIGHT_EDGE (struct unaligned_opaque_data*) ; 
#define  ECORE_IWARP_MPA_PKT_PACKED 130 
#define  ECORE_IWARP_MPA_PKT_PARTIAL 129 
#define  ECORE_IWARP_MPA_PKT_UNALIGNED 128 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_iwarp_fpdu*,int) ; 
 int ecore_iwarp_copy_fpdu (struct ecore_hwfn*,struct ecore_iwarp_fpdu*,struct unaligned_opaque_data*,struct ecore_iwarp_ll2_buff*,int) ; 
 struct ecore_iwarp_fpdu* ecore_iwarp_get_curr_fpdu (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  ecore_iwarp_init_fpdu (struct ecore_iwarp_ll2_buff*,struct ecore_iwarp_fpdu*,struct unaligned_opaque_data*,int,int) ; 
 int ecore_iwarp_ll2_post_rx (struct ecore_hwfn*,struct ecore_iwarp_ll2_buff*,int /*<<< orphan*/ ) ; 
 int ecore_iwarp_mpa_classify (struct ecore_hwfn*,struct ecore_iwarp_fpdu*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_iwarp_mpa_print_tcp_seq (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 int ecore_iwarp_send_fpdu (struct ecore_hwfn*,struct ecore_iwarp_fpdu*,struct unaligned_opaque_data*,struct ecore_iwarp_ll2_buff*,int,int) ; 
 int /*<<< orphan*/  ecore_iwarp_update_fpdu_length (struct ecore_hwfn*,struct ecore_iwarp_fpdu*,int /*<<< orphan*/ *) ; 
 int ecore_iwarp_win_right_edge (struct ecore_hwfn*,struct ecore_iwarp_fpdu*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_iwarp_process_mpa_pkt(struct ecore_hwfn *p_hwfn,
			    struct ecore_iwarp_ll2_mpa_buf *mpa_buf)
{
	struct ecore_iwarp_ll2_buff *buf = mpa_buf->ll2_buf;
	enum ecore_iwarp_mpa_pkt_type pkt_type;
	struct unaligned_opaque_data *curr_pkt = &mpa_buf->data;
	struct ecore_iwarp_fpdu *fpdu;
	u8 *mpa_data;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	ecore_iwarp_mpa_print_tcp_seq(
		p_hwfn, (u8 *)(buf->data) + mpa_buf->placement_offset);

	fpdu = ecore_iwarp_get_curr_fpdu(p_hwfn, curr_pkt->cid & 0xffff);
	if (!fpdu) {/* something corrupt with cid, post rx back */
		DP_ERR(p_hwfn, "Invalid cid, drop and post back to rx cid=%x\n",
		       curr_pkt->cid);
		rc = ecore_iwarp_ll2_post_rx(
			p_hwfn, buf, p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle);

		if (rc) { /* not much we can do here except log and free */
			DP_ERR(p_hwfn, "Post rx buffer failed\n");

			/* we don't expect any failures from rx, not even
			 * busy since we allocate #bufs=#descs
			 */
			rc = ECORE_UNKNOWN_ERROR;
		}
		return rc;
	}

	do {
		mpa_data = ((u8 *)(buf->data) + curr_pkt->first_mpa_offset);

		pkt_type = ecore_iwarp_mpa_classify(p_hwfn, fpdu,
						    mpa_buf->tcp_payload_len,
						    mpa_data);

		switch (pkt_type) {
		case ECORE_IWARP_MPA_PKT_PARTIAL:
			ecore_iwarp_init_fpdu(buf, fpdu,
					      curr_pkt,
					      mpa_buf->tcp_payload_len,
					      mpa_buf->placement_offset);

			if (!ECORE_IWARP_IS_RIGHT_EDGE(curr_pkt)) {
				mpa_buf->tcp_payload_len = 0;
				break;
			}

			rc = ecore_iwarp_win_right_edge(p_hwfn, fpdu);

			if (rc) {
				DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
					   "Can't send FPDU:reset rc=%d\n", rc);
				OSAL_MEM_ZERO(fpdu, sizeof(*fpdu));
				break;
			}

			mpa_buf->tcp_payload_len = 0;
			break;
		case ECORE_IWARP_MPA_PKT_PACKED:
			if (fpdu->fpdu_length == 8) {
				DP_ERR(p_hwfn, "SUSPICIOUS fpdu_length = 0x%x: assuming bug...aborting this packet...\n",
				       fpdu->fpdu_length);
				mpa_buf->tcp_payload_len = 0;
				break;
			}

			ecore_iwarp_init_fpdu(buf, fpdu,
					      curr_pkt,
					      mpa_buf->tcp_payload_len,
					      mpa_buf->placement_offset);

			rc = ecore_iwarp_send_fpdu(p_hwfn, fpdu, curr_pkt, buf,
						   mpa_buf->tcp_payload_len,
						   pkt_type);
			if (rc) {
				DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
					   "Can't send FPDU:reset rc=%d\n", rc);
				OSAL_MEM_ZERO(fpdu, sizeof(*fpdu));
				break;
			}
			mpa_buf->tcp_payload_len -= fpdu->fpdu_length;
			curr_pkt->first_mpa_offset += fpdu->fpdu_length;
			break;
		case ECORE_IWARP_MPA_PKT_UNALIGNED:
			ecore_iwarp_update_fpdu_length(p_hwfn, fpdu, mpa_data);
			if (mpa_buf->tcp_payload_len < fpdu->incomplete_bytes) {
				/* special handling of fpdu split over more
				 * than 2 segments
				 */
				if (ECORE_IWARP_IS_RIGHT_EDGE(curr_pkt)) {
					rc = ecore_iwarp_win_right_edge(p_hwfn,
									fpdu);
					/* packet will be re-processed later */
					if (rc)
						return rc;
				}

				rc = ecore_iwarp_copy_fpdu(
					p_hwfn, fpdu, curr_pkt,
					buf, mpa_buf->tcp_payload_len);

				/* packet will be re-processed later */
				if (rc)
					return rc;

				mpa_buf->tcp_payload_len = 0;

				break;
			}

			rc = ecore_iwarp_send_fpdu(p_hwfn, fpdu, curr_pkt, buf,
						   mpa_buf->tcp_payload_len,
						   pkt_type);
			if (rc) {
				DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
					   "Can't send FPDU:delay rc=%d\n", rc);
				/* don't reset fpdu -> we need it for next
				 * classify
				 */
				break;
			}
			mpa_buf->tcp_payload_len -= fpdu->incomplete_bytes;
			curr_pkt->first_mpa_offset += fpdu->incomplete_bytes;
			/* The framed PDU was sent - no more incomplete bytes */
			fpdu->incomplete_bytes = 0;
			break;
		}

	} while (mpa_buf->tcp_payload_len && !rc);

	return rc;
}
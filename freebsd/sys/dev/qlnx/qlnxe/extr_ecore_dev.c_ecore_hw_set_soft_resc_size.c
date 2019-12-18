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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ BDQ_NUM_RESOURCES ; 
#define  ECORE_BDQ 131 
 int ECORE_IS_AH (int /*<<< orphan*/ ) ; 
#define  ECORE_LL2_QUEUE 130 
 int ECORE_MAX_RESC ; 
 int ECORE_NOTIMPL ; 
#define  ECORE_RDMA_CNQ_RAM 129 
#define  ECORE_RDMA_STATS_QUEUE 128 
 int ECORE_SUCCESS ; 
 scalar_t__ FW_MSG_CODE_UNSUPPORTED ; 
 scalar_t__ MAX_NUM_LL2_RX_QUEUES ; 
 scalar_t__ NUM_OF_GLOBAL_QUEUES ; 
 scalar_t__ RDMA_NUM_STATISTIC_COUNTERS_BB ; 
 scalar_t__ RDMA_NUM_STATISTIC_COUNTERS_K2 ; 
 int __ecore_hw_set_soft_resc_size (struct ecore_hwfn*,struct ecore_ptt*,int,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_hw_set_soft_resc_size(struct ecore_hwfn *p_hwfn,
			    struct ecore_ptt *p_ptt)
{
	bool b_ah = ECORE_IS_AH(p_hwfn->p_dev);
	u32 resc_max_val, mcp_resp;
	u8 res_id;
	enum _ecore_status_t rc;

	for (res_id = 0; res_id < ECORE_MAX_RESC; res_id++) {
		switch (res_id) {
		case ECORE_LL2_QUEUE:
			resc_max_val = MAX_NUM_LL2_RX_QUEUES;
			break;
		case ECORE_RDMA_CNQ_RAM:
			/* No need for a case for ECORE_CMDQS_CQS since
			 * CNQ/CMDQS are the same resource.
			 */
			resc_max_val = NUM_OF_GLOBAL_QUEUES;
			break;
		case ECORE_RDMA_STATS_QUEUE:
			resc_max_val = b_ah ? RDMA_NUM_STATISTIC_COUNTERS_K2
					    : RDMA_NUM_STATISTIC_COUNTERS_BB;
			break;
		case ECORE_BDQ:
			resc_max_val = BDQ_NUM_RESOURCES;
			break;
		default:
			continue;
		}

		rc = __ecore_hw_set_soft_resc_size(p_hwfn, p_ptt, res_id,
						   resc_max_val, &mcp_resp);
		if (rc != ECORE_SUCCESS)
			return rc;

		/* There's no point to continue to the next resource if the
		 * command is not supported by the MFW.
		 * We do continue if the command is supported but the resource
		 * is unknown to the MFW. Such a resource will be later
		 * configured with the default allocation values.
		 */
		if (mcp_resp == FW_MSG_CODE_UNSUPPORTED)
			return ECORE_NOTIMPL;
	}

	return ECORE_SUCCESS;
}
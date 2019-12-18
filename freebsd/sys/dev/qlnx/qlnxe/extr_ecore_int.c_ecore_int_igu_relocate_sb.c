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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  free_cnt_iov; int /*<<< orphan*/  iov_cnt; int /*<<< orphan*/  free_cnt; int /*<<< orphan*/  cnt; } ;
struct ecore_igu_info {TYPE_2__ usage; struct ecore_igu_block* entry; int /*<<< orphan*/  b_allow_pf_vf_change; } ;
struct ecore_igu_block {int status; int function_id; int is_pf; int vector_number; } ;
struct TYPE_8__ {int /*<<< orphan*/ * feat_num; struct ecore_igu_info* p_igu_info; } ;
struct ecore_hwfn {int rel_pf_id; TYPE_3__ hw_info; TYPE_4__* p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_9__ {TYPE_1__* p_iov_info; } ;
struct TYPE_6__ {scalar_t__ first_vf_in_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int,char*,...) ; 
 int ECORE_IGU_STATUS_FREE ; 
 int ECORE_IGU_STATUS_PF ; 
 int ECORE_IGU_STATUS_VALID ; 
 int ECORE_INVAL ; 
 scalar_t__ ECORE_MAPPING_MEMORY_SIZE (TYPE_4__*) ; 
 int ECORE_MSG_INTR ; 
 int ECORE_MSG_IOV ; 
 size_t ECORE_PF_L2_QUE ; 
 scalar_t__ ECORE_SB_INVALID_IDX ; 
 scalar_t__ ECORE_SP_SB_ID ; 
 int ECORE_SUCCESS ; 
 size_t ECORE_VF_L2_QUE ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_FUNCTION_NUMBER ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_PF_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VALID ; 
 int /*<<< orphan*/  IGU_MAPPING_LINE_VECTOR_NUMBER ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 int /*<<< orphan*/  IS_PF_SRIOV (struct ecore_hwfn*) ; 
 scalar_t__ IS_VF (TYPE_4__*) ; 
 struct ecore_igu_block* OSAL_NULL ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_get_pf_igu_sb_id (struct ecore_hwfn*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_int_cau_conf_sb (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int /*<<< orphan*/ ) ; 

enum _ecore_status_t
ecore_int_igu_relocate_sb(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			  u16 sb_id, bool b_to_vf)
{
	struct ecore_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	struct ecore_igu_block *p_block = OSAL_NULL;
	u16 igu_sb_id = 0, vf_num = 0;
	u32 val = 0;

	if (IS_VF(p_hwfn->p_dev) || !IS_PF_SRIOV(p_hwfn))
		return ECORE_INVAL;

	if (sb_id == ECORE_SP_SB_ID)
		return ECORE_INVAL;

	if (!p_info->b_allow_pf_vf_change) {
		DP_INFO(p_hwfn, "Can't relocate SBs as MFW is too old.\n");
		return ECORE_INVAL;
	}

	/* If we're moving a SB from PF to VF, the client had to specify
	 * which vector it wants to move.
	 */
	if (b_to_vf) {
		igu_sb_id = ecore_get_pf_igu_sb_id(p_hwfn, sb_id + 1);
		if (igu_sb_id == ECORE_SB_INVALID_IDX)
			return ECORE_INVAL;
	}

	/* If we're moving a SB from VF to PF, need to validate there isn't
	 * already a line configured for that vector.
	 */
	if (!b_to_vf) {
		if (ecore_get_pf_igu_sb_id(p_hwfn, sb_id + 1) !=
		    ECORE_SB_INVALID_IDX)
			return ECORE_INVAL;
	}

	/* We need to validate that the SB can actually be relocated.
	 * This would also handle the previous case where we've explicitly
	 * stated which IGU SB needs to move.
	 */
	for (; igu_sb_id < ECORE_MAPPING_MEMORY_SIZE(p_hwfn->p_dev);
	     igu_sb_id++) {
		p_block = &p_info->entry[igu_sb_id];

		if (!(p_block->status & ECORE_IGU_STATUS_VALID) ||
		    !(p_block->status & ECORE_IGU_STATUS_FREE) ||
		    (!!(p_block->status & ECORE_IGU_STATUS_PF) != b_to_vf)) {
			if (b_to_vf)
				return ECORE_INVAL;
			else
				continue;
		}

		break;
	}

	if (igu_sb_id == ECORE_MAPPING_MEMORY_SIZE(p_hwfn->p_dev)) {
		DP_VERBOSE(p_hwfn, (ECORE_MSG_INTR | ECORE_MSG_IOV),
			   "Failed to find a free SB to move\n");
		return ECORE_INVAL;
	}

	if (p_block == OSAL_NULL) {
		DP_VERBOSE(p_hwfn, (ECORE_MSG_INTR | ECORE_MSG_IOV),
			   "SB address (p_block) is NULL\n");
		return ECORE_INVAL;
	}

	/* At this point, p_block points to the SB we want to relocate */
	if (b_to_vf) {
		p_block->status &= ~ECORE_IGU_STATUS_PF;

		/* It doesn't matter which VF number we choose, since we're
		 * going to disable the line; But let's keep it in range.
		 */
		vf_num = (u16)p_hwfn->p_dev->p_iov_info->first_vf_in_pf;

		p_block->function_id = (u8)vf_num;
		p_block->is_pf = 0;
		p_block->vector_number = 0;

		p_info->usage.cnt--;
		p_info->usage.free_cnt--;
		p_info->usage.iov_cnt++;
		p_info->usage.free_cnt_iov++;

		/* TODO - if SBs aren't really the limiting factor,
		 * then it might not be accurate [in the since that
		 * we might not need decrement the feature].
		 */
		p_hwfn->hw_info.feat_num[ECORE_PF_L2_QUE]--;
		p_hwfn->hw_info.feat_num[ECORE_VF_L2_QUE]++;
	} else {
		p_block->status |= ECORE_IGU_STATUS_PF;
		p_block->function_id = p_hwfn->rel_pf_id;
		p_block->is_pf = 1;
		p_block->vector_number = sb_id + 1;

		p_info->usage.cnt++;
		p_info->usage.free_cnt++;
		p_info->usage.iov_cnt--;
		p_info->usage.free_cnt_iov--;

		p_hwfn->hw_info.feat_num[ECORE_PF_L2_QUE]++;
		p_hwfn->hw_info.feat_num[ECORE_VF_L2_QUE]--;
	}

	/* Update the IGU and CAU with the new configuration */
	SET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER,
		  p_block->function_id);
	SET_FIELD(val, IGU_MAPPING_LINE_PF_VALID, p_block->is_pf);
	SET_FIELD(val, IGU_MAPPING_LINE_VALID, p_block->is_pf);
	SET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER,
		  p_block->vector_number);

	ecore_wr(p_hwfn, p_ptt,
		 IGU_REG_MAPPING_MEMORY + sizeof(u32) * igu_sb_id,
		 val);

	ecore_int_cau_conf_sb(p_hwfn, p_ptt, 0,
			      igu_sb_id, vf_num,
			      p_block->is_pf ? 0 : 1);

	DP_VERBOSE(p_hwfn, ECORE_MSG_INTR,
		   "Relocation: [SB 0x%04x] func_id = %d is_pf = %d vector_num = 0x%x\n",
		   igu_sb_id, p_block->function_id,
		   p_block->is_pf, p_block->vector_number);

	return ECORE_SUCCESS;
}
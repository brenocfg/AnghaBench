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
typedef  int u32 ;
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  rel_pf_id; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_SLOW (int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_REV_IS_TEDIBEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int FINAL_CLEANUP_POLL_CNT ; 
 int /*<<< orphan*/  FINAL_CLEANUP_POLL_TIME ; 
 int GTT_BAR0_MAP_REG_USDM_RAM ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_RD (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  REG_WR (struct ecore_hwfn*,int,int /*<<< orphan*/ ) ; 
 int SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_SHIFT ; 
 int SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_SHIFT ; 
 int SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_SHIFT ; 
 int SDM_COMP_TYPE_AGG_INT ; 
 int SDM_OP_GEN_COMP_TYPE_SHIFT ; 
 int USTORM_FLR_FINAL_ACK_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSDM_REG_OPERATION_GEN ; 
 int X_FINAL_CLEANUP_AGG_INT ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_final_cleanup(struct ecore_hwfn *p_hwfn,
					 struct ecore_ptt *p_ptt,
					 u16 id, bool is_vf)
{
	u32 command = 0, addr, count = FINAL_CLEANUP_POLL_CNT;
	enum _ecore_status_t rc = ECORE_TIMEOUT;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_TEDIBEAR(p_hwfn->p_dev) ||
	    CHIP_REV_IS_SLOW(p_hwfn->p_dev)) {
		DP_INFO(p_hwfn, "Skipping final cleanup for non-ASIC\n");
		return ECORE_SUCCESS;
	}
#endif

	addr = GTT_BAR0_MAP_REG_USDM_RAM +
	       USTORM_FLR_FINAL_ACK_OFFSET(p_hwfn->rel_pf_id);

	if (is_vf)
		id += 0x10;

	command |= X_FINAL_CLEANUP_AGG_INT <<
		   SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_SHIFT;
	command |= 1 << SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_SHIFT;
	command |= id << SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_SHIFT;
	command |= SDM_COMP_TYPE_AGG_INT << SDM_OP_GEN_COMP_TYPE_SHIFT;

	/* Make sure notification is not set before initiating final cleanup */
	if (REG_RD(p_hwfn, addr)) {
		DP_NOTICE(p_hwfn, false,
			  "Unexpected; Found final cleanup notification before initiating final cleanup\n");
		REG_WR(p_hwfn, addr, 0);
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "Sending final cleanup for PFVF[%d] [Command %08x]\n",
		   id, command);

	ecore_wr(p_hwfn, p_ptt, XSDM_REG_OPERATION_GEN, command);

	/* Poll until completion */
	while (!REG_RD(p_hwfn, addr) && count--)
		OSAL_MSLEEP(FINAL_CLEANUP_POLL_TIME);

	if (REG_RD(p_hwfn, addr))
		rc = ECORE_SUCCESS;
	else
		DP_NOTICE(p_hwfn, true, "Failed to receive FW final cleanup notification\n");

	/* Cleanup afterwards */
	REG_WR(p_hwfn, addr, 0);

	return rc;
}
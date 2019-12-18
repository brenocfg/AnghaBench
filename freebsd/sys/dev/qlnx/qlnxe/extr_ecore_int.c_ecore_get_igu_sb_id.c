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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {TYPE_1__* p_igu_info; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_2__ hw_info; } ;
struct TYPE_3__ {scalar_t__ igu_dsb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ECORE_MSG_INTR ; 
 scalar_t__ ECORE_SB_INVALID_IDX ; 
 scalar_t__ ECORE_SP_SB_ID ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_get_pf_igu_sb_id (struct ecore_hwfn*,scalar_t__) ; 
 scalar_t__ ecore_vf_get_igu_sb_id (struct ecore_hwfn*,scalar_t__) ; 

u16 ecore_get_igu_sb_id(struct ecore_hwfn *p_hwfn, u16 sb_id)
{
	u16 igu_sb_id;

	/* Assuming continuous set of IGU SBs dedicated for given PF */
	if (sb_id == ECORE_SP_SB_ID)
		igu_sb_id = p_hwfn->hw_info.p_igu_info->igu_dsb_id;
	else if (IS_PF(p_hwfn->p_dev))
		igu_sb_id = ecore_get_pf_igu_sb_id(p_hwfn, sb_id + 1);
	else
		igu_sb_id = ecore_vf_get_igu_sb_id(p_hwfn, sb_id);

	if (igu_sb_id == ECORE_SB_INVALID_IDX)
		DP_NOTICE(p_hwfn, true,
			  "Slowpath SB vector %04x doesn't exist\n",
			  sb_id);
	else if (sb_id == ECORE_SP_SB_ID)
		DP_VERBOSE(p_hwfn, ECORE_MSG_INTR,
			   "Slowpath SB index in IGU is 0x%04x\n", igu_sb_id);
	else
		DP_VERBOSE(p_hwfn, ECORE_MSG_INTR,
			   "SB [%04x] <--> IGU SB [%04x]\n", sb_id, igu_sb_id);

	return igu_sb_id;
}
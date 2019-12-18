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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_FPGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  IGU_REG_ATTENTION_ENABLE ; 
 int /*<<< orphan*/  IGU_REG_LEADING_EDGE_LATCH ; 
 int /*<<< orphan*/  IGU_REG_TRAILING_EDGE_LATCH ; 
 int /*<<< orphan*/  MISC_REG_AEU_MASK_ATTN_IGU ; 
 int /*<<< orphan*/  OSAL_MMIOWB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_int_igu_enable_attn(struct ecore_hwfn *p_hwfn,
				      struct ecore_ptt *p_ptt)
{
#ifndef ASIC_ONLY
	if (CHIP_REV_IS_FPGA(p_hwfn->p_dev)) {
		DP_INFO(p_hwfn, "FPGA - Don't enable Attentions in IGU and MISC\n");
		return;
	}
#endif

	/* Configure AEU signal change to produce attentions */
	ecore_wr(p_hwfn, p_ptt, IGU_REG_ATTENTION_ENABLE, 0);
	ecore_wr(p_hwfn, p_ptt, IGU_REG_LEADING_EDGE_LATCH, 0xfff);
	ecore_wr(p_hwfn, p_ptt, IGU_REG_TRAILING_EDGE_LATCH, 0xfff);
	ecore_wr(p_hwfn, p_ptt, IGU_REG_ATTENTION_ENABLE, 0xfff);

	/* Flush the writes to IGU */
	OSAL_MMIOWB(p_hwfn->p_dev);

	/* Unmask AEU signals toward IGU */
	ecore_wr(p_hwfn, p_ptt, MISC_REG_AEU_MASK_ATTN_IGU, 0xff);
}
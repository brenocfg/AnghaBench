#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_igu_info {size_t igu_dsb_id; struct ecore_igu_block* entry; } ;
struct ecore_igu_block {int status; int /*<<< orphan*/  is_pf; } ;
struct TYPE_2__ {int /*<<< orphan*/  opaque_fid; struct ecore_igu_info* p_igu_info; } ;
struct ecore_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int ECORE_IGU_STATUS_DSB ; 
 int ECORE_IGU_STATUS_VALID ; 
 size_t ECORE_MAPPING_MEMORY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGU_REG_BLOCK_CONFIGURATION ; 
 int /*<<< orphan*/  IGU_REG_BLOCK_CONFIGURATION_PXP_TPH_INTERFACE_EN ; 
 int /*<<< orphan*/  IGU_REG_BLOCK_CONFIGURATION_VF_CLEANUP_EN ; 
 int /*<<< orphan*/  ecore_int_igu_init_pure_rt_single (struct ecore_hwfn*,struct ecore_ptt*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ecore_int_igu_init_pure_rt(struct ecore_hwfn *p_hwfn,
				 struct ecore_ptt *p_ptt,
				 bool b_set,
				 bool b_slowpath)
{
	struct ecore_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	struct ecore_igu_block *p_block;
	u16 igu_sb_id = 0;
	u32 val = 0;

	/* @@@TBD MichalK temporary... should be moved to init-tool... */
	val = ecore_rd(p_hwfn, p_ptt, IGU_REG_BLOCK_CONFIGURATION);
	val |= IGU_REG_BLOCK_CONFIGURATION_VF_CLEANUP_EN;
	val &= ~IGU_REG_BLOCK_CONFIGURATION_PXP_TPH_INTERFACE_EN;
	ecore_wr(p_hwfn, p_ptt, IGU_REG_BLOCK_CONFIGURATION, val);
	/* end temporary */

	for (igu_sb_id = 0;
	     igu_sb_id < ECORE_MAPPING_MEMORY_SIZE(p_hwfn->p_dev);
	     igu_sb_id++) {
		p_block = &p_info->entry[igu_sb_id];

		if (!(p_block->status & ECORE_IGU_STATUS_VALID) ||
		    !p_block->is_pf ||
		    (p_block->status & ECORE_IGU_STATUS_DSB))
			continue;

		ecore_int_igu_init_pure_rt_single(p_hwfn, p_ptt, igu_sb_id,
						  p_hwfn->hw_info.opaque_fid,
						  b_set);
	}

	if (b_slowpath)
		ecore_int_igu_init_pure_rt_single(p_hwfn, p_ptt,
						  p_info->igu_dsb_id,
						  p_hwfn->hw_info.opaque_fid,
						  b_set);
}
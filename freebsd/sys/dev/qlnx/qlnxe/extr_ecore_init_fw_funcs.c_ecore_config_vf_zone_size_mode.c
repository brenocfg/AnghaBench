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
typedef  scalar_t__ u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int MSTORM_VF_ZONE_DEFAULT_SIZE_LOG ; 
 int /*<<< orphan*/  PGLUE_B_REG_MSDM_OFFSET_MASK_B ; 
 int /*<<< orphan*/  PGLUE_B_REG_MSDM_VF_SHIFT_B ; 
 int /*<<< orphan*/  PGLUE_REG_B_MSDM_OFFSET_MASK_B_RT_OFFSET ; 
 int /*<<< orphan*/  PGLUE_REG_B_MSDM_VF_SHIFT_B_RT_OFFSET ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VF_ZONE_SIZE_MODE_DOUBLE ; 
 scalar_t__ VF_ZONE_SIZE_MODE_QUAD ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

void ecore_config_vf_zone_size_mode(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt, u16 mode, bool runtime_init)
{
	u32 msdm_vf_size_log = MSTORM_VF_ZONE_DEFAULT_SIZE_LOG;
	u32 msdm_vf_offset_mask; 

	if (mode == VF_ZONE_SIZE_MODE_DOUBLE)
		msdm_vf_size_log += 1; 
	else if (mode == VF_ZONE_SIZE_MODE_QUAD)
		msdm_vf_size_log += 2; 

	msdm_vf_offset_mask = (1 << msdm_vf_size_log) - 1;

	if (runtime_init) {
		STORE_RT_REG(p_hwfn, PGLUE_REG_B_MSDM_VF_SHIFT_B_RT_OFFSET, msdm_vf_size_log);
		STORE_RT_REG(p_hwfn, PGLUE_REG_B_MSDM_OFFSET_MASK_B_RT_OFFSET, msdm_vf_offset_mask);
	}
	else {
		ecore_wr(p_hwfn, p_ptt, PGLUE_B_REG_MSDM_VF_SHIFT_B, msdm_vf_size_log);
		ecore_wr(p_hwfn, p_ptt, PGLUE_B_REG_MSDM_OFFSET_MASK_B, msdm_vf_offset_mask);
	}
}
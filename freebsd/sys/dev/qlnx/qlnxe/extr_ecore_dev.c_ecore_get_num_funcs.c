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
typedef  void* u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int abs_pf_id; int num_funcs_on_engine; void* enabled_func_idx; void* rel_pf_id; struct ecore_dev* p_dev; } ;
struct ecore_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_FPGA (struct ecore_dev*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,void*,int,void*,int) ; 
 scalar_t__ ECORE_IS_AH (struct ecore_dev*) ; 
 scalar_t__ ECORE_IS_BB (struct ecore_dev*) ; 
 int /*<<< orphan*/  ECORE_IS_CMT (struct ecore_dev*) ; 
 int /*<<< orphan*/  ECORE_MSG_PROBE ; 
 scalar_t__ ECORE_PATH_ID (struct ecore_hwfn*) ; 
 void* MAX_NUM_PFS_BB ; 
 void* MAX_NUM_PFS_K2 ; 
 int /*<<< orphan*/  MISCS_REG_FUNCTION_HIDE ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_get_num_funcs(struct ecore_hwfn *p_hwfn,
				struct ecore_ptt *p_ptt)
{
	u8 num_funcs, enabled_func_idx = p_hwfn->rel_pf_id;
	u32 reg_function_hide, tmp, eng_mask, low_pfs_mask;
	struct ecore_dev *p_dev = p_hwfn->p_dev;

	num_funcs = ECORE_IS_AH(p_dev) ? MAX_NUM_PFS_K2 : MAX_NUM_PFS_BB;

	/* Bit 0 of MISCS_REG_FUNCTION_HIDE indicates whether the bypass values
	 * in the other bits are selected.
	 * Bits 1-15 are for functions 1-15, respectively, and their value is
	 * '0' only for enabled functions (function 0 always exists and
	 * enabled).
	 * In case of CMT in BB, only the "even" functions are enabled, and thus
	 * the number of functions for both hwfns is learnt from the same bits.
	 */
	reg_function_hide = ecore_rd(p_hwfn, p_ptt, MISCS_REG_FUNCTION_HIDE);

	if (reg_function_hide & 0x1) {
		if (ECORE_IS_BB(p_dev)) {
			if (ECORE_PATH_ID(p_hwfn) && !ECORE_IS_CMT(p_dev)) {
				num_funcs = 0;
				eng_mask = 0xaaaa;
			} else {
				num_funcs = 1;
				eng_mask = 0x5554;
			}
		} else {
			num_funcs = 1;
			eng_mask = 0xfffe;
		}

		/* Get the number of the enabled functions on the engine */
		tmp = (reg_function_hide ^ 0xffffffff) & eng_mask;
		while (tmp) {
			if (tmp & 0x1)
				num_funcs++;
			tmp >>= 0x1;
		}

		/* Get the PF index within the enabled functions */
		low_pfs_mask = (0x1 << p_hwfn->abs_pf_id) - 1;
		tmp = reg_function_hide & eng_mask & low_pfs_mask;
		while (tmp) {
			if (tmp & 0x1)
				enabled_func_idx--;
			tmp >>= 0x1;
		}
	}

	p_hwfn->num_funcs_on_engine = num_funcs;
	p_hwfn->enabled_func_idx = enabled_func_idx;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_FPGA(p_dev)) {
		DP_NOTICE(p_hwfn, false,
			  "FPGA: Limit number of PFs to 4 [would affect resource allocation, needed for IOV]\n");
		p_hwfn->num_funcs_on_engine = 4;
	}
#endif

	DP_VERBOSE(p_hwfn, ECORE_MSG_PROBE,
		   "PF [rel_id %d, abs_id %d] occupies index %d within the %d enabled functions on the engine\n",
		   p_hwfn->rel_pf_id, p_hwfn->abs_pf_id,
		   p_hwfn->enabled_func_idx, p_hwfn->num_funcs_on_engine);
}
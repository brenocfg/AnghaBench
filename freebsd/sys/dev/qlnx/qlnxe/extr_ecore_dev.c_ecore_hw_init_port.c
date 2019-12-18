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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; int /*<<< orphan*/  port_id; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_ASIC (int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_REV_IS_EMUL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_REV_IS_FPGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_E5_MISSING_CODE ; 
 scalar_t__ ECORE_IS_AH (int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_IS_BB (int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_IS_CMT (int /*<<< orphan*/ ) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  IS_LEAD_HWFN (struct ecore_hwfn*) ; 
 scalar_t__ MISCS_REG_CLK_100G_MODE ; 
 scalar_t__ MISCS_REG_RESET_PL_HV ; 
 scalar_t__ MISC_REG_CLK_100G_MODE ; 
 scalar_t__ MISC_REG_OPTE_MODE ; 
 int /*<<< orphan*/  NIG_REG_BRB_GATE_DNTFWD_PORT_RT_OFFSET ; 
 scalar_t__ NIG_REG_LLH_ENG_CLS_ENG_ID_TBL ; 
 scalar_t__ NIG_REG_LLH_ENG_CLS_TCP_4_TUPLE_SEARCH ; 
 scalar_t__ PGLUE_B_REG_MASTER_WRITE_PAD_ENABLE ; 
 int /*<<< orphan*/  PHASE_PORT ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_emul_link_init (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_init_run (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_link_init_bb (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_hw_init_port(struct ecore_hwfn *p_hwfn,
					       struct ecore_ptt *p_ptt,
					       int hw_mode)
{
	enum _ecore_status_t rc	= ECORE_SUCCESS;

	/* In CMT the gate should be cleared by the 2nd hwfn */
	if (!ECORE_IS_CMT(p_hwfn->p_dev) || !IS_LEAD_HWFN(p_hwfn))
		STORE_RT_REG(p_hwfn, NIG_REG_BRB_GATE_DNTFWD_PORT_RT_OFFSET, 0);

	rc = ecore_init_run(p_hwfn, p_ptt, PHASE_PORT, p_hwfn->port_id,
			    hw_mode);
	if (rc != ECORE_SUCCESS)
		return rc;

	ecore_wr(p_hwfn, p_ptt, PGLUE_B_REG_MASTER_WRITE_PAD_ENABLE, 0);

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_ASIC(p_hwfn->p_dev))
		return ECORE_SUCCESS;

	if (CHIP_REV_IS_FPGA(p_hwfn->p_dev)) {
		if (ECORE_IS_AH(p_hwfn->p_dev))
			return ECORE_SUCCESS;
		else if (ECORE_IS_BB(p_hwfn->p_dev))
			ecore_link_init_bb(p_hwfn, p_ptt, p_hwfn->port_id);
		else /* E5 */
			ECORE_E5_MISSING_CODE;
	} else if (CHIP_REV_IS_EMUL(p_hwfn->p_dev)) {
		if (ECORE_IS_CMT(p_hwfn->p_dev)) {
			/* Activate OPTE in CMT */
			u32 val;

			val = ecore_rd(p_hwfn, p_ptt, MISCS_REG_RESET_PL_HV);
			val |= 0x10;
			ecore_wr(p_hwfn, p_ptt, MISCS_REG_RESET_PL_HV, val);
			ecore_wr(p_hwfn, p_ptt, MISC_REG_CLK_100G_MODE, 1);
			ecore_wr(p_hwfn, p_ptt, MISCS_REG_CLK_100G_MODE, 1);
			ecore_wr(p_hwfn, p_ptt, MISC_REG_OPTE_MODE, 1);
			ecore_wr(p_hwfn, p_ptt,
				 NIG_REG_LLH_ENG_CLS_TCP_4_TUPLE_SEARCH, 1);
			ecore_wr(p_hwfn, p_ptt,
				 NIG_REG_LLH_ENG_CLS_ENG_ID_TBL, 0x55555555);
			ecore_wr(p_hwfn, p_ptt,
				 NIG_REG_LLH_ENG_CLS_ENG_ID_TBL + 0x4,
				 0x55555555);
		}

		ecore_emul_link_init(p_hwfn, p_ptt);
	} else {
		DP_INFO(p_hwfn->p_dev, "link is not being configured\n");
	}
#endif

	return rc;
}
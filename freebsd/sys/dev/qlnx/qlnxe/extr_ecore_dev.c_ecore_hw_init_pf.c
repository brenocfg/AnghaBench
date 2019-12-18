#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_function_info {scalar_t__ bandwidth_min; } ;
struct TYPE_6__ {int ovlan; scalar_t__ personality; } ;
struct TYPE_5__ {int pf_rl; scalar_t__ pf_wfq; } ;
struct ecore_hwfn {TYPE_3__ hw_info; scalar_t__ p_dev; int /*<<< orphan*/  my_id; TYPE_2__ qm_info; TYPE_1__* mcp_info; int /*<<< orphan*/  rel_pf_id; } ;
struct ecore_hw_init_params {scalar_t__ pci_rlx_odr_mode; int /*<<< orphan*/  allow_npar_tx_switch; int /*<<< orphan*/  p_tunn; int /*<<< orphan*/  int_mode; scalar_t__ b_hw_start; int /*<<< orphan*/  avoid_eng_affin; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {struct ecore_mcp_function_info func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ECORE_DISABLE_RLX_ODR ; 
 scalar_t__ ECORE_ENABLE_RLX_ODR ; 
 int ECORE_IO ; 
 int /*<<< orphan*/  ECORE_MSG_HW ; 
 int /*<<< orphan*/  ECORE_MSG_STORAGE ; 
 scalar_t__ ECORE_PCI_FCOE ; 
 scalar_t__ ECORE_PCI_ISCSI ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_LEAD_HWFN (struct ecore_hwfn*) ; 
 int MODE_MF_SD ; 
 int MODE_MF_SI ; 
 int /*<<< orphan*/  NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_OFFSET ; 
 int /*<<< orphan*/  NIG_REG_LLH_FUNC_TAGMAC_CLS_TYPE_RT_OFFSET ; 
 int /*<<< orphan*/  NIG_REG_LLH_FUNC_TAG_EN_RT_OFFSET ; 
 int /*<<< orphan*/  NIG_REG_LLH_FUNC_TAG_VALUE_RT_OFFSET ; 
 int /*<<< orphan*/  OSAL_BEFORE_PF_START (void*,int /*<<< orphan*/ ) ; 
 int OSAL_PCI_FIND_CAPABILITY (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_PCI_READ_CONFIG_WORD (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_PCI_WRITE_CONFIG_WORD (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 scalar_t__ PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_RELAX_EN ; 
 int /*<<< orphan*/  PHASE_PF ; 
 int /*<<< orphan*/  PHASE_QM_PF ; 
 int /*<<< orphan*/  PRS_REG_PKT_LEN_STAT_TAGS_NOT_COUNTED_FIRST ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_FCOE ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_FCOE_RT_OFFSET ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_ROCE ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_ROCE_RT_OFFSET ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_TAG1 ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_TCP ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_TCP_FIRST_FRAG ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_TCP_RT_OFFSET ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_UDP ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_cxt_hw_init_pf (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_dmae_sanity (struct ecore_hwfn*,struct ecore_ptt*,char*) ; 
 int ecore_hw_init_pf_doorbell_bar (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_init_run (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ecore_int_igu_enable (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_int_igu_init_pure_rt (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 
 int /*<<< orphan*/  ecore_int_igu_init_rt (struct ecore_hwfn*) ; 
 int ecore_llh_hw_init_pf (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_mcp_rlx_odr_supported (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int ecore_sp_pf_start (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_hw_init_pf(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		 int hw_mode, struct ecore_hw_init_params *p_params)
{
	u8 rel_pf_id = p_hwfn->rel_pf_id;
	u32 prs_reg;
	enum _ecore_status_t rc	= ECORE_SUCCESS;
	u16 ctrl;
	int pos;

	if (p_hwfn->mcp_info) {
		struct ecore_mcp_function_info *p_info;

		p_info = &p_hwfn->mcp_info->func_info;
		if (p_info->bandwidth_min)
			p_hwfn->qm_info.pf_wfq = p_info->bandwidth_min;

		/* Update rate limit once we'll actually have a link */
		p_hwfn->qm_info.pf_rl = 100000;
	}
	ecore_cxt_hw_init_pf(p_hwfn, p_ptt);

	ecore_int_igu_init_rt(p_hwfn);

	/* Set VLAN in NIG if needed */
	if (hw_mode & (1 << MODE_MF_SD)) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "Configuring LLH_FUNC_TAG\n");
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_TAG_EN_RT_OFFSET, 1);
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_TAG_VALUE_RT_OFFSET,
			     p_hwfn->hw_info.ovlan);

		DP_VERBOSE(p_hwfn, ECORE_MSG_HW,
			   "Configuring LLH_FUNC_FILTER_HDR_SEL\n");
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_OFFSET,
			     1);
	}

	/* Enable classification by MAC if needed */
	if (hw_mode & (1 << MODE_MF_SI)) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "Configuring TAGMAC_CLS_TYPE\n");
		STORE_RT_REG(p_hwfn,
			     NIG_REG_LLH_FUNC_TAGMAC_CLS_TYPE_RT_OFFSET, 1);
	}

	/* Protocl Configuration  - @@@TBD - should we set 0 otherwise?*/
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_TCP_RT_OFFSET,
		     (p_hwfn->hw_info.personality == ECORE_PCI_ISCSI) ? 1 : 0);
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_FCOE_RT_OFFSET,
		     (p_hwfn->hw_info.personality == ECORE_PCI_FCOE) ? 1 : 0);
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_ROCE_RT_OFFSET, 0);

	/* perform debug configuration when chip is out of reset */
	OSAL_BEFORE_PF_START((void *)p_hwfn->p_dev, p_hwfn->my_id);

	/* Sanity check before the PF init sequence that uses DMAE */
	rc = ecore_dmae_sanity(p_hwfn, p_ptt, "pf_phase");
	if (rc)
		return rc;

	/* PF Init sequence */
	rc = ecore_init_run(p_hwfn, p_ptt, PHASE_PF, rel_pf_id, hw_mode);
	if (rc)
		return rc;

	/* QM_PF Init sequence (may be invoked separately e.g. for DCB) */
	rc = ecore_init_run(p_hwfn, p_ptt, PHASE_QM_PF, rel_pf_id, hw_mode);
	if (rc)
		return rc;

	/* Pure runtime initializations - directly to the HW  */
	ecore_int_igu_init_pure_rt(p_hwfn, p_ptt, true, true);

	/* PCI relaxed ordering is generally beneficial for performance,
	 * but can hurt performance or lead to instability on some setups.
	 * If management FW is taking care of it go with that, otherwise
	 * disable to be on the safe side.
	 */
	pos = OSAL_PCI_FIND_CAPABILITY(p_hwfn->p_dev, PCI_CAP_ID_EXP);
	if (!pos) {
		DP_NOTICE(p_hwfn, true,
			  "Failed to find the PCI Express Capability structure in the PCI config space\n");
		return ECORE_IO;
	}

	OSAL_PCI_READ_CONFIG_WORD(p_hwfn->p_dev, pos + PCI_EXP_DEVCTL, &ctrl);

	if (p_params->pci_rlx_odr_mode == ECORE_ENABLE_RLX_ODR) {
		ctrl |= PCI_EXP_DEVCTL_RELAX_EN;
		OSAL_PCI_WRITE_CONFIG_WORD(p_hwfn->p_dev,
					   pos + PCI_EXP_DEVCTL, ctrl);
	} else if (p_params->pci_rlx_odr_mode == ECORE_DISABLE_RLX_ODR) {
		ctrl &= ~PCI_EXP_DEVCTL_RELAX_EN;
		OSAL_PCI_WRITE_CONFIG_WORD(p_hwfn->p_dev,
					   pos + PCI_EXP_DEVCTL, ctrl);
	} else if (ecore_mcp_rlx_odr_supported(p_hwfn)) {
		DP_INFO(p_hwfn, "PCI relax ordering configured by MFW\n");
	} else {
		ctrl &= ~PCI_EXP_DEVCTL_RELAX_EN;
		OSAL_PCI_WRITE_CONFIG_WORD(p_hwfn->p_dev,
					   pos + PCI_EXP_DEVCTL, ctrl);
	}

	rc = ecore_hw_init_pf_doorbell_bar(p_hwfn, p_ptt);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Use the leading hwfn since in CMT only NIG #0 is operational */
	if (IS_LEAD_HWFN(p_hwfn)) {
		rc = ecore_llh_hw_init_pf(p_hwfn, p_ptt,
					  p_params->avoid_eng_affin);
		if (rc != ECORE_SUCCESS)
			return rc;
	}

	if (p_params->b_hw_start) {
		/* enable interrupts */
		rc = ecore_int_igu_enable(p_hwfn, p_ptt, p_params->int_mode);
		if (rc != ECORE_SUCCESS)
			return rc;

		/* send function start command */
		rc = ecore_sp_pf_start(p_hwfn, p_ptt, p_params->p_tunn,
				       p_params->allow_npar_tx_switch);
		if (rc) {
			DP_NOTICE(p_hwfn, true, "Function start ramrod failed\n");
			return rc;
		}
		prs_reg = ecore_rd(p_hwfn, p_ptt, PRS_REG_SEARCH_TAG1);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_TAG1: %x\n", prs_reg);

		if (p_hwfn->hw_info.personality == ECORE_PCI_FCOE)
		{
			ecore_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TAG1,
					(1 << 2));
			ecore_wr(p_hwfn, p_ptt,
					PRS_REG_PKT_LEN_STAT_TAGS_NOT_COUNTED_FIRST,
					0x100);
		}
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH registers after start PFn\n");
		prs_reg = ecore_rd(p_hwfn, p_ptt, PRS_REG_SEARCH_TCP);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_TCP: %x\n", prs_reg);
		prs_reg = ecore_rd(p_hwfn, p_ptt, PRS_REG_SEARCH_UDP);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_UDP: %x\n", prs_reg);
		prs_reg = ecore_rd(p_hwfn, p_ptt, PRS_REG_SEARCH_FCOE);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_FCOE: %x\n", prs_reg);
		prs_reg = ecore_rd(p_hwfn, p_ptt, PRS_REG_SEARCH_ROCE);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_ROCE: %x\n", prs_reg);
		prs_reg = ecore_rd(p_hwfn, p_ptt,
				PRS_REG_SEARCH_TCP_FIRST_FRAG);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_TCP_FIRST_FRAG: %x\n",
				prs_reg);
		prs_reg = ecore_rd(p_hwfn, p_ptt, PRS_REG_SEARCH_TAG1);
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
				"PRS_REG_SEARCH_TAG1: %x\n", prs_reg);
	}
	return ECORE_SUCCESS;
}
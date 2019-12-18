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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ecore_rdma_pf_params {int roce_edpm_mode; int /*<<< orphan*/  min_dpis; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {struct ecore_rdma_pf_params rdma_pf_params; } ;
struct ecore_hwfn {int dpi_start_offset; scalar_t__ db_bar_no_edpm; scalar_t__ dcbx_no_edpm; int /*<<< orphan*/  dpi_count; int /*<<< orphan*/  dpi_size; scalar_t__ wid_count; int /*<<< orphan*/  p_dev; TYPE_1__ pf_params; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_ID_1 ; 
 int /*<<< orphan*/  DORQ_REG_PF_ICID_BIT_SHIFT_NORM ; 
 int /*<<< orphan*/  DORQ_REG_PF_MIN_ADDR_REG1 ; 
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int,...) ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long) ; 
 scalar_t__ ECORE_IS_CMT (int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_IS_IWARP_PERSONALITY (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ECORE_MIN_DPIS ; 
 int ECORE_MIN_PWM_REGION ; 
 int ECORE_NORESOURCES ; 
 int ECORE_PF_DEMS_SIZE ; 
 int ECORE_ROCE_EDPM_MODE_DISABLE ; 
 int ECORE_ROCE_EDPM_MODE_ENABLE ; 
 int ECORE_ROCE_EDPM_MODE_FORCE_ON ; 
 int ECORE_SUCCESS ; 
 int OSAL_LOG2 (int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int OSAL_NUM_CPUS () ; 
 scalar_t__ OSAL_PAGE_SIZE ; 
 int /*<<< orphan*/  PROTOCOLID_CORE ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int ROUNDUP (int,scalar_t__) ; 
 int ecore_cxt_get_proto_cid_count (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_hw_bar_size (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int ecore_hw_init_dpi_size (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 
 int /*<<< orphan*/  ecore_rdma_dpm_bar (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_hw_init_pf_doorbell_bar(struct ecore_hwfn *p_hwfn,
			      struct ecore_ptt *p_ptt)
{
	struct ecore_rdma_pf_params *p_rdma_pf_params;
	u32 pwm_regsize, norm_regsize;
	u32 non_pwm_conn, min_addr_reg1;
	u32 db_bar_size, n_cpus = 1;
	u32 roce_edpm_mode;
	u32 pf_dems_shift;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	u8 cond;

	db_bar_size = ecore_hw_bar_size(p_hwfn, p_ptt, BAR_ID_1);
	if (ECORE_IS_CMT(p_hwfn->p_dev))
		db_bar_size /= 2;

	/* Calculate doorbell regions
	 * -----------------------------------
	 * The doorbell BAR is made of two regions. The first is called normal
	 * region and the second is called PWM region. In the normal region
	 * each ICID has its own set of addresses so that writing to that
	 * specific address identifies the ICID. In the Process Window Mode
	 * region the ICID is given in the data written to the doorbell. The
	 * above per PF register denotes the offset in the doorbell BAR in which
	 * the PWM region begins.
	 * The normal region has ECORE_PF_DEMS_SIZE bytes per ICID, that is per
	 * non-PWM connection. The calculation below computes the total non-PWM
	 * connections. The DORQ_REG_PF_MIN_ADDR_REG1 register is
	 * in units of 4,096 bytes.
	 */
	non_pwm_conn = ecore_cxt_get_proto_cid_start(p_hwfn, PROTOCOLID_CORE) +
		       ecore_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_CORE,
						     OSAL_NULL) +
		       ecore_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_ETH,
						     OSAL_NULL);
	norm_regsize = ROUNDUP(ECORE_PF_DEMS_SIZE * non_pwm_conn, OSAL_PAGE_SIZE);
	min_addr_reg1 = norm_regsize / 4096;
	pwm_regsize = db_bar_size - norm_regsize;

	/* Check that the normal and PWM sizes are valid */
	if (db_bar_size < norm_regsize) {
		DP_ERR(p_hwfn->p_dev,
		       "Doorbell BAR size 0x%x is too small (normal region is 0x%0x )\n",
		       db_bar_size, norm_regsize);
		return ECORE_NORESOURCES;
	}
	if (pwm_regsize < ECORE_MIN_PWM_REGION) {
		DP_ERR(p_hwfn->p_dev,
		       "PWM region size 0x%0x is too small. Should be at least 0x%0x (Doorbell BAR size is 0x%x and normal region size is 0x%0x)\n",
		       pwm_regsize, ECORE_MIN_PWM_REGION, db_bar_size,
		       norm_regsize);
		return ECORE_NORESOURCES;
	}

	p_rdma_pf_params = &p_hwfn->pf_params.rdma_pf_params;

	/* Calculate number of DPIs */
	if (ECORE_IS_IWARP_PERSONALITY(p_hwfn))
		p_rdma_pf_params->roce_edpm_mode =  ECORE_ROCE_EDPM_MODE_DISABLE;

	if (p_rdma_pf_params->roce_edpm_mode <= ECORE_ROCE_EDPM_MODE_DISABLE) {
		roce_edpm_mode = p_rdma_pf_params->roce_edpm_mode;
	} else {
		DP_ERR(p_hwfn->p_dev,
		       "roce edpm mode was configured to an illegal value of %u. Resetting it to 0-Enable EDPM if BAR size is adequate\n",
		       p_rdma_pf_params->roce_edpm_mode);
		roce_edpm_mode = 0;
	}

	if ((roce_edpm_mode == ECORE_ROCE_EDPM_MODE_ENABLE) ||
	    ((roce_edpm_mode == ECORE_ROCE_EDPM_MODE_FORCE_ON))) {
		/* Either EDPM is mandatory, or we are attempting to allocate a
		 * WID per CPU.
		 */
		n_cpus = OSAL_NUM_CPUS();
		rc = ecore_hw_init_dpi_size(p_hwfn, p_ptt, pwm_regsize, n_cpus);
	}

	cond = ((rc != ECORE_SUCCESS) &&
		(roce_edpm_mode == ECORE_ROCE_EDPM_MODE_ENABLE)) ||
		(roce_edpm_mode == ECORE_ROCE_EDPM_MODE_DISABLE);
	if (cond || p_hwfn->dcbx_no_edpm) {
		/* Either EDPM is disabled from user configuration, or it is
		 * disabled via DCBx, or it is not mandatory and we failed to
		 * allocated a WID per CPU.
		 */
		n_cpus = 1;
		rc = ecore_hw_init_dpi_size(p_hwfn, p_ptt, pwm_regsize, n_cpus);

#ifdef CONFIG_ECORE_ROCE
		/* If we entered this flow due to DCBX then the DPM register is
		 * already configured.
		 */
		if (cond)
			ecore_rdma_dpm_bar(p_hwfn, p_ptt);
#endif
	}

	p_hwfn->wid_count = (u16)n_cpus;

	/* Check return codes from above calls */
	if (rc != ECORE_SUCCESS) {
#ifndef LINUX_REMOVE
		DP_ERR(p_hwfn,
		       "Failed to allocate enough DPIs. Allocated %d but the current minimum is set to %d. You can reduce this minimum down to %d via user configuration min_dpis or by disabling EDPM via user configuration roce_edpm_mode\n",
		       p_hwfn->dpi_count, p_rdma_pf_params->min_dpis,
		       ECORE_MIN_DPIS);
#else
		DP_ERR(p_hwfn,
		       "Failed to allocate enough DPIs. Allocated %d but the current minimum is set to %d. You can reduce this minimum down to %d via the module parameter min_rdma_dpis or by disabling EDPM by setting the module parameter roce_edpm to 2\n",
		       p_hwfn->dpi_count, p_rdma_pf_params->min_dpis,
		       ECORE_MIN_DPIS);
#endif
		DP_ERR(p_hwfn,
		       "doorbell bar: normal_region_size=%d, pwm_region_size=%d, dpi_size=%d, dpi_count=%d, roce_edpm=%s, page_size=%lu\n",
		       norm_regsize, pwm_regsize, p_hwfn->dpi_size,
		       p_hwfn->dpi_count,
		       ((p_hwfn->dcbx_no_edpm) || (p_hwfn->db_bar_no_edpm)) ?
		       "disabled" : "enabled", (unsigned long)OSAL_PAGE_SIZE);

		return ECORE_NORESOURCES;
	}

	DP_INFO(p_hwfn,
		"doorbell bar: normal_region_size=%d, pwm_region_size=%d, dpi_size=%d, dpi_count=%d, roce_edpm=%s, page_size=%lu\n",
		norm_regsize, pwm_regsize, p_hwfn->dpi_size, p_hwfn->dpi_count,
		((p_hwfn->dcbx_no_edpm) || (p_hwfn->db_bar_no_edpm)) ?
		"disabled" : "enabled", (unsigned long)OSAL_PAGE_SIZE);

	/* Update hwfn */
	p_hwfn->dpi_start_offset = norm_regsize; /* this is later used to
						      * calculate the doorbell
						      * address
						      */

	/* Update registers */
	/* DEMS size is configured log2 of DWORDs, hence the division by 4 */
	pf_dems_shift = OSAL_LOG2(ECORE_PF_DEMS_SIZE / 4);
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_PF_ICID_BIT_SHIFT_NORM, pf_dems_shift);
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_PF_MIN_ADDR_REG1, min_addr_reg1);

	return ECORE_SUCCESS;
}
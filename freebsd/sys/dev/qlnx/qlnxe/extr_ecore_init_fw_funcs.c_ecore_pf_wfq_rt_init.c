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
typedef  int u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct init_qm_pq_params {int /*<<< orphan*/  tc_id; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 scalar_t__ ECORE_IS_E5 (int /*<<< orphan*/ ) ; 
 int MAX_NUM_PFS_BB ; 
 int MAX_NUM_PFS_E5 ; 
 int /*<<< orphan*/  OVERWRITE_RT_REG (struct ecore_hwfn*,int,int) ; 
 int QM_REG_WFQPFCRD_MSB_RT_OFFSET ; 
 int QM_REG_WFQPFCRD_RT_OFFSET ; 
 scalar_t__ QM_REG_WFQPFUPPERBOUND_RT_OFFSET ; 
 scalar_t__ QM_REG_WFQPFWEIGHT_RT_OFFSET ; 
 int QM_WFQ_CRD_E5_NUM_VOQS ; 
 scalar_t__ QM_WFQ_CRD_REG_SIGN_BIT ; 
 int QM_WFQ_INC_VAL (size_t) ; 
 int QM_WFQ_MAX_INC_VAL ; 
 int QM_WFQ_UPPER_BOUND ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,scalar_t__,int) ; 
 int ecore_get_ext_voq (struct ecore_hwfn*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ecore_pf_wfq_rt_init(struct ecore_hwfn *p_hwfn,
								u8 port_id,
								u8 pf_id,
								u16 pf_wfq,
								u8 max_phys_tcs_per_port,
								u16 num_tx_pqs,
								struct init_qm_pq_params *pq_params)
{
	u32 inc_val, crd_reg_offset;
	u8 ext_voq;
	u16 i;

	inc_val = QM_WFQ_INC_VAL(pf_wfq);
	if (!inc_val || inc_val > QM_WFQ_MAX_INC_VAL) {
		DP_NOTICE(p_hwfn, true, "Invalid PF WFQ weight configuration\n");
		return -1;
	}

	for (i = 0; i < num_tx_pqs; i++) {
		ext_voq = ecore_get_ext_voq(p_hwfn, port_id, pq_params[i].tc_id, max_phys_tcs_per_port);
		crd_reg_offset = ECORE_IS_E5(p_hwfn->p_dev) ?
			(ext_voq < QM_WFQ_CRD_E5_NUM_VOQS ? QM_REG_WFQPFCRD_RT_OFFSET : QM_REG_WFQPFCRD_MSB_RT_OFFSET) + (ext_voq % QM_WFQ_CRD_E5_NUM_VOQS) * MAX_NUM_PFS_E5 + pf_id :
			(pf_id < MAX_NUM_PFS_BB ? QM_REG_WFQPFCRD_RT_OFFSET : QM_REG_WFQPFCRD_MSB_RT_OFFSET) + ext_voq * MAX_NUM_PFS_BB + (pf_id % MAX_NUM_PFS_BB);
		OVERWRITE_RT_REG(p_hwfn, crd_reg_offset, (u32)QM_WFQ_CRD_REG_SIGN_BIT);
	}

	STORE_RT_REG(p_hwfn, QM_REG_WFQPFUPPERBOUND_RT_OFFSET + pf_id, QM_WFQ_UPPER_BOUND | (u32)QM_WFQ_CRD_REG_SIGN_BIT);
	STORE_RT_REG(p_hwfn, QM_REG_WFQPFWEIGHT_RT_OFFSET + pf_id, inc_val);

	return 0;
}
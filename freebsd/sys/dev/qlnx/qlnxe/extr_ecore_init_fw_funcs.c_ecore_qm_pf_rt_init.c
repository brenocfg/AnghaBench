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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct init_qm_vport_params {int /*<<< orphan*/ * first_tx_pq_id; } ;
struct init_qm_pq_params {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 size_t NUM_OF_TCS ; 
 int /*<<< orphan*/  QM_INVALID_PQ_ID ; 
 int QM_OTHER_PQS_PER_PF ; 
 int QM_PQ_MEM_4KB (int) ; 
 int /*<<< orphan*/  ecore_other_pq_map_rt_init (struct ecore_hwfn*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_pf_rl_rt_init (struct ecore_hwfn*,size_t,int) ; 
 scalar_t__ ecore_pf_wfq_rt_init (struct ecore_hwfn*,size_t,size_t,scalar_t__,size_t,scalar_t__,struct init_qm_pq_params*) ; 
 int /*<<< orphan*/  ecore_tx_pq_map_rt_init (struct ecore_hwfn*,struct ecore_ptt*,size_t,size_t,size_t,int,int,int,scalar_t__,scalar_t__,scalar_t__,size_t,int,struct init_qm_pq_params*,struct init_qm_vport_params*) ; 
 scalar_t__ ecore_vp_wfq_rt_init (struct ecore_hwfn*,size_t,struct init_qm_vport_params*) ; 
 scalar_t__ ecore_vport_rl_rt_init (struct ecore_hwfn*,size_t,size_t,int,struct init_qm_vport_params*) ; 

int ecore_qm_pf_rt_init(struct ecore_hwfn *p_hwfn,
						struct ecore_ptt *p_ptt,
						u8 port_id,
						u8 pf_id,
						u8 max_phys_tcs_per_port,
						bool is_pf_loading,
						u32 num_pf_cids,
						u32 num_vf_cids,
						u32 num_tids,
						u16 start_pq,
						u16 num_pf_pqs,
						u16 num_vf_pqs,
						u8 start_vport,
						u8 num_vports,
						u16 pf_wfq,
						u32 pf_rl,
						u32 link_speed,
						struct init_qm_pq_params *pq_params,
						struct init_qm_vport_params *vport_params)
{
	u32 other_mem_size_4kb;
	u8 tc, i;

	other_mem_size_4kb = QM_PQ_MEM_4KB(num_pf_cids + num_tids) * QM_OTHER_PQS_PER_PF;

	/* Clear first Tx PQ ID array for each VPORT */
	for(i = 0; i < num_vports; i++)
		for(tc = 0; tc < NUM_OF_TCS; tc++)
			vport_params[i].first_tx_pq_id[tc] = QM_INVALID_PQ_ID;

	/* Map Other PQs (if any) */
#if QM_OTHER_PQS_PER_PF > 0
	ecore_other_pq_map_rt_init(p_hwfn, pf_id, is_pf_loading, num_pf_cids, num_tids, 0);
#endif

	/* Map Tx PQs */
	ecore_tx_pq_map_rt_init(p_hwfn, p_ptt, port_id, pf_id, max_phys_tcs_per_port, is_pf_loading, num_pf_cids, num_vf_cids,
							start_pq, num_pf_pqs, num_vf_pqs, start_vport, other_mem_size_4kb, pq_params, vport_params);

	/* Init PF WFQ */
	if (pf_wfq)
		if (ecore_pf_wfq_rt_init(p_hwfn, port_id, pf_id, pf_wfq, max_phys_tcs_per_port, num_pf_pqs + num_vf_pqs, pq_params))
		return -1;

	/* Init PF RL */
	if (ecore_pf_rl_rt_init(p_hwfn, pf_id, pf_rl))
		return -1;

	/* Set VPORT WFQ */
	if (ecore_vp_wfq_rt_init(p_hwfn, num_vports, vport_params))
		return -1;

	/* Set VPORT RL */
	if (ecore_vport_rl_rt_init(p_hwfn, start_vport, num_vports, link_speed, vport_params))
		return -1;

	return 0;
}
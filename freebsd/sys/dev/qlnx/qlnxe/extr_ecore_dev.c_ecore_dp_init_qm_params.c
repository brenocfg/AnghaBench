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
struct init_qm_vport_params {int /*<<< orphan*/ * first_tx_pq_id; int /*<<< orphan*/  vport_wfq; int /*<<< orphan*/  vport_rl; } ;
struct init_qm_pq_params {int vport_id; int /*<<< orphan*/  rl_valid; int /*<<< orphan*/  wrr_group; int /*<<< orphan*/  tc_id; } ;
struct init_qm_port_params {int /*<<< orphan*/  reserved; int /*<<< orphan*/  num_btb_blocks; int /*<<< orphan*/  num_pbf_cmd_lines; int /*<<< orphan*/  active_phys_tcs; int /*<<< orphan*/  active; } ;
struct ecore_qm_info {int start_pq; int start_vport; int num_pqs; int num_vports; struct init_qm_pq_params* qm_pq_params; struct init_qm_vport_params* qm_vport_params; struct init_qm_port_params* qm_port_params; int /*<<< orphan*/  num_pf_rls; int /*<<< orphan*/  pf_rl; int /*<<< orphan*/  pf_wfq; int /*<<< orphan*/  vport_wfq_en; int /*<<< orphan*/  vport_rl_en; int /*<<< orphan*/  pf_wfq_en; int /*<<< orphan*/  pf_rl_en; int /*<<< orphan*/  max_phys_tcs_per_port; int /*<<< orphan*/  num_vf_pqs; int /*<<< orphan*/  first_vf_pq; int /*<<< orphan*/  ooo_pq; int /*<<< orphan*/  pure_ack_pq; int /*<<< orphan*/  offload_pq; int /*<<< orphan*/  pure_lb_pq; } ;
struct ecore_hwfn {TYPE_1__* p_dev; struct ecore_qm_info qm_info; } ;
struct TYPE_2__ {int num_ports_in_engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_MSG_HW ; 
 int NUM_OF_TCS ; 
 int /*<<< orphan*/  ecore_get_pq_flags (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_dp_init_qm_params(struct ecore_hwfn *p_hwfn)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;
	struct init_qm_vport_params *vport;
	struct init_qm_port_params *port;
	struct init_qm_pq_params *pq;
	int i, tc;

	/* top level params */
	DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "qm init top level params: start_pq %d, start_vport %d, pure_lb_pq %d, offload_pq %d, pure_ack_pq %d\n",
		   qm_info->start_pq, qm_info->start_vport, qm_info->pure_lb_pq, qm_info->offload_pq, qm_info->pure_ack_pq);
	DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "ooo_pq %d, first_vf_pq %d, num_pqs %d, num_vf_pqs %d, num_vports %d, max_phys_tcs_per_port %d\n",
		   qm_info->ooo_pq, qm_info->first_vf_pq, qm_info->num_pqs, qm_info->num_vf_pqs, qm_info->num_vports, qm_info->max_phys_tcs_per_port);
	DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "pf_rl_en %d, pf_wfq_en %d, vport_rl_en %d, vport_wfq_en %d, pf_wfq %d, pf_rl %d, num_pf_rls %d, pq_flags %x\n",
		   qm_info->pf_rl_en, qm_info->pf_wfq_en, qm_info->vport_rl_en, qm_info->vport_wfq_en, qm_info->pf_wfq, qm_info->pf_rl, qm_info->num_pf_rls, ecore_get_pq_flags(p_hwfn));

	/* port table */
	for (i = 0; i < p_hwfn->p_dev->num_ports_in_engine; i++) {
		port = &(qm_info->qm_port_params[i]);
		DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "port idx %d, active %d, active_phys_tcs %d, num_pbf_cmd_lines %d, num_btb_blocks %d, reserved %d\n",
			   i, port->active, port->active_phys_tcs, port->num_pbf_cmd_lines, port->num_btb_blocks, port->reserved);
	}

	/* vport table */
	for (i = 0; i < qm_info->num_vports; i++) {
		vport = &(qm_info->qm_vport_params[i]);
		DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "vport idx %d, vport_rl %d, wfq %d, first_tx_pq_id [ ",
			   qm_info->start_vport + i, vport->vport_rl, vport->vport_wfq);
		for (tc = 0; tc < NUM_OF_TCS; tc++)
			DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "%d ", vport->first_tx_pq_id[tc]);
		DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "]\n");
	}

	/* pq table */
	for (i = 0; i < qm_info->num_pqs; i++) {
		pq = &(qm_info->qm_pq_params[i]);
		DP_VERBOSE(p_hwfn, ECORE_MSG_HW, "pq idx %d, vport_id %d, tc %d, wrr_grp %d, rl_valid %d\n",
			   qm_info->start_pq + i, pq->vport_id, pq->tc_id, pq->wrr_group, pq->rl_valid);
	}
}
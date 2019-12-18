#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_qm_info {int /*<<< orphan*/  qm_vport_params; int /*<<< orphan*/  qm_pq_params; int /*<<< orphan*/  pf_rl; int /*<<< orphan*/  pf_wfq; int /*<<< orphan*/  num_vports; int /*<<< orphan*/  start_vport; scalar_t__ num_vf_pqs; scalar_t__ num_pqs; int /*<<< orphan*/  start_pq; int /*<<< orphan*/  max_phys_tcs_per_port; } ;
struct ecore_qm_iids {int /*<<< orphan*/  tids; int /*<<< orphan*/  vf_cids; int /*<<< orphan*/  cids; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_link_state {int /*<<< orphan*/  speed; } ;
struct ecore_hwfn {struct ecore_qm_info qm_info; int /*<<< orphan*/  rel_pf_id; int /*<<< orphan*/  port_id; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  iids ;
struct TYPE_4__ {TYPE_1__* mcp_info; } ;
struct TYPE_3__ {struct ecore_mcp_link_state link_output; } ;

/* Variables and functions */
 TYPE_2__* ECORE_LEADING_HWFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_qm_iids*,int) ; 
 int /*<<< orphan*/  ecore_cxt_qm_iids (struct ecore_hwfn*,struct ecore_qm_iids*) ; 
 int /*<<< orphan*/  ecore_qm_pf_rt_init (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ecore_qm_init_pf(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		      bool is_pf_loading)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;
	struct ecore_mcp_link_state *p_link;
	struct ecore_qm_iids iids;

	OSAL_MEM_ZERO(&iids, sizeof(iids));
	ecore_cxt_qm_iids(p_hwfn, &iids);

	p_link = &ECORE_LEADING_HWFN(p_hwfn->p_dev)->mcp_info->link_output;

	ecore_qm_pf_rt_init(p_hwfn, p_ptt, p_hwfn->port_id,
			    p_hwfn->rel_pf_id, qm_info->max_phys_tcs_per_port,
			    is_pf_loading,
			    iids.cids, iids.vf_cids, iids.tids,
			    qm_info->start_pq,
			    qm_info->num_pqs - qm_info->num_vf_pqs,
			    qm_info->num_vf_pqs,
			    qm_info->start_vport,
			    qm_info->num_vports, qm_info->pf_wfq,
			    qm_info->pf_rl, p_link->speed,
			    p_hwfn->qm_info.qm_pq_params,
			    p_hwfn->qm_info.qm_vport_params);
}
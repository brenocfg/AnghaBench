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
typedef  int u32 ;
struct init_qm_vport_params {int vport_wfq; int /*<<< orphan*/  first_tx_pq_id; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_4__ {int num_vports; TYPE_1__* wfq_data; struct init_qm_vport_params* qm_vport_params; } ;
struct ecore_hwfn {TYPE_2__ qm_info; } ;
struct TYPE_3__ {int min_speed; } ;

/* Variables and functions */
 int ECORE_WFQ_UNIT ; 
 int /*<<< orphan*/  ecore_init_vport_wfq (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_configure_wfq_for_all_vports(struct ecore_hwfn *p_hwfn,
					       struct ecore_ptt *p_ptt,
					       u32 min_pf_rate)
{
	struct init_qm_vport_params *vport_params;
	int i;

	vport_params = p_hwfn->qm_info.qm_vport_params;

	for (i = 0; i < p_hwfn->qm_info.num_vports; i++) {
		u32 wfq_speed = p_hwfn->qm_info.wfq_data[i].min_speed;

		vport_params[i].vport_wfq = (wfq_speed * ECORE_WFQ_UNIT) /
					    min_pf_rate;
		ecore_init_vport_wfq(p_hwfn, p_ptt,
				     vport_params[i].first_tx_pq_id,
				     vport_params[i].vport_wfq);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_link_state {int /*<<< orphan*/  min_pf_rate; } ;
struct TYPE_10__ {TYPE_4__* wfq_data; } ;
struct ecore_hwfn {TYPE_5__ qm_info; TYPE_3__* p_dev; } ;
struct TYPE_9__ {int configured; int /*<<< orphan*/  min_speed; } ;
struct TYPE_8__ {TYPE_2__* hwfns; } ;
struct TYPE_7__ {TYPE_1__* mcp_info; } ;
struct TYPE_6__ {struct ecore_mcp_link_state link_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ecore_configure_wfq_for_all_vports (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int ecore_init_wfq_param (struct ecore_hwfn*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ecore_configure_vport_wfq(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt,
				       u16 vp_id, u32 rate)
{
	struct ecore_mcp_link_state *p_link;
	int rc = ECORE_SUCCESS;

	p_link = &p_hwfn->p_dev->hwfns[0].mcp_info->link_output;

	if (!p_link->min_pf_rate) {
		p_hwfn->qm_info.wfq_data[vp_id].min_speed = rate;
		p_hwfn->qm_info.wfq_data[vp_id].configured = true;
		return rc;
	}

	rc = ecore_init_wfq_param(p_hwfn, vp_id, rate, p_link->min_pf_rate);

	if (rc == ECORE_SUCCESS)
		ecore_configure_wfq_for_all_vports(p_hwfn, p_ptt,
						   p_link->min_pf_rate);
	else
		DP_NOTICE(p_hwfn, false,
			  "Validation failed while configuring min rate\n");

	return rc;
}
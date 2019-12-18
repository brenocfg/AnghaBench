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
typedef  int u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_link_state {int line_speed; int min_pf_rate; } ;
struct TYPE_6__ {int pf_wfq; } ;
struct ecore_hwfn {int /*<<< orphan*/  rel_pf_id; TYPE_3__ qm_info; TYPE_2__* mcp_info; } ;
struct TYPE_4__ {int bandwidth_min; } ;
struct TYPE_5__ {TYPE_1__ func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_LINK ; 
 int ECORE_SUCCESS ; 
 int ecore_init_pf_wfq (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

int __ecore_configure_pf_min_bandwidth(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt,
				       struct ecore_mcp_link_state *p_link,
				       u8 min_bw)
{
	int rc = ECORE_SUCCESS;

	p_hwfn->mcp_info->func_info.bandwidth_min = min_bw;
	p_hwfn->qm_info.pf_wfq = min_bw;

	if (!p_link->line_speed)
		return rc;

	p_link->min_pf_rate = (p_link->line_speed * min_bw) / 100;

	rc = ecore_init_pf_wfq(p_hwfn, p_ptt, p_hwfn->rel_pf_id, min_bw);

	DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
		   "Configured MIN bandwidth to be %d Mb/sec\n",
		   p_link->min_pf_rate);

	return rc;
}
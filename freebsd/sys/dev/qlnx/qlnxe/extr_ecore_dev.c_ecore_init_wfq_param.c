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
typedef  int u16 ;
struct TYPE_4__ {int num_vports; TYPE_1__* wfq_data; } ;
struct ecore_hwfn {TYPE_2__ qm_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {int configured; int min_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_LINK ; 
 int ECORE_SUCCESS ; 
 int ECORE_WFQ_UNIT ; 

__attribute__((used)) static enum _ecore_status_t ecore_init_wfq_param(struct ecore_hwfn *p_hwfn,
						 u16 vport_id, u32 req_rate,
						 u32 min_pf_rate)
{
	u32 total_req_min_rate = 0, total_left_rate = 0, left_rate_per_vp = 0;
	int non_requested_count = 0, req_count = 0, i, num_vports;

	num_vports = p_hwfn->qm_info.num_vports;

	/* Accounting for the vports which are configured for WFQ explicitly */
	for (i = 0; i < num_vports; i++) {
		u32 tmp_speed;

		if ((i != vport_id) && p_hwfn->qm_info.wfq_data[i].configured) {
			req_count++;
			tmp_speed = p_hwfn->qm_info.wfq_data[i].min_speed;
			total_req_min_rate += tmp_speed;
		}
	}

	/* Include current vport data as well */
	req_count++;
	total_req_min_rate += req_rate;
	non_requested_count = num_vports - req_count;

	/* validate possible error cases */
	if (req_rate < min_pf_rate / ECORE_WFQ_UNIT) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
			   "Vport [%d] - Requested rate[%d Mbps] is less than one percent of configured PF min rate[%d Mbps]\n",
			   vport_id, req_rate, min_pf_rate);
		return ECORE_INVAL;
	}

	/* TBD - for number of vports greater than 100 */
	if (num_vports > ECORE_WFQ_UNIT) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
			   "Number of vports is greater than %d\n",
			   ECORE_WFQ_UNIT);
		return ECORE_INVAL;
	}

	if (total_req_min_rate > min_pf_rate) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
			   "Total requested min rate for all vports[%d Mbps] is greater than configured PF min rate[%d Mbps]\n",
			   total_req_min_rate, min_pf_rate);
		return ECORE_INVAL;
	}

	/* Data left for non requested vports */
	total_left_rate = min_pf_rate - total_req_min_rate;
	left_rate_per_vp = total_left_rate / non_requested_count;

	/* validate if non requested get < 1% of min bw */
	if (left_rate_per_vp < min_pf_rate / ECORE_WFQ_UNIT) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
			   "Non WFQ configured vports rate [%d Mbps] is less than one percent of configured PF min rate[%d Mbps]\n",
			   left_rate_per_vp, min_pf_rate);
		return ECORE_INVAL;
	}

	/* now req_rate for given vport passes all scenarios.
	 * assign final wfq rates to all vports.
	 */
	p_hwfn->qm_info.wfq_data[vport_id].min_speed = req_rate;
	p_hwfn->qm_info.wfq_data[vport_id].configured = true;

	for (i = 0; i < num_vports; i++) {
		if (p_hwfn->qm_info.wfq_data[i].configured)
			continue;

		p_hwfn->qm_info.wfq_data[i].min_speed = left_rate_per_vp;
	}

	return ECORE_SUCCESS;
}
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
struct ecore_ptt {int dummy; } ;
struct ecore_mdump_retain_data {int /*<<< orphan*/  status; int /*<<< orphan*/  pf; int /*<<< orphan*/  epoch; scalar_t__ valid; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ allow_mdump; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 int /*<<< orphan*/  ECORE_HW_ERR_HW_ATTN ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (TYPE_1__*) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ecore_hw_err_notify (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_mcp_mdump_ack (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_mcp_mdump_get_retain (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mdump_retain_data*) ; 

__attribute__((used)) static void ecore_mcp_handle_critical_error(struct ecore_hwfn *p_hwfn,
					    struct ecore_ptt *p_ptt)
{
	struct ecore_mdump_retain_data mdump_retain;
	enum _ecore_status_t rc;

	/* In CMT mode - no need for more than a single acknowledgement to the
	 * MFW, and no more than a single notification to the upper driver.
	 */
	if (p_hwfn != ECORE_LEADING_HWFN(p_hwfn->p_dev))
		return;

	rc = ecore_mcp_mdump_get_retain(p_hwfn, p_ptt, &mdump_retain);
	if (rc == ECORE_SUCCESS && mdump_retain.valid) {
		DP_NOTICE(p_hwfn, false,
			  "The MFW notified that a critical error occurred in the device [epoch 0x%08x, pf 0x%x, status 0x%08x]\n",
			  mdump_retain.epoch, mdump_retain.pf,
			  mdump_retain.status);
	} else {
		DP_NOTICE(p_hwfn, false,
			  "The MFW notified that a critical error occurred in the device\n");
	}

	if (p_hwfn->p_dev->allow_mdump) {
		DP_NOTICE(p_hwfn, false,
			  "Not acknowledging the notification to allow the MFW crash dump\n");
		return;
	}

	DP_NOTICE(p_hwfn, false,
		  "Acknowledging the notification to not allow the MFW crash dump [driver debug data collection is preferable]\n");
	ecore_mcp_mdump_ack(p_hwfn, p_ptt);
	ecore_hw_err_notify(p_hwfn, ECORE_HW_ERR_HW_ATTN);
}
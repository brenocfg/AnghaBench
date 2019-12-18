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
struct ecore_hwfn {TYPE_1__* p_dev; } ;
typedef  enum ecore_hw_err_type { ____Placeholder_ecore_hw_err_type } ecore_hw_err_type ;
struct TYPE_2__ {scalar_t__ recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int ECORE_HW_ERR_FAN_FAIL ; 
 int /*<<< orphan*/  ECORE_MSG_DRV ; 
 int /*<<< orphan*/  OSAL_HW_ERROR_OCCURRED (struct ecore_hwfn*,int) ; 

void ecore_hw_err_notify(struct ecore_hwfn *p_hwfn,
			 enum ecore_hw_err_type err_type)
{
	/* Fan failure cannot be masked by handling of another HW error */
	if (p_hwfn->p_dev->recov_in_prog && err_type != ECORE_HW_ERR_FAN_FAIL) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_DRV,
			   "Recovery is in progress. Avoid notifying about HW error %d.\n",
			   err_type);
		return;
	}

	OSAL_HW_ERROR_OCCURRED(p_hwfn, err_type);
}
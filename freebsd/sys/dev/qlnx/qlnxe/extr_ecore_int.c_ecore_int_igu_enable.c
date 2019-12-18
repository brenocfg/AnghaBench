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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int b_int_requested; int b_int_enabled; } ;
typedef  enum ecore_int_mode { ____Placeholder_ecore_int_mode } ecore_int_mode ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_INT_MODE_INTA ; 
 int ECORE_NORESOURCES ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_LEAD_HWFN (struct ecore_hwfn*) ; 
 int OSAL_SLOWPATH_IRQ_REQ (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_int_igu_enable_attn (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_int_igu_enable_int (struct ecore_hwfn*,struct ecore_ptt*,int) ; 

enum _ecore_status_t
ecore_int_igu_enable(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			  enum ecore_int_mode int_mode)
{
	enum _ecore_status_t rc = ECORE_SUCCESS;

	ecore_int_igu_enable_attn(p_hwfn, p_ptt);

	if ((int_mode != ECORE_INT_MODE_INTA) || IS_LEAD_HWFN(p_hwfn)) {
		rc = OSAL_SLOWPATH_IRQ_REQ(p_hwfn);
		if (rc != ECORE_SUCCESS) {
			DP_NOTICE(p_hwfn, true, "Slowpath IRQ request failed\n");
			return ECORE_NORESOURCES;
		}
		p_hwfn->b_int_requested = true;
	}

	/* Enable interrupt Generation */
	ecore_int_igu_enable_int(p_hwfn, p_ptt, int_mode);

	p_hwfn->b_int_enabled = 1;

	return rc;
}
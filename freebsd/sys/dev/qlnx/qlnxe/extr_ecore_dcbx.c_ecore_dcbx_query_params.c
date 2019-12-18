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
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
struct ecore_dcbx_get {int dummy; } ;
typedef  enum ecore_mib_read_type { ____Placeholder_ecore_mib_read_type } ecore_mib_read_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_dcbx_get_dscp_params (struct ecore_hwfn*,struct ecore_dcbx_get*) ; 
 int ecore_dcbx_get_params (struct ecore_hwfn*,struct ecore_dcbx_get*,int) ; 
 int ecore_dcbx_read_mib (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

enum _ecore_status_t ecore_dcbx_query_params(struct ecore_hwfn *p_hwfn,
					     struct ecore_dcbx_get *p_get,
					     enum ecore_mib_read_type type)
{
	struct ecore_ptt *p_ptt;
	enum _ecore_status_t rc;

	if (IS_VF(p_hwfn->p_dev))
		return ECORE_INVAL;

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return ECORE_TIMEOUT;

	rc = ecore_dcbx_read_mib(p_hwfn, p_ptt, type);
	if (rc != ECORE_SUCCESS)
		goto out;

	ecore_dcbx_get_dscp_params(p_hwfn, p_get);

	rc = ecore_dcbx_get_params(p_hwfn, p_get, type);

out:
	ecore_ptt_release(p_hwfn, p_ptt);
	return rc;
}
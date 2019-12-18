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
typedef  scalar_t__ u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dev {int /*<<< orphan*/  mf_bits; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ ECORE_IS_E4 (struct ecore_dev*) ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (struct ecore_dev*) ; 
 int /*<<< orphan*/  ECORE_MF_LLH_MAC_CLSS ; 
 int /*<<< orphan*/  ECORE_MF_LLH_PROTO_CLSS ; 
 int ECORE_SUCCESS ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 struct ecore_ptt* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_abs_ppfid (struct ecore_dev*,scalar_t__,scalar_t__*) ; 
 int ecore_llh_remove_filter_e4 (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__) ; 
 int ecore_llh_remove_filter_e5 (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__) ; 
 int ecore_llh_shadow_remove_all_filters (struct ecore_dev*,scalar_t__) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

void ecore_llh_clear_ppfid_filters(struct ecore_dev *p_dev, u8 ppfid)
{
	struct ecore_hwfn *p_hwfn = ECORE_LEADING_HWFN(p_dev);
	struct ecore_ptt *p_ptt = ecore_ptt_acquire(p_hwfn);
	u8 filter_idx, abs_ppfid;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	if (p_ptt == OSAL_NULL)
		return;

	if (!OSAL_TEST_BIT(ECORE_MF_LLH_PROTO_CLSS, &p_dev->mf_bits) &&
	    !OSAL_TEST_BIT(ECORE_MF_LLH_MAC_CLSS, &p_dev->mf_bits))
		goto out;

	rc = ecore_abs_ppfid(p_dev, ppfid, &abs_ppfid);
	if (rc != ECORE_SUCCESS)
		goto out;

	rc = ecore_llh_shadow_remove_all_filters(p_dev, ppfid);
	if (rc != ECORE_SUCCESS)
		goto out;

	for (filter_idx = 0; filter_idx < NIG_REG_LLH_FUNC_FILTER_EN_SIZE;
	     filter_idx++) {
		if (ECORE_IS_E4(p_dev))
			rc = ecore_llh_remove_filter_e4(p_hwfn, p_ptt,
							abs_ppfid, filter_idx);
		else /* E5 */
			rc = ecore_llh_remove_filter_e5(p_hwfn, p_ptt,
							abs_ppfid, filter_idx);
		if (rc != ECORE_SUCCESS)
			goto out;
	}
out:
	ecore_ptt_release(p_hwfn, p_ptt);
}
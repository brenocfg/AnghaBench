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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dev {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_AGAIN ; 
 scalar_t__ ECORE_IS_E4 (struct ecore_dev*) ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (struct ecore_dev*) ; 
 struct ecore_ptt* OSAL_NULL ; 
 int ecore_llh_dump_ppfid_e4 (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int ecore_llh_dump_ppfid_e5 (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

enum _ecore_status_t ecore_llh_dump_ppfid(struct ecore_dev *p_dev, u8 ppfid)
{
	struct ecore_hwfn *p_hwfn = ECORE_LEADING_HWFN(p_dev);
	struct ecore_ptt *p_ptt = ecore_ptt_acquire(p_hwfn);
	enum _ecore_status_t rc;

	if (p_ptt == OSAL_NULL)
		return ECORE_AGAIN;

	if (ECORE_IS_E4(p_dev))
		rc = ecore_llh_dump_ppfid_e4(p_hwfn, p_ptt, ppfid);
	else /* E5 */
		rc = ecore_llh_dump_ppfid_e5(p_hwfn, p_ptt, ppfid);

	ecore_ptt_release(p_hwfn, p_ptt);

	return rc;
}
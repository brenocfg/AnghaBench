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
struct ecore_hwfn {struct ecore_ptt* p_main_ptt; } ;
struct ecore_dev {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (struct ecore_dev*) ; 
 int /*<<< orphan*/  ECORE_RECOVERY_PROLOG_SLEEP_MS ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 int ecore_pglueb_set_pfid_enable (struct ecore_hwfn*,struct ecore_ptt*,int) ; 

enum _ecore_status_t ecore_recovery_prolog(struct ecore_dev *p_dev)
{
	struct ecore_hwfn *p_hwfn = ECORE_LEADING_HWFN(p_dev);
	struct ecore_ptt *p_ptt = p_hwfn->p_main_ptt;
	enum _ecore_status_t rc;

	/* Allow ongoing PCIe transactions to complete */
	OSAL_MSLEEP(ECORE_RECOVERY_PROLOG_SLEEP_MS);

	/* Clear the PF's internal FID_enable in the PXP */
	rc = ecore_pglueb_set_pfid_enable(p_hwfn, p_ptt, false);
	if (rc != ECORE_SUCCESS)
		DP_NOTICE(p_hwfn, false,
			  "ecore_pglueb_set_pfid_enable() failed. rc = %d.\n",
			  rc);

	return rc;
}
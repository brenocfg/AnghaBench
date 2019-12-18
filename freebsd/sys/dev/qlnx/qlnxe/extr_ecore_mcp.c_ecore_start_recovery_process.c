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
struct ecore_hwfn {struct ecore_dev* p_dev; } ;
struct ecore_dev {scalar_t__ recov_in_prog; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_AGAIN ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  MISC_REG_AEU_GENERAL_ATTN_35 ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_start_recovery_process(struct ecore_hwfn *p_hwfn,
						  struct ecore_ptt *p_ptt)
{
	struct ecore_dev *p_dev = p_hwfn->p_dev;

	if (p_dev->recov_in_prog) {
		DP_NOTICE(p_hwfn, false,
			  "Avoid triggering a recovery since such a process is already in progress\n");
		return ECORE_AGAIN;
	}

	DP_NOTICE(p_hwfn, false, "Triggering a recovery process\n");
	ecore_wr(p_hwfn, p_ptt, MISC_REG_AEU_GENERAL_ATTN_35, 0x1);

	return ECORE_SUCCESS;
}
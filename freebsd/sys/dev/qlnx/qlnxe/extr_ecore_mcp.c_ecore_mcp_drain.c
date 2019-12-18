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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MSG_CODE_NIG_DRAIN ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_mcp_drain(struct ecore_hwfn *p_hwfn,
				     struct ecore_ptt *p_ptt)
{
	u32 resp = 0, param = 0;
	enum _ecore_status_t rc;

	rc = ecore_mcp_cmd(p_hwfn, p_ptt,
			   DRV_MSG_CODE_NIG_DRAIN, 1000,
			   &resp, &param);

	/* Wait for the drain to complete before returning */
	OSAL_MSLEEP(1020);

	return rc;
}
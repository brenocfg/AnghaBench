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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 int VF_MAX_STATIC ; 
 int /*<<< orphan*/  ecore_iov_execute_vf_flr_cleanup (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_mcp_ack_vf_flr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ *) ; 

enum _ecore_status_t
ecore_iov_single_vf_flr_cleanup(struct ecore_hwfn *p_hwfn,
				struct ecore_ptt  *p_ptt,
				u16		  rel_vf_id)

{
	u32 ack_vfs[VF_MAX_STATIC / 32];
	enum _ecore_status_t rc = ECORE_SUCCESS;

	OSAL_MEMSET(ack_vfs, 0, sizeof(u32) * (VF_MAX_STATIC / 32));

	/* Wait instead of polling the BRB <-> PRS interface */
	OSAL_MSLEEP(100);

	ecore_iov_execute_vf_flr_cleanup(p_hwfn, p_ptt, rel_vf_id, ack_vfs);

	rc = ecore_mcp_ack_vf_flr(p_hwfn, p_ptt, ack_vfs);
	return rc;
}
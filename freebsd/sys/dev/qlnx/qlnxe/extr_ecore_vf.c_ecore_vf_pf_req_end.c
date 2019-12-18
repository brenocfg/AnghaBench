#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union pfvf_tlvs {TYPE_2__ default_resp; } ;
struct ecore_hwfn {TYPE_3__* vf_iov_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; union pfvf_tlvs* pf2vf_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/  OSAL_MUTEX_RELEASE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecore_vf_pf_req_end(struct ecore_hwfn *p_hwfn,
				 enum _ecore_status_t req_status)
{
	union pfvf_tlvs *resp = p_hwfn->vf_iov_info->pf2vf_reply;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "VF request status = 0x%x, PF reply status = 0x%x\n",
		   req_status, resp->default_resp.hdr.status);

	OSAL_MUTEX_RELEASE(&(p_hwfn->vf_iov_info->mutex));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  mbx_state; } ;
struct TYPE_4__ {TYPE_1__ sw_mbx; } ;
struct ecore_vf_info {TYPE_2__ vf_mbx; void* ctx; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 struct ecore_vf_info* OSAL_NULL ; 
 int /*<<< orphan*/  VF_PF_WAIT_FOR_START_REQUEST ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_iov_set_vf_ctx(struct ecore_hwfn *p_hwfn,
					  u16		    vf_id,
					  void		    *ctx)
{
	enum _ecore_status_t rc = ECORE_SUCCESS;
	struct ecore_vf_info *vf = ecore_iov_get_vf_info(p_hwfn, vf_id, true);

	if (vf != OSAL_NULL) {
		vf->ctx = ctx;
#ifdef CONFIG_ECORE_SW_CHANNEL
		vf->vf_mbx.sw_mbx.mbx_state = VF_PF_WAIT_FOR_START_REQUEST;
#endif
	} else {
		rc = ECORE_UNKNOWN_ERROR;
	}
	return rc;
}
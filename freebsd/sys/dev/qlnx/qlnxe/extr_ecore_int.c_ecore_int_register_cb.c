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
typedef  size_t u8 ;
struct TYPE_5__ {TYPE_1__* sb_virt; } ;
struct ecore_sb_sp_info {TYPE_2__ sb_info; TYPE_3__* pi_info_arr; } ;
struct ecore_hwfn {struct ecore_sb_sp_info* p_sp_sb; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  scalar_t__ ecore_int_comp_cb_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {scalar_t__ comp_cb; void* cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pi_array; } ;

/* Variables and functions */
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 size_t OSAL_ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ OSAL_NULL ; 

enum _ecore_status_t ecore_int_register_cb(struct ecore_hwfn *p_hwfn,
					   ecore_int_comp_cb_t comp_cb,
					   void *cookie,
					   u8 *sb_idx,
					   __le16 **p_fw_cons)
{
	struct ecore_sb_sp_info *p_sp_sb  = p_hwfn->p_sp_sb;
	enum _ecore_status_t rc = ECORE_NOMEM;
	u8 pi;

	/* Look for a free index */
	for (pi = 0; pi < OSAL_ARRAY_SIZE(p_sp_sb->pi_info_arr); pi++) {
		if (p_sp_sb->pi_info_arr[pi].comp_cb != OSAL_NULL)
			continue;

		p_sp_sb->pi_info_arr[pi].comp_cb = comp_cb;
		p_sp_sb->pi_info_arr[pi].cookie = cookie;
		*sb_idx = pi;
		*p_fw_cons = &p_sp_sb->sb_info.sb_virt->pi_array[pi];
		rc = ECORE_SUCCESS;
		break;
	}

	return rc;
}
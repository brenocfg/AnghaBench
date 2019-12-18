#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ecore_sb_sp_info {TYPE_1__* pi_info_arr; } ;
struct ecore_hwfn {struct ecore_sb_sp_info* p_sp_sb; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ comp_cb; scalar_t__ cookie; } ;

/* Variables and functions */
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 scalar_t__ OSAL_NULL ; 

enum _ecore_status_t ecore_int_unregister_cb(struct ecore_hwfn *p_hwfn,
					     u8 pi)
{
	struct ecore_sb_sp_info *p_sp_sb = p_hwfn->p_sp_sb;

	if (p_sp_sb->pi_info_arr[pi].comp_cb == OSAL_NULL)
		return ECORE_NOMEM;

	p_sp_sb->pi_info_arr[pi].comp_cb = OSAL_NULL;
	p_sp_sb->pi_info_arr[pi].cookie = OSAL_NULL;

	return ECORE_SUCCESS;
}
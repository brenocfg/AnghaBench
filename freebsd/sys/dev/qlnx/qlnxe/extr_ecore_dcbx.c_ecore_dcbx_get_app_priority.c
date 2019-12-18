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
typedef  int u8 ;
typedef  int u32 ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_MAX_PFC_PRIORITIES ; 
 int ECORE_SUCCESS ; 

__attribute__((used)) static enum _ecore_status_t
ecore_dcbx_get_app_priority(u8 pri_bitmap, u8 *priority)
{
	u32 pri_mask, pri = ECORE_MAX_PFC_PRIORITIES;
	u32 index = ECORE_MAX_PFC_PRIORITIES - 1;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	/* Bitmap 1 corresponds to priority 0, return priority 0 */
	if (pri_bitmap == 1) {
		*priority = 0;
		return rc;
	}

	/* Choose the highest priority */
	while ((ECORE_MAX_PFC_PRIORITIES == pri) && index) {
		pri_mask = 1 << index;
		if (pri_bitmap & pri_mask)
			pri = index;
		index--;
	}

	if (pri < ECORE_MAX_PFC_PRIORITIES)
		*priority = (u8)pri;
	else
		rc = ECORE_INVAL;

	return rc;
}
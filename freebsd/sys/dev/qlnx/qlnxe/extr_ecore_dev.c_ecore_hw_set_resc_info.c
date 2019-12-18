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
typedef  scalar_t__ u8 ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ ECORE_MAX_RESC ; 
 int ECORE_SUCCESS ; 
 int __ecore_hw_set_resc_info (struct ecore_hwfn*,scalar_t__,int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_hw_set_resc_info(struct ecore_hwfn *p_hwfn,
						   bool drv_resc_alloc)
{
	enum _ecore_status_t rc;
	u8 res_id;

	for (res_id = 0; res_id < ECORE_MAX_RESC; res_id++) {
		rc = __ecore_hw_set_resc_info(p_hwfn, res_id, drv_resc_alloc);
		if (rc != ECORE_SUCCESS)
			return rc;
	}

	return ECORE_SUCCESS;
}
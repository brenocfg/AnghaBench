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
typedef  union ecore_llh_filter {int dummy; } ecore_llh_filter ;
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ecore_llh_info {struct ecore_llh_filter_info** pp_filters; } ;
struct ecore_llh_filter_info {int b_enabled; int type; scalar_t__ ref_cnt; int /*<<< orphan*/  filter; } ;
struct ecore_dev {struct ecore_llh_info* p_llh_info; } ;
typedef  enum ecore_llh_filter_type { ____Placeholder_ecore_llh_filter_type } ecore_llh_filter_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ *,union ecore_llh_filter*,int) ; 
 int ecore_llh_shadow_sanity (struct ecore_dev*,size_t,size_t,char*) ; 

__attribute__((used)) static enum _ecore_status_t
__ecore_llh_shadow_add_filter(struct ecore_dev *p_dev, u8 ppfid, u8 filter_idx,
			      enum ecore_llh_filter_type type,
			      union ecore_llh_filter *p_filter, u32 *p_ref_cnt)
{
	struct ecore_llh_info *p_llh_info = p_dev->p_llh_info;
	struct ecore_llh_filter_info *p_filters;
	enum _ecore_status_t rc;

	rc = ecore_llh_shadow_sanity(p_dev, ppfid, filter_idx, "add");
	if (rc != ECORE_SUCCESS)
		return rc;

	p_filters = p_llh_info->pp_filters[ppfid];
	if (!p_filters[filter_idx].ref_cnt) {
		p_filters[filter_idx].b_enabled = true;
		p_filters[filter_idx].type = type;
		OSAL_MEMCPY(&p_filters[filter_idx].filter, p_filter,
			    sizeof(p_filters[filter_idx].filter));
	}

	*p_ref_cnt = ++p_filters[filter_idx].ref_cnt;

	return ECORE_SUCCESS;
}
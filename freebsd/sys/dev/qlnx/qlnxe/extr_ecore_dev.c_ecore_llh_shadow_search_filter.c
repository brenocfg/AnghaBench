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
struct ecore_llh_info {struct ecore_llh_filter_info** pp_filters; } ;
struct ecore_llh_filter_info {int /*<<< orphan*/  filter; } ;
struct ecore_dev {struct ecore_llh_info* p_llh_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 size_t ECORE_LLH_INVALID_FILTER_IDX ; 
 int ECORE_SUCCESS ; 
 size_t NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 
 int /*<<< orphan*/  OSAL_MEMCMP (union ecore_llh_filter*,int /*<<< orphan*/ *,int) ; 
 int ecore_llh_shadow_sanity (struct ecore_dev*,size_t,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_llh_shadow_search_filter(struct ecore_dev *p_dev, u8 ppfid,
			       union ecore_llh_filter *p_filter,
			       u8 *p_filter_idx)
{
	struct ecore_llh_info *p_llh_info = p_dev->p_llh_info;
	struct ecore_llh_filter_info *p_filters;
	enum _ecore_status_t rc;
	u8 i;

	rc = ecore_llh_shadow_sanity(p_dev, ppfid, 0, "search");
	if (rc != ECORE_SUCCESS)
		return rc;

	*p_filter_idx = ECORE_LLH_INVALID_FILTER_IDX;

	p_filters = p_llh_info->pp_filters[ppfid];
	for (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) {
		if (!OSAL_MEMCMP(p_filter, &p_filters[i].filter,
				 sizeof(*p_filter))) {
			*p_filter_idx = i;
			break;
		}
	}

	return ECORE_SUCCESS;
}
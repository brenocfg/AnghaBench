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
struct ecore_llh_info {scalar_t__ num_ppfid; } ;
struct ecore_dev {struct ecore_llh_info* p_llh_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,char const*,scalar_t__,scalar_t__) ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN_SIZE ; 

__attribute__((used)) static enum _ecore_status_t ecore_llh_shadow_sanity(struct ecore_dev *p_dev,
						    u8 ppfid, u8 filter_idx,
						    const char *action)
{
	struct ecore_llh_info *p_llh_info = p_dev->p_llh_info;

	if (ppfid >= p_llh_info->num_ppfid) {
		DP_NOTICE(p_dev, false,
			  "LLH shadow [%s]: using ppfid %d while only %d ppfids are available\n",
			  action, ppfid, p_llh_info->num_ppfid);
		return ECORE_INVAL;
	}

	if (filter_idx >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE) {
		DP_NOTICE(p_dev, false,
			  "LLH shadow [%s]: using filter_idx %d while only %d filters are available\n",
			  action, filter_idx, NIG_REG_LLH_FUNC_FILTER_EN_SIZE);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}
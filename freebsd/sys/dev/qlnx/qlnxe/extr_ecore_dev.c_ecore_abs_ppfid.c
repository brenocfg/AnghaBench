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
typedef  size_t u8 ;
struct ecore_llh_info {size_t num_ppfid; size_t* ppfid_array; } ;
struct ecore_dev {struct ecore_llh_info* p_llh_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,size_t,size_t) ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 

__attribute__((used)) static enum _ecore_status_t ecore_abs_ppfid(struct ecore_dev *p_dev,
					    u8 rel_ppfid, u8 *p_abs_ppfid)
{
	struct ecore_llh_info *p_llh_info = p_dev->p_llh_info;

	if (rel_ppfid >= p_llh_info->num_ppfid) {
		DP_NOTICE(p_dev, false,
			  "rel_ppfid %d is not valid, available indices are 0..%hhd\n",
			  rel_ppfid, (u8)(p_llh_info->num_ppfid - 1));
		return ECORE_INVAL;
	}

	*p_abs_ppfid = p_llh_info->ppfid_array[rel_ppfid];

	return ECORE_SUCCESS;
}
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
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_RSS_ENG ; 
 int ECORE_SUCCESS ; 
 scalar_t__ RESC_NUM (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ RESC_START (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_fw_rss_eng(struct ecore_hwfn *p_hwfn,
				      u8 src_id, u8 *dst_id)
{
	if (src_id >= RESC_NUM(p_hwfn, ECORE_RSS_ENG)) {
		u8 min, max;

		min = (u8)RESC_START(p_hwfn, ECORE_RSS_ENG);
		max = min + RESC_NUM(p_hwfn, ECORE_RSS_ENG);
		DP_NOTICE(p_hwfn, true, "rss_eng id [%d] is not valid, available indices [%d - %d]\n",
			  src_id, min, max);

		return ECORE_INVAL;
	}

	*dst_id = RESC_START(p_hwfn, ECORE_RSS_ENG) + src_id;

	return ECORE_SUCCESS;
}
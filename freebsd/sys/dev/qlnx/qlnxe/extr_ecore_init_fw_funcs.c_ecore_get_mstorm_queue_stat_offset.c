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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_NUM_PFS ; 
 int MSTORM_QUEUE_STAT_OFFSET (scalar_t__) ; 
 int MSTORM_VF_ZONE_DEFAULT_SIZE_LOG ; 
 scalar_t__ VF_ZONE_SIZE_MODE_DEFAULT ; 
 scalar_t__ VF_ZONE_SIZE_MODE_DOUBLE ; 
 scalar_t__ VF_ZONE_SIZE_MODE_QUAD ; 

u32 ecore_get_mstorm_queue_stat_offset(struct ecore_hwfn *p_hwfn, u16 stat_cnt_id, u16 vf_zone_size_mode)
{
	u32 offset = MSTORM_QUEUE_STAT_OFFSET(stat_cnt_id);

	if ((vf_zone_size_mode != VF_ZONE_SIZE_MODE_DEFAULT) && (stat_cnt_id > MAX_NUM_PFS)) {
		if (vf_zone_size_mode == VF_ZONE_SIZE_MODE_DOUBLE)
			offset += (1 << MSTORM_VF_ZONE_DEFAULT_SIZE_LOG) * (stat_cnt_id - MAX_NUM_PFS);
		else if (vf_zone_size_mode == VF_ZONE_SIZE_MODE_QUAD)
			offset += 3 * (1 << MSTORM_VF_ZONE_DEFAULT_SIZE_LOG) * (stat_cnt_id - MAX_NUM_PFS);
	}

	return offset;
}
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
typedef  scalar_t__ u16 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int MSTORM_ETH_VF_PRODS_OFFSET (int,int) ; 
 int MSTORM_VF_ZONE_DEFAULT_SIZE_LOG ; 
 scalar_t__ VF_ZONE_SIZE_MODE_DEFAULT ; 
 scalar_t__ VF_ZONE_SIZE_MODE_DOUBLE ; 
 scalar_t__ VF_ZONE_SIZE_MODE_QUAD ; 

u32 ecore_get_mstorm_eth_vf_prods_offset(struct ecore_hwfn *p_hwfn, u8 vf_id, u8 vf_queue_id, u16 vf_zone_size_mode)
{
	u32 offset = MSTORM_ETH_VF_PRODS_OFFSET(vf_id, vf_queue_id);

	if (vf_zone_size_mode != VF_ZONE_SIZE_MODE_DEFAULT) {
		if (vf_zone_size_mode == VF_ZONE_SIZE_MODE_DOUBLE)
			offset += (1 << MSTORM_VF_ZONE_DEFAULT_SIZE_LOG) * vf_id;
		else if (vf_zone_size_mode == VF_ZONE_SIZE_MODE_QUAD)
			offset += 3 * (1 << MSTORM_VF_ZONE_DEFAULT_SIZE_LOG) * vf_id;
	}

	return offset;
}
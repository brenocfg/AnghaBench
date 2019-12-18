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
typedef  int u8 ;
struct ecore_hwfn {TYPE_1__* vf_iov_info; } ;
struct ecore_bulletin_content {int valid_bitmap; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {struct ecore_bulletin_content bulletin_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int MAC_ADDR_FORCED ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VFPF_BULLETIN_MAC_ADDR ; 

bool ecore_vf_bulletin_get_forced_mac(struct ecore_hwfn *hwfn, u8 *dst_mac,
				      u8 *p_is_forced)
{
	struct ecore_bulletin_content *bulletin;

	bulletin = &hwfn->vf_iov_info->bulletin_shadow;

	if (bulletin->valid_bitmap & (1 << MAC_ADDR_FORCED)) {
		if (p_is_forced)
			*p_is_forced = 1;
	} else if (bulletin->valid_bitmap & (1 << VFPF_BULLETIN_MAC_ADDR)) {
		if (p_is_forced)
			*p_is_forced = 0;
	} else {
		return false;
	}

	OSAL_MEMCPY(dst_mac, bulletin->mac, ETH_ALEN);

	return true;
}
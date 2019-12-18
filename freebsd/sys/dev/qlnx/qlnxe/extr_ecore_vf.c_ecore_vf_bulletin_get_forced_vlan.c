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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_hwfn {TYPE_1__* vf_iov_info; } ;
struct ecore_bulletin_content {int valid_bitmap; int /*<<< orphan*/  pvid; } ;
struct TYPE_2__ {struct ecore_bulletin_content bulletin_shadow; } ;

/* Variables and functions */
 int VLAN_ADDR_FORCED ; 

bool ecore_vf_bulletin_get_forced_vlan(struct ecore_hwfn *hwfn, u16 *dst_pvid)
{
	struct ecore_bulletin_content *bulletin;

	bulletin = &hwfn->vf_iov_info->bulletin_shadow;

	if (!(bulletin->valid_bitmap & (1 << VLAN_ADDR_FORCED)))
		return false;

	if (dst_pvid)
		*dst_pvid = bulletin->pvid;

	return true;
}
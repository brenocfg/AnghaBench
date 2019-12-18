#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  size_t u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ldTgtIdToLd; } ;
struct TYPE_5__ {TYPE_1__ raidMap; } ;
typedef  TYPE_2__ MR_DRV_RAID_MAP_ALL ;

/* Variables and functions */

u_int8_t
MR_TargetIdToLdGet(u_int32_t ldTgtId, MR_DRV_RAID_MAP_ALL * map)
{
	return map->raidMap.ldTgtIdToLd[ldTgtId];
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_10__ {TYPE_3__* ldSpanMap; } ;
struct TYPE_11__ {TYPE_4__ raidMap; } ;
struct TYPE_9__ {TYPE_2__* spanBlock; } ;
struct TYPE_7__ {int /*<<< orphan*/  arrayRef; } ;
struct TYPE_8__ {TYPE_1__ span; } ;
typedef  TYPE_5__ MR_DRV_RAID_MAP_ALL ;

/* Variables and functions */

__attribute__((used)) static u_int16_t
MR_LdSpanArrayGet(u_int32_t ld, u_int32_t span, MR_DRV_RAID_MAP_ALL * map)
{
	return map->raidMap.ldSpanMap[ld].spanBlock[span].span.arrayRef;
}
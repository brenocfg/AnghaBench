#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct map_info {scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ window_size; scalar_t__ switch_bank; struct map_info map; } ;
struct adm5120_flash_info {TYPE_1__ amap; TYPE_2__* mtd; } ;
struct TYPE_4__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ BANK_SIZE ; 
 int /*<<< orphan*/  MAP_ERR (struct map_info*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void adm5120_flash_initbanks(struct adm5120_flash_info *info)
{
	struct map_info *map = &info->amap.map;

	if (info->mtd->size <= BANK_SIZE)
		/* no bank switching needed */
		return;

	if (info->amap.switch_bank) {
		info->amap.window_size = info->mtd->size;
		return;
	}

	MAP_ERR(map, "reduce visibility from %ldKiB to %ldKiB\n",
		(unsigned long)map->size >> 10,
		(unsigned long)info->mtd->size >> 10);

	info->mtd->size = info->amap.window_size;
}
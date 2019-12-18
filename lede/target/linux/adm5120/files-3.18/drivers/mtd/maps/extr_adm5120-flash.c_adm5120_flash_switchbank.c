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
struct map_info {int dummy; } ;
struct adm5120_map_info {int /*<<< orphan*/  (* switch_bank ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned long BANK_START_MASK ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  MAP_DBG (struct map_info*,char*,unsigned int,unsigned long) ; 
 struct adm5120_map_info* map_to_amap (struct map_info*) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void adm5120_flash_switchbank(struct map_info *map,
		unsigned long ofs)
{
	struct adm5120_map_info *amap = map_to_amap(map);
	unsigned bank;

	if (amap->switch_bank == NULL)
		return;

	bank = (ofs & BANK_START_MASK) >> 21;
	if (bank > 1)
		BUG();

	MAP_DBG(map, "switching to bank %u, ofs=%lX\n", bank, ofs);
	amap->switch_bank(bank);
}
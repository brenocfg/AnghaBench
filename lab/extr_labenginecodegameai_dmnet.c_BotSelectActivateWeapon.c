#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* inventory; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 size_t INVENTORY_BFG10K ; 
 size_t INVENTORY_BFGAMMO ; 
 size_t INVENTORY_BULLETS ; 
 size_t INVENTORY_CELLS ; 
 size_t INVENTORY_GRENADELAUNCHER ; 
 size_t INVENTORY_GRENADES ; 
 size_t INVENTORY_LIGHTNING ; 
 size_t INVENTORY_LIGHTNINGAMMO ; 
 size_t INVENTORY_MACHINEGUN ; 
 size_t INVENTORY_PLASMAGUN ; 
 size_t INVENTORY_RAILGUN ; 
 size_t INVENTORY_ROCKETLAUNCHER ; 
 size_t INVENTORY_ROCKETS ; 
 size_t INVENTORY_SHELLS ; 
 size_t INVENTORY_SHOTGUN ; 
 size_t INVENTORY_SLUGS ; 
 int WEAPONINDEX_BFG ; 
 int WEAPONINDEX_GRENADE_LAUNCHER ; 
 int WEAPONINDEX_LIGHTNING ; 
 int WEAPONINDEX_MACHINEGUN ; 
 int WEAPONINDEX_PLASMAGUN ; 
 int WEAPONINDEX_RAILGUN ; 
 int WEAPONINDEX_ROCKET_LAUNCHER ; 
 int WEAPONINDEX_SHOTGUN ; 

int BotSelectActivateWeapon(bot_state_t *bs) {
	//
	if (bs->inventory[INVENTORY_MACHINEGUN] > 0 && bs->inventory[INVENTORY_BULLETS] > 0)
		return WEAPONINDEX_MACHINEGUN;
	else if (bs->inventory[INVENTORY_SHOTGUN] > 0 && bs->inventory[INVENTORY_SHELLS] > 0)
		return WEAPONINDEX_SHOTGUN;
	else if (bs->inventory[INVENTORY_PLASMAGUN] > 0 && bs->inventory[INVENTORY_CELLS] > 0)
		return WEAPONINDEX_PLASMAGUN;
	else if (bs->inventory[INVENTORY_LIGHTNING] > 0 && bs->inventory[INVENTORY_LIGHTNINGAMMO] > 0)
		return WEAPONINDEX_LIGHTNING;
#ifdef MISSIONPACK
	else if (bs->inventory[INVENTORY_CHAINGUN] > 0 && bs->inventory[INVENTORY_BELT] > 0)
		return WEAPONINDEX_CHAINGUN;
	else if (bs->inventory[INVENTORY_NAILGUN] > 0 && bs->inventory[INVENTORY_NAILS] > 0)
		return WEAPONINDEX_NAILGUN;
	else if (bs->inventory[INVENTORY_PROXLAUNCHER] > 0 && bs->inventory[INVENTORY_MINES] > 0)
		return WEAPONINDEX_PROXLAUNCHER;
#endif
	else if (bs->inventory[INVENTORY_GRENADELAUNCHER] > 0 && bs->inventory[INVENTORY_GRENADES] > 0)
		return WEAPONINDEX_GRENADE_LAUNCHER;
	else if (bs->inventory[INVENTORY_RAILGUN] > 0 && bs->inventory[INVENTORY_SLUGS] > 0)
		return WEAPONINDEX_RAILGUN;
	else if (bs->inventory[INVENTORY_ROCKETLAUNCHER] > 0 && bs->inventory[INVENTORY_ROCKETS] > 0)
		return WEAPONINDEX_ROCKET_LAUNCHER;
	else if (bs->inventory[INVENTORY_BFG10K] > 0 && bs->inventory[INVENTORY_BFGAMMO] > 0)
		return WEAPONINDEX_BFG;
	else {
		return -1;
	}
}
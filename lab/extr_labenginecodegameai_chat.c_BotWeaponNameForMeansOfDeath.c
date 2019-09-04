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

/* Variables and functions */
#define  MOD_BFG 141 
#define  MOD_BFG_SPLASH 140 
#define  MOD_GAUNTLET 139 
#define  MOD_GRAPPLE 138 
#define  MOD_GRENADE 137 
#define  MOD_GRENADE_SPLASH 136 
#define  MOD_LIGHTNING 135 
#define  MOD_MACHINEGUN 134 
#define  MOD_PLASMA 133 
#define  MOD_PLASMA_SPLASH 132 
#define  MOD_RAILGUN 131 
#define  MOD_ROCKET 130 
#define  MOD_ROCKET_SPLASH 129 
#define  MOD_SHOTGUN 128 

char *BotWeaponNameForMeansOfDeath(int mod) {
	switch(mod) {
		case MOD_SHOTGUN: return "Shotgun";
		case MOD_GAUNTLET: return "Gauntlet";
		case MOD_MACHINEGUN: return "Machinegun";
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH: return "Grenade Launcher";
		case MOD_ROCKET:
		case MOD_ROCKET_SPLASH: return "Rocket Launcher";
		case MOD_PLASMA:
		case MOD_PLASMA_SPLASH: return "Plasmagun";
		case MOD_RAILGUN: return "Railgun";
		case MOD_LIGHTNING: return "Lightning Gun";
		case MOD_BFG:
		case MOD_BFG_SPLASH: return "BFG10K";
#ifdef MISSIONPACK
		case MOD_NAIL: return "Nailgun";
		case MOD_CHAINGUN: return "Chaingun";
		case MOD_PROXIMITY_MINE: return "Proximity Launcher";
		case MOD_KAMIKAZE: return "Kamikaze";
		case MOD_JUICED: return "Prox mine";
#endif
		case MOD_GRAPPLE: return "Grapple";
		default: return "[unknown weapon]";
	}
}
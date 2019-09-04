#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ltgtype; int /*<<< orphan*/  enemy; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  aas_entityinfo_t ;

/* Variables and functions */
 int BotAggression (TYPE_1__*) ; 
 scalar_t__ BotCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotEntityInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EntityCarriesFlag (int /*<<< orphan*/ *) ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ LTG_GETFLAG ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 

int BotWantsToChase(bot_state_t *bs) {
	aas_entityinfo_t entinfo;

	if (gametype == GT_CTF) {
		//never chase when carrying a CTF flag
		if (BotCTFCarryingFlag(bs))
			return qfalse;
		//always chase if the enemy is carrying a flag
		BotEntityInfo(bs->enemy, &entinfo);
		if (EntityCarriesFlag(&entinfo))
			return qtrue;
	}
#ifdef MISSIONPACK
	else if (gametype == GT_1FCTF) {
		//never chase if carrying the flag
		if (Bot1FCTFCarryingFlag(bs))
			return qfalse;
		//always chase if the enemy is carrying a flag
		BotEntityInfo(bs->enemy, &entinfo);
		if (EntityCarriesFlag(&entinfo))
			return qtrue;
	}
	else if (gametype == GT_OBELISK) {
		//the bots should be dedicated to attacking the enemy obelisk
		if (bs->ltgtype == LTG_ATTACKENEMYBASE) {
			if (bs->enemy != redobelisk.entitynum &&
						bs->enemy != blueobelisk.entitynum) {
				return qfalse;
			}
		}
	}
	else if (gametype == GT_HARVESTER) {
		//never chase if carrying cubes
		if (BotHarvesterCarryingCubes(bs)) return qfalse;

		BotEntityInfo(bs->enemy, &entinfo);
		// always chase if the enemy is carrying cubes
		if (EntityCarriesCubes(&entinfo)) return qtrue;
	}
#endif
	//if the bot is getting the flag
	if (bs->ltgtype == LTG_GETFLAG)
		return qfalse;
	//
	if (BotAggression(bs) > 50)
		return qtrue;
	return qfalse;
}
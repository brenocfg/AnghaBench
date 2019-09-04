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
typedef  int /*<<< orphan*/  bot_state_t ;

/* Variables and functions */

void BotSetTeamStatus(bot_state_t *bs) {
#ifdef MISSIONPACK
	int teamtask;
	aas_entityinfo_t entinfo;

	teamtask = TEAMTASK_PATROL;

	switch(bs->ltgtype) {
		case LTG_TEAMHELP:
			break;
		case LTG_TEAMACCOMPANY:
			BotEntityInfo(bs->teammate, &entinfo);
			if ( ( (gametype == GT_CTF || gametype == GT_1FCTF) && EntityCarriesFlag(&entinfo))
				|| ( gametype == GT_HARVESTER && EntityCarriesCubes(&entinfo)) ) {
				teamtask = TEAMTASK_ESCORT;
			}
			else {
				teamtask = TEAMTASK_FOLLOW;
			}
			break;
		case LTG_DEFENDKEYAREA:
			teamtask = TEAMTASK_DEFENSE;
			break;
		case LTG_GETFLAG:
			teamtask = TEAMTASK_OFFENSE;
			break;
		case LTG_RUSHBASE:
			teamtask = TEAMTASK_DEFENSE;
			break;
		case LTG_RETURNFLAG:
			teamtask = TEAMTASK_RETRIEVE;
			break;
		case LTG_CAMP:
		case LTG_CAMPORDER:
			teamtask = TEAMTASK_CAMP;
			break;
		case LTG_PATROL:
			teamtask = TEAMTASK_PATROL;
			break;
		case LTG_GETITEM:
			teamtask = TEAMTASK_PATROL;
			break;
		case LTG_KILL:
			teamtask = TEAMTASK_PATROL;
			break;
		case LTG_HARVEST:
			teamtask = TEAMTASK_OFFENSE;
			break;
		case LTG_ATTACKENEMYBASE:
			teamtask = TEAMTASK_OFFENSE;
			break;
		default:
			teamtask = TEAMTASK_PATROL;
			break;
	}
	BotSetUserInfo(bs, "teamtask", va("%d", teamtask));
#endif
}
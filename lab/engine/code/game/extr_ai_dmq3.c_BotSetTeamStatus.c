#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ltgtype; int /*<<< orphan*/  teammate; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotSetUserInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EntityCarriesCubes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EntityCarriesFlag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GT_1FCTF ; 
 int /*<<< orphan*/  GT_CTF ; 
 int /*<<< orphan*/  GT_HARVESTER ; 
#define  LTG_ATTACKENEMYBASE 140 
#define  LTG_CAMP 139 
#define  LTG_CAMPORDER 138 
#define  LTG_DEFENDKEYAREA 137 
#define  LTG_GETFLAG 136 
#define  LTG_GETITEM 135 
#define  LTG_HARVEST 134 
#define  LTG_KILL 133 
#define  LTG_PATROL 132 
#define  LTG_RETURNFLAG 131 
#define  LTG_RUSHBASE 130 
#define  LTG_TEAMACCOMPANY 129 
#define  LTG_TEAMHELP 128 
 int TEAMTASK_CAMP ; 
 int TEAMTASK_DEFENSE ; 
 int TEAMTASK_ESCORT ; 
 int TEAMTASK_FOLLOW ; 
 int TEAMTASK_OFFENSE ; 
 int TEAMTASK_PATROL ; 
 int TEAMTASK_RETRIEVE ; 
 int /*<<< orphan*/  gametype ; 
 int /*<<< orphan*/  va (char*,int) ; 

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
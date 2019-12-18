#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_64__   TYPE_2__ ;
typedef  struct TYPE_63__   TYPE_1__ ;

/* Type definitions */
struct TYPE_63__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_64__ {int type; } ;
typedef  TYPE_2__ bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BotMatch_AttackEnemyBase (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_CTF (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_Camp (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_CheckPoint (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_DefendKeyArea (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_Dismiss (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_EnterGame (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_FormationSpace (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_GetFlag (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_GetItem (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_Harvest (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_HelpAccompany (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_JoinSubteam (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_Kill (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_LeadTheWay (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_LeaveSubteam (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_NewLeader (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_Patrol (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_ReturnFlag (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_RushBase (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_StartTeamLeaderShip (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_StopTeamLeaderShip (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_Suicide (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_TaskPreference (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_WhatAreYouDoing (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_WhatIsMyCommand (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_WhereAreYou (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_WhichTeam (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BotMatch_WhoIsTeamLeader (TYPE_1__*,TYPE_2__*) ; 
#define  MSG_ACCOMPANY 161 
#define  MSG_ATTACKENEMYBASE 160 
#define  MSG_CAMP 159 
#define  MSG_CHECKPOINT 158 
#define  MSG_CREATENEWFORMATION 157 
#define  MSG_CTF 156 
#define  MSG_DEFENDKEYAREA 155 
#define  MSG_DISMISS 154 
#define  MSG_DOFORMATION 153 
#define  MSG_ENTERGAME 152 
#define  MSG_FORMATIONPOSITION 151 
#define  MSG_FORMATIONSPACE 150 
#define  MSG_GETFLAG 149 
#define  MSG_GETITEM 148 
#define  MSG_HARVEST 147 
#define  MSG_HELP 146 
#define  MSG_JOINSUBTEAM 145 
#define  MSG_KILL 144 
#define  MSG_LEADTHEWAY 143 
#define  MSG_LEAVESUBTEAM 142 
#define  MSG_NEWLEADER 141 
#define  MSG_PATROL 140 
#define  MSG_RETURNFLAG 139 
#define  MSG_RUSHBASE 138 
#define  MSG_STARTTEAMLEADERSHIP 137 
#define  MSG_STOPTEAMLEADERSHIP 136 
#define  MSG_SUICIDE 135 
#define  MSG_TASKPREFERENCE 134 
#define  MSG_WAIT 133 
#define  MSG_WHATAREYOUDOING 132 
#define  MSG_WHATISMYCOMMAND 131 
#define  MSG_WHEREAREYOU 130 
#define  MSG_WHICHTEAM 129 
#define  MSG_WHOISTEAMLAEDER 128 
 int MTCONTEXT_CTF ; 
 int MTCONTEXT_INITIALTEAMCHAT ; 
 int MTCONTEXT_MISC ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_BotFindMatch (char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  trap_EA_SayTeam (int /*<<< orphan*/ ,char*) ; 

int BotMatchMessage(bot_state_t *bs, char *message) {
	bot_match_t match;

	match.type = 0;
	//if it is an unknown message
	if (!trap_BotFindMatch(message, &match, MTCONTEXT_MISC
											|MTCONTEXT_INITIALTEAMCHAT
											|MTCONTEXT_CTF)) {
		return qfalse;
	}
	//react to the found message
	switch(match.type)
	{
		case MSG_HELP:					//someone calling for help
		case MSG_ACCOMPANY:				//someone calling for company
		{
			BotMatch_HelpAccompany(bs, &match);
			break;
		}
		case MSG_DEFENDKEYAREA:			//teamplay defend a key area
		{
			BotMatch_DefendKeyArea(bs, &match);
			break;
		}
		case MSG_CAMP:					//camp somewhere
		{
			BotMatch_Camp(bs, &match);
			break;
		}
		case MSG_PATROL:				//patrol between several key areas
		{
			BotMatch_Patrol(bs, &match);
			break;
		}
		//CTF & 1FCTF
		case MSG_GETFLAG:				//ctf get the enemy flag
		{
			BotMatch_GetFlag(bs, &match);
			break;
		}
#ifdef MISSIONPACK
		//CTF & 1FCTF & Obelisk & Harvester
		case MSG_ATTACKENEMYBASE:
		{
			BotMatch_AttackEnemyBase(bs, &match);
			break;
		}
		//Harvester
		case MSG_HARVEST:
		{
			BotMatch_Harvest(bs, &match);
			break;
		}
#endif
		//CTF & 1FCTF & Harvester
		case MSG_RUSHBASE:				//ctf rush to the base
		{
			BotMatch_RushBase(bs, &match);
			break;
		}
		//CTF & 1FCTF
		case MSG_RETURNFLAG:
		{
			BotMatch_ReturnFlag(bs, &match);
			break;
		}
		//CTF & 1FCTF & Obelisk & Harvester
		case MSG_TASKPREFERENCE:
		{
			BotMatch_TaskPreference(bs, &match);
			break;
		}
		//CTF & 1FCTF
		case MSG_CTF:
		{
			BotMatch_CTF(bs, &match);
			break;
		}
		case MSG_GETITEM:
		{
			BotMatch_GetItem(bs, &match);
			break;
		}
		case MSG_JOINSUBTEAM:			//join a sub team
		{
			BotMatch_JoinSubteam(bs, &match);
			break;
		}
		case MSG_LEAVESUBTEAM:			//leave a sub team
		{
			BotMatch_LeaveSubteam(bs, &match);
			break;
		}
		case MSG_WHICHTEAM:
		{
			BotMatch_WhichTeam(bs, &match);
			break;
		}
		case MSG_CHECKPOINT:			//remember a check point
		{
			BotMatch_CheckPoint(bs, &match);
			break;
		}
		case MSG_CREATENEWFORMATION:	//start the creation of a new formation
		{
			trap_EA_SayTeam(bs->client, "the part of my brain to create formations has been damaged");
			break;
		}
		case MSG_FORMATIONPOSITION:		//tell someone his/her position in the formation
		{
			trap_EA_SayTeam(bs->client, "the part of my brain to create formations has been damaged");
			break;
		}
		case MSG_FORMATIONSPACE:		//set the formation space
		{
			BotMatch_FormationSpace(bs, &match);
			break;
		}
		case MSG_DOFORMATION:			//form a certain formation
		{
			break;
		}
		case MSG_DISMISS:				//dismiss someone
		{
			BotMatch_Dismiss(bs, &match);
			break;
		}
		case MSG_STARTTEAMLEADERSHIP:	//someone will become the team leader
		{
			BotMatch_StartTeamLeaderShip(bs, &match);
			break;
		}
		case MSG_STOPTEAMLEADERSHIP:	//someone will stop being the team leader
		{
			BotMatch_StopTeamLeaderShip(bs, &match);
			break;
		}
		case MSG_WHOISTEAMLAEDER:
		{
			BotMatch_WhoIsTeamLeader(bs, &match);
			break;
		}
		case MSG_WHATAREYOUDOING:		//ask a bot what he/she is doing
		{
			BotMatch_WhatAreYouDoing(bs, &match);
			break;
		}
		case MSG_WHATISMYCOMMAND:
		{
			BotMatch_WhatIsMyCommand(bs, &match);
			break;
		}
		case MSG_WHEREAREYOU:
		{
			BotMatch_WhereAreYou(bs, &match);
			break;
		}
		case MSG_LEADTHEWAY:
		{
			BotMatch_LeadTheWay(bs, &match);
			break;
		}
		case MSG_KILL:
		{
			BotMatch_Kill(bs, &match);
			break;
		}
		case MSG_ENTERGAME:				//someone entered the game
		{
			BotMatch_EnterGame(bs, &match);
			break;
		}
		case MSG_NEWLEADER:
		{
			BotMatch_NewLeader(bs, &match);
			break;
		}
		case MSG_WAIT:
		{
			break;
		}
		case MSG_SUICIDE:
		{
			BotMatch_Suicide(bs, &match);
			break;
		}
		default:
		{
			BotAI_Print(PRT_MESSAGE, "unknown match type\n");
			break;
		}
	}
	return qtrue;
}
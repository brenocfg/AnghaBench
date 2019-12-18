#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t number; scalar_t__ eType; scalar_t__ event; int otherEntityNum; int otherEntityNum2; int eventParm; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ entityState_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_13__ {scalar_t__* entityeventTime; int client; int botdeathtype; int lastkilledby; int enemydeathtype; int lastkilledplayer; int enemy; int neutralflagstatus; int blueflagstatus; int redflagstatus; int /*<<< orphan*/ * inventory; void* flagstatuschanged; void* enemysuicide; int /*<<< orphan*/  num_kills; void* killedenemy_time; int /*<<< orphan*/  num_deaths; void* botsuicide; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_14__ {int powerups; } ;
typedef  TYPE_3__ aas_entityinfo_t ;
struct TYPE_15__ {scalar_t__ eventTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BotDontAvoid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_3__*) ; 
 int /*<<< orphan*/  BotGoForPowerups (TYPE_2__*) ; 
 int /*<<< orphan*/  BotSameTeam (TYPE_2__*,int) ; 
 int /*<<< orphan*/  BotTeam (TYPE_2__*) ; 
 int CS_SOUNDS ; 
 int ENTITYNUM_NONE ; 
 int ENTITYNUM_WORLD ; 
 scalar_t__ ET_EVENTS ; 
#define  EV_CHANGE_WEAPON 178 
 scalar_t__ EV_EVENT_BITS ; 
#define  EV_FALL_FAR 177 
#define  EV_FALL_MEDIUM 176 
#define  EV_FALL_SHORT 175 
#define  EV_FIRE_WEAPON 174 
#define  EV_FOOTSPLASH 173 
#define  EV_FOOTSTEP 172 
#define  EV_FOOTSTEP_METAL 171 
#define  EV_FOOTWADE 170 
#define  EV_GENERAL_SOUND 169 
#define  EV_GLOBAL_ITEM_PICKUP 168 
#define  EV_GLOBAL_SOUND 167 
#define  EV_GLOBAL_TEAM_SOUND 166 
#define  EV_ITEM_PICKUP 165 
#define  EV_JUMP 164 
#define  EV_JUMP_PAD 163 
#define  EV_NOAMMO 162 
#define  EV_OBITUARY 161 
#define  EV_PLAYER_TELEPORT_IN 160 
#define  EV_STEP_12 159 
#define  EV_STEP_16 158 
#define  EV_STEP_4 157 
#define  EV_STEP_8 156 
#define  EV_SWIM 155 
#define  EV_TAUNT 154 
#define  EV_USE_ITEM0 153 
#define  EV_USE_ITEM1 152 
#define  EV_USE_ITEM10 151 
#define  EV_USE_ITEM11 150 
#define  EV_USE_ITEM12 149 
#define  EV_USE_ITEM13 148 
#define  EV_USE_ITEM14 147 
#define  EV_USE_ITEM15 146 
#define  EV_USE_ITEM2 145 
#define  EV_USE_ITEM3 144 
#define  EV_USE_ITEM4 143 
#define  EV_USE_ITEM5 142 
#define  EV_USE_ITEM6 141 
#define  EV_USE_ITEM7 140 
#define  EV_USE_ITEM8 139 
#define  EV_USE_ITEM9 138 
#define  EV_WATER_CLEAR 137 
#define  EV_WATER_LEAVE 136 
#define  EV_WATER_TOUCH 135 
#define  EV_WATER_UNDER 134 
 void* FloatTime () ; 
#define  GTS_BLUE_CAPTURE 133 
#define  GTS_BLUE_RETURN 132 
#define  GTS_BLUE_TAKEN 131 
#define  GTS_RED_CAPTURE 130 
#define  GTS_RED_RETURN 129 
#define  GTS_RED_TAKEN 128 
 int /*<<< orphan*/  GT_1FCTF ; 
 int /*<<< orphan*/  GT_CTF ; 
 size_t INVENTORY_TELEPORTER ; 
 int MAX_SOUNDS ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int PW_NEUTRALFLAG ; 
 int /*<<< orphan*/  TEAM_BLUE ; 
 int /*<<< orphan*/  TEAM_RED ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* g_entities ; 
 int /*<<< orphan*/  gametype ; 
 int /*<<< orphan*/  lastteleport_origin ; 
 void* lastteleport_time ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  trap_EA_Use (size_t) ; 
 int /*<<< orphan*/  trap_GetConfigstring (int,char*,int) ; 

void BotCheckEvents(bot_state_t *bs, entityState_t *state) {
	int event;
	char buf[128];
#ifdef MISSIONPACK
	aas_entityinfo_t entinfo;
#endif

	//NOTE: this sucks, we're accessing the gentity_t directly
	//but there's no other fast way to do it right now
	if (bs->entityeventTime[state->number] == g_entities[state->number].eventTime) {
		return;
	}
	bs->entityeventTime[state->number] = g_entities[state->number].eventTime;
	//if it's an event only entity
	if (state->eType > ET_EVENTS) {
		event = (state->eType - ET_EVENTS) & ~EV_EVENT_BITS;
	}
	else {
		event = state->event & ~EV_EVENT_BITS;
	}
	//
	switch(event) {
		//client obituary event
		case EV_OBITUARY:
		{
			int target, attacker, mod;

			target = state->otherEntityNum;
			attacker = state->otherEntityNum2;
			mod = state->eventParm;
			//
			if (target == bs->client) {
				bs->botdeathtype = mod;
				bs->lastkilledby = attacker;
				//
				if (target == attacker ||
					target == ENTITYNUM_NONE ||
					target == ENTITYNUM_WORLD) bs->botsuicide = qtrue;
				else bs->botsuicide = qfalse;
				//
				bs->num_deaths++;
			}
			//else if this client was killed by the bot
			else if (attacker == bs->client) {
				bs->enemydeathtype = mod;
				bs->lastkilledplayer = target;
				bs->killedenemy_time = FloatTime();
				//
				bs->num_kills++;
			}
			else if (attacker == bs->enemy && target == attacker) {
				bs->enemysuicide = qtrue;
			}
			//
#ifdef MISSIONPACK			
			if (gametype == GT_1FCTF) {
				//
				BotEntityInfo(target, &entinfo);
				if ( entinfo.powerups & ( 1 << PW_NEUTRALFLAG ) ) {
					if (!BotSameTeam(bs, target)) {
						bs->neutralflagstatus = 3;	//enemy dropped the flag
						bs->flagstatuschanged = qtrue;
					}
				}
			}
#endif
			break;
		}
		case EV_GLOBAL_SOUND:
		{
			if (state->eventParm < 0 || state->eventParm >= MAX_SOUNDS) {
				BotAI_Print(PRT_ERROR, "EV_GLOBAL_SOUND: eventParm (%d) out of range\n", state->eventParm);
				break;
			}
			trap_GetConfigstring(CS_SOUNDS + state->eventParm, buf, sizeof(buf));
			/*
			if (!strcmp(buf, "sound/teamplay/flagret_red.wav")) {
				//red flag is returned
				bs->redflagstatus = 0;
				bs->flagstatuschanged = qtrue;
			}
			else if (!strcmp(buf, "sound/teamplay/flagret_blu.wav")) {
				//blue flag is returned
				bs->blueflagstatus = 0;
				bs->flagstatuschanged = qtrue;
			}
			else*/
#ifdef MISSIONPACK
			if (!strcmp(buf, "sound/items/kamikazerespawn.wav" )) {
				//the kamikaze respawned so don't avoid it
				BotDontAvoid(bs, "Kamikaze");
			}
			else
#endif
				if (!strcmp(buf, "sound/items/poweruprespawn.wav")) {
				//powerup respawned... go get it
				BotGoForPowerups(bs);
			}
			break;
		}
		case EV_GLOBAL_TEAM_SOUND:
		{
			if (gametype == GT_CTF) {
				switch(state->eventParm) {
					case GTS_RED_CAPTURE:
						bs->blueflagstatus = 0;
						bs->redflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
					case GTS_BLUE_CAPTURE:
						bs->blueflagstatus = 0;
						bs->redflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
					case GTS_RED_RETURN:
						//blue flag is returned
						bs->blueflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_RETURN:
						//red flag is returned
						bs->redflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_RED_TAKEN:
						//blue flag is taken
						bs->blueflagstatus = 1;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
					case GTS_BLUE_TAKEN:
						//red flag is taken
						bs->redflagstatus = 1;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
				}
			}
#ifdef MISSIONPACK
			else if (gametype == GT_1FCTF) {
				switch(state->eventParm) {
					case GTS_RED_CAPTURE:
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_CAPTURE:
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_RED_RETURN:
						//flag has returned
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_RETURN:
						//flag has returned
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_RED_TAKEN:
						bs->neutralflagstatus = BotTeam(bs) == TEAM_RED ? 2 : 1; //FIXME: check Team_TakeFlagSound in g_team.c
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_TAKEN:
						bs->neutralflagstatus = BotTeam(bs) == TEAM_BLUE ? 2 : 1; //FIXME: check Team_TakeFlagSound in g_team.c
						bs->flagstatuschanged = qtrue;
						break;
				}
			}
#endif
			break;
		}
		case EV_PLAYER_TELEPORT_IN:
		{
			VectorCopy(state->origin, lastteleport_origin);
			lastteleport_time = FloatTime();
			break;
		}
		case EV_GENERAL_SOUND:
		{
			//if this sound is played on the bot
			if (state->number == bs->client) {
				if (state->eventParm < 0 || state->eventParm >= MAX_SOUNDS) {
					BotAI_Print(PRT_ERROR, "EV_GENERAL_SOUND: eventParm (%d) out of range\n", state->eventParm);
					break;
				}
				//check out the sound
				trap_GetConfigstring(CS_SOUNDS + state->eventParm, buf, sizeof(buf));
				//if falling into a death pit
				if (!strcmp(buf, "*falling1.wav")) {
					//if the bot has a personal teleporter
					if (bs->inventory[INVENTORY_TELEPORTER] > 0) {
						//use the holdable item
						trap_EA_Use(bs->client);
					}
				}
			}
			break;
		}
		case EV_FOOTSTEP:
		case EV_FOOTSTEP_METAL:
		case EV_FOOTSPLASH:
		case EV_FOOTWADE:
		case EV_SWIM:
		case EV_FALL_SHORT:
		case EV_FALL_MEDIUM:
		case EV_FALL_FAR:
		case EV_STEP_4:
		case EV_STEP_8:
		case EV_STEP_12:
		case EV_STEP_16:
		case EV_JUMP_PAD:
		case EV_JUMP:
		case EV_TAUNT:
		case EV_WATER_TOUCH:
		case EV_WATER_LEAVE:
		case EV_WATER_UNDER:
		case EV_WATER_CLEAR:
		case EV_ITEM_PICKUP:
		case EV_GLOBAL_ITEM_PICKUP:
		case EV_NOAMMO:
		case EV_CHANGE_WEAPON:
		case EV_FIRE_WEAPON:
			//FIXME: either add to sound queue or mark player as someone making noise
			break;
		case EV_USE_ITEM0:
		case EV_USE_ITEM1:
		case EV_USE_ITEM2:
		case EV_USE_ITEM3:
		case EV_USE_ITEM4:
		case EV_USE_ITEM5:
		case EV_USE_ITEM6:
		case EV_USE_ITEM7:
		case EV_USE_ITEM8:
		case EV_USE_ITEM9:
		case EV_USE_ITEM10:
		case EV_USE_ITEM11:
		case EV_USE_ITEM12:
		case EV_USE_ITEM13:
		case EV_USE_ITEM14:
		case EV_USE_ITEM15:
			break;
	}
}
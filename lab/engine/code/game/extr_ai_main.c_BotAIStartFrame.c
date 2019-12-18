#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_29__ {scalar_t__ eType; scalar_t__ weapon; int /*<<< orphan*/  torsoAnim; int /*<<< orphan*/  legsAnim; int /*<<< orphan*/  powerups; int /*<<< orphan*/  eventParm; int /*<<< orphan*/  event; int /*<<< orphan*/  frame; int /*<<< orphan*/  modelindex2; int /*<<< orphan*/  modelindex; int /*<<< orphan*/  groundEntityNum; int /*<<< orphan*/  eFlags; int /*<<< orphan*/  origin2; TYPE_1__ apos; } ;
struct TYPE_30__ {int svFlags; scalar_t__ contents; scalar_t__ bmodel; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  currentAngles; int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  linked; } ;
struct TYPE_31__ {scalar_t__ touch; TYPE_3__* client; TYPE_4__ s; TYPE_5__ r; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_32__ {scalar_t__ type; scalar_t__ weapon; int /*<<< orphan*/  torsoAnim; int /*<<< orphan*/  legsAnim; int /*<<< orphan*/  powerups; int /*<<< orphan*/  eventParm; int /*<<< orphan*/  event; int /*<<< orphan*/  frame; int /*<<< orphan*/  modelindex2; int /*<<< orphan*/  modelindex; int /*<<< orphan*/  groundent; int /*<<< orphan*/  solid; int /*<<< orphan*/  flags; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  old_origin; int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; } ;
typedef  TYPE_7__ bot_entitystate_t ;
struct TYPE_34__ {int serverTime; scalar_t__ buttons; scalar_t__ upmove; scalar_t__ rightmove; scalar_t__ forwardmove; } ;
struct TYPE_33__ {int integer; } ;
struct TYPE_27__ {scalar_t__ connected; } ;
struct TYPE_28__ {TYPE_2__ pers; } ;
struct TYPE_25__ {int botthink_residual; TYPE_9__ lastucmd; int /*<<< orphan*/  client; int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI (int,float) ; 
 int /*<<< orphan*/  BotAIRegularUpdate () ; 
 int /*<<< orphan*/  BotInterbreeding () ; 
 int /*<<< orphan*/  BotScheduleBotThink () ; 
 int /*<<< orphan*/  BotUpdateInfoConfigStrings () ; 
 int /*<<< orphan*/  BotUpdateInput (TYPE_13__*,int,int) ; 
 scalar_t__ CONTENTS_TRIGGER ; 
 scalar_t__ CON_CONNECTED ; 
 scalar_t__ ET_EVENTS ; 
 scalar_t__ ET_MISSILE ; 
 int /*<<< orphan*/  G_CheckBotSpawn () ; 
 int MAX_CLIENTS ; 
 int MAX_GENTITIES ; 
 scalar_t__ ProximityMine_Trigger ; 
 int /*<<< orphan*/  SOLID_BBOX ; 
 int /*<<< orphan*/  SOLID_BSP ; 
 int SVF_NOCLIENT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WP_GRAPPLING_HOOK ; 
 TYPE_8__ bot_fastchat ; 
 TYPE_8__ bot_grapple ; 
 TYPE_8__ bot_memorydump ; 
 TYPE_8__ bot_nochat ; 
 TYPE_8__ bot_pause ; 
 TYPE_8__ bot_report ; 
 TYPE_8__ bot_rocketjump ; 
 TYPE_8__ bot_saveroutingcache ; 
 TYPE_8__ bot_testrchat ; 
 TYPE_8__ bot_thinktime ; 
 TYPE_13__** botstates ; 
 int /*<<< orphan*/  floattime ; 
 TYPE_6__* g_entities ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_AAS_Initialized () ; 
 int /*<<< orphan*/  trap_AAS_Time () ; 
 int /*<<< orphan*/  trap_BotLibStartFrame (float) ; 
 int /*<<< orphan*/  trap_BotLibUpdateEntity (int,TYPE_7__*) ; 
 int /*<<< orphan*/  trap_BotLibVarSet (char*,char*) ; 
 int /*<<< orphan*/  trap_BotUserCommand (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Update (TYPE_8__*) ; 

int BotAIStartFrame(int time) {
	int i;
	gentity_t	*ent;
	bot_entitystate_t state;
	int elapsed_time, thinktime;
	static int local_time;
	static int botlib_residual;
	static int lastbotthink_time;

	G_CheckBotSpawn();

	trap_Cvar_Update(&bot_rocketjump);
	trap_Cvar_Update(&bot_grapple);
	trap_Cvar_Update(&bot_fastchat);
	trap_Cvar_Update(&bot_nochat);
	trap_Cvar_Update(&bot_testrchat);
	trap_Cvar_Update(&bot_thinktime);
	trap_Cvar_Update(&bot_memorydump);
	trap_Cvar_Update(&bot_saveroutingcache);
	trap_Cvar_Update(&bot_pause);
	trap_Cvar_Update(&bot_report);

	if (bot_report.integer) {
//		BotTeamplayReport();
//		trap_Cvar_Set("bot_report", "0");
		BotUpdateInfoConfigStrings();
	}

	if (bot_pause.integer) {
		// execute bot user commands every frame
		for( i = 0; i < MAX_CLIENTS; i++ ) {
			if( !botstates[i] || !botstates[i]->inuse ) {
				continue;
			}
			if( g_entities[i].client->pers.connected != CON_CONNECTED ) {
				continue;
			}
			botstates[i]->lastucmd.forwardmove = 0;
			botstates[i]->lastucmd.rightmove = 0;
			botstates[i]->lastucmd.upmove = 0;
			botstates[i]->lastucmd.buttons = 0;
			botstates[i]->lastucmd.serverTime = time;
			trap_BotUserCommand(botstates[i]->client, &botstates[i]->lastucmd);
		}
		return qtrue;
	}

	if (bot_memorydump.integer) {
		trap_BotLibVarSet("memorydump", "1");
		trap_Cvar_Set("bot_memorydump", "0");
	}
	if (bot_saveroutingcache.integer) {
		trap_BotLibVarSet("saveroutingcache", "1");
		trap_Cvar_Set("bot_saveroutingcache", "0");
	}
	//check if bot interbreeding is activated
	BotInterbreeding();
	//cap the bot think time
	if (bot_thinktime.integer > 200) {
		trap_Cvar_Set("bot_thinktime", "200");
	}
	//if the bot think time changed we should reschedule the bots
	if (bot_thinktime.integer != lastbotthink_time) {
		lastbotthink_time = bot_thinktime.integer;
		BotScheduleBotThink();
	}

	elapsed_time = time - local_time;
	local_time = time;

	botlib_residual += elapsed_time;

	if (elapsed_time > bot_thinktime.integer) thinktime = elapsed_time;
	else thinktime = bot_thinktime.integer;

	// update the bot library
	if ( botlib_residual >= thinktime ) {
		botlib_residual -= thinktime;

		trap_BotLibStartFrame((float) time / 1000);

		if (!trap_AAS_Initialized()) return qfalse;

		//update entities in the botlib
		for (i = 0; i < MAX_GENTITIES; i++) {
			ent = &g_entities[i];
			if (!ent->inuse) {
				trap_BotLibUpdateEntity(i, NULL);
				continue;
			}
			if (!ent->r.linked) {
				trap_BotLibUpdateEntity(i, NULL);
				continue;
			}
			if (ent->r.svFlags & SVF_NOCLIENT) {
				trap_BotLibUpdateEntity(i, NULL);
				continue;
			}
			// do not update missiles
			if (ent->s.eType == ET_MISSILE && ent->s.weapon != WP_GRAPPLING_HOOK) {
				trap_BotLibUpdateEntity(i, NULL);
				continue;
			}
			// do not update event only entities
			if (ent->s.eType > ET_EVENTS) {
				trap_BotLibUpdateEntity(i, NULL);
				continue;
			}
#ifdef MISSIONPACK
			// never link prox mine triggers
			if (ent->r.contents == CONTENTS_TRIGGER) {
				if (ent->touch == ProximityMine_Trigger) {
					trap_BotLibUpdateEntity(i, NULL);
					continue;
				}
			}
#endif
			//
			memset(&state, 0, sizeof(bot_entitystate_t));
			//
			VectorCopy(ent->r.currentOrigin, state.origin);
			if (i < MAX_CLIENTS) {
				VectorCopy(ent->s.apos.trBase, state.angles);
			} else {
				VectorCopy(ent->r.currentAngles, state.angles);
			}
			VectorCopy(ent->s.origin2, state.old_origin);
			VectorCopy(ent->r.mins, state.mins);
			VectorCopy(ent->r.maxs, state.maxs);
			state.type = ent->s.eType;
			state.flags = ent->s.eFlags;
			if (ent->r.bmodel) state.solid = SOLID_BSP;
			else state.solid = SOLID_BBOX;
			state.groundent = ent->s.groundEntityNum;
			state.modelindex = ent->s.modelindex;
			state.modelindex2 = ent->s.modelindex2;
			state.frame = ent->s.frame;
			state.event = ent->s.event;
			state.eventParm = ent->s.eventParm;
			state.powerups = ent->s.powerups;
			state.legsAnim = ent->s.legsAnim;
			state.torsoAnim = ent->s.torsoAnim;
			state.weapon = ent->s.weapon;
			//
			trap_BotLibUpdateEntity(i, &state);
		}

		BotAIRegularUpdate();
	}

	floattime = trap_AAS_Time();

	// execute scheduled bot AI
	for( i = 0; i < MAX_CLIENTS; i++ ) {
		if( !botstates[i] || !botstates[i]->inuse ) {
			continue;
		}
		//
		botstates[i]->botthink_residual += elapsed_time;
		//
		if ( botstates[i]->botthink_residual >= thinktime ) {
			botstates[i]->botthink_residual -= thinktime;

			if (!trap_AAS_Initialized()) return qfalse;

			if (g_entities[i].client->pers.connected == CON_CONNECTED) {
				BotAI(i, (float) thinktime / 1000);
			}
		}
	}


	// execute bot user commands every frame
	for( i = 0; i < MAX_CLIENTS; i++ ) {
		if( !botstates[i] || !botstates[i]->inuse ) {
			continue;
		}
		if( g_entities[i].client->pers.connected != CON_CONNECTED ) {
			continue;
		}

		BotUpdateInput(botstates[i], time, elapsed_time);
		trap_BotUserCommand(botstates[i]->client, &botstates[i]->lastucmd);
	}

	return qtrue;
}
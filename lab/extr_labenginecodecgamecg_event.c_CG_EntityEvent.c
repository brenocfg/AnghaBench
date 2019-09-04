#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_19__ ;
typedef  struct TYPE_47__   TYPE_18__ ;
typedef  struct TYPE_46__   TYPE_17__ ;
typedef  struct TYPE_45__   TYPE_16__ ;
typedef  struct TYPE_44__   TYPE_15__ ;
typedef  struct TYPE_43__   TYPE_14__ ;
typedef  struct TYPE_42__   TYPE_13__ ;
typedef  struct TYPE_41__   TYPE_12__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
struct TYPE_56__ {int member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_8__ vec3_t ;
struct TYPE_57__ {int /*<<< orphan*/  pickup_sound; int /*<<< orphan*/  giType; } ;
typedef  TYPE_9__ gitem_t ;
struct TYPE_52__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_39__ {int event; int number; int clientNum; int eventParm; int eFlags; int /*<<< orphan*/  loopSound; int /*<<< orphan*/  otherEntityNum; TYPE_4__ pos; int /*<<< orphan*/  weapon; int /*<<< orphan*/  origin2; int /*<<< orphan*/  time; } ;
typedef  TYPE_10__ entityState_t ;
struct TYPE_40__ {size_t footsteps; } ;
typedef  TYPE_11__ clientInfo_t ;
struct TYPE_49__ {int painTime; } ;
struct TYPE_41__ {int miscTime; int /*<<< orphan*/ * lerpOrigin; TYPE_10__ currentState; TYPE_1__ pe; } ;
typedef  TYPE_12__ centity_t ;
struct TYPE_55__ {int /*<<< orphan*/  gibSound; int /*<<< orphan*/  regenSound; int /*<<< orphan*/  protectSound; int /*<<< orphan*/  quadSound; int /*<<< orphan*/  teamsTiedSound; int /*<<< orphan*/  blueLeadsSound; int /*<<< orphan*/  redLeadsSound; int /*<<< orphan*/  blueScoredSound; int /*<<< orphan*/  redScoredSound; int /*<<< orphan*/  yourTeamTookEnemyFlagSound; int /*<<< orphan*/  enemyTookYourFlagSound; int /*<<< orphan*/  redFlagReturnedSound; int /*<<< orphan*/  returnOpponentSound; int /*<<< orphan*/  returnYourTeamSound; int /*<<< orphan*/  blueFlagReturnedSound; int /*<<< orphan*/  captureOpponentSound; int /*<<< orphan*/  captureYourTeamSound; int /*<<< orphan*/  hgrenb2aSound; int /*<<< orphan*/  hgrenb1aSound; int /*<<< orphan*/  respawnSound; int /*<<< orphan*/  teleOutSound; int /*<<< orphan*/  teleInSound; int /*<<< orphan*/  selectSound; int /*<<< orphan*/  n_healthSound; int /*<<< orphan*/  watrUnSound; int /*<<< orphan*/  watrOutSound; int /*<<< orphan*/  watrInSound; int /*<<< orphan*/  jumpPadSound; int /*<<< orphan*/  smokePuffShader; int /*<<< orphan*/  landSound; int /*<<< orphan*/ ** footsteps; } ;
struct TYPE_53__ {int pm_flags; int clientNum; int /*<<< orphan*/ * persistant; int /*<<< orphan*/ * powerups; } ;
struct TYPE_54__ {TYPE_5__ ps; } ;
struct TYPE_51__ {int /*<<< orphan*/ * viewaxis; } ;
struct TYPE_50__ {int clientNum; } ;
struct TYPE_48__ {int landChange; int landTime; int time; int stepTime; int stepChange; int powerupTime; int /*<<< orphan*/  powerupActive; TYPE_6__* snap; TYPE_3__ refdef; int /*<<< orphan*/  renderingThirdPerson; int /*<<< orphan*/  demoPlayback; TYPE_2__ predictedPlayerState; } ;
struct TYPE_47__ {scalar_t__ integer; } ;
struct TYPE_46__ {int integer; } ;
struct TYPE_45__ {int /*<<< orphan*/  integer; } ;
struct TYPE_44__ {int /*<<< orphan*/  integer; } ;
struct TYPE_43__ {int /*<<< orphan*/  integer; } ;
struct TYPE_42__ {TYPE_7__ media; int /*<<< orphan*/ * gameSounds; TYPE_11__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ByteToDir (int,TYPE_8__) ; 
 int /*<<< orphan*/  CG_AddBufferedSound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Beam (TYPE_12__*) ; 
 int /*<<< orphan*/  CG_Bullet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__,int /*<<< orphan*/ ,int) ; 
 char* CG_ConfigString (size_t) ; 
 int /*<<< orphan*/  CG_CustomSound (int,char const*) ; 
 int /*<<< orphan*/  CG_Error (char*,int) ; 
 int /*<<< orphan*/  CG_FireWeapon (TYPE_12__*) ; 
 int /*<<< orphan*/  CG_GibPlayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CG_ItemPickup (int) ; 
 int /*<<< orphan*/  CG_MissileHitPlayer (int /*<<< orphan*/ ,TYPE_8__,TYPE_8__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_MissileHitWall (int /*<<< orphan*/ ,int,TYPE_8__,TYPE_8__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Obituary (TYPE_10__*) ; 
 int /*<<< orphan*/  CG_OutOfAmmoChange () ; 
 int /*<<< orphan*/  CG_PainEvent (TYPE_12__*,size_t) ; 
 int /*<<< orphan*/  CG_Printf (char*,int,int) ; 
 int /*<<< orphan*/  CG_RailTrail (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_ScorePlum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_ShotgunFire (TYPE_10__*) ; 
 int /*<<< orphan*/  CG_SmokePuff (int /*<<< orphan*/ *,TYPE_8__,int,int,int,int,float,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_SpawnEffect (TYPE_8__) ; 
 int /*<<< orphan*/  CG_UseItem (TYPE_12__*) ; 
 int CG_WaterLevel (TYPE_12__*) ; 
 int /*<<< orphan*/  CHAN_AUTO ; 
 int /*<<< orphan*/  CHAN_BODY ; 
 int /*<<< orphan*/  CHAN_ITEM ; 
 int /*<<< orphan*/  CHAN_VOICE ; 
 size_t CS_SOUNDS ; 
 int /*<<< orphan*/  DEBUGNAME (char*) ; 
 int EF_KAMIKAZE ; 
 int ENTITYNUM_WORLD ; 
#define  EV_BULLET_HIT_FLESH 205 
#define  EV_BULLET_HIT_WALL 204 
#define  EV_CHANGE_WEAPON 203 
#define  EV_DEATH1 202 
#define  EV_DEATH2 201 
#define  EV_DEATH3 200 
#define  EV_DEBUG_LINE 199 
 int EV_EVENT_BITS ; 
#define  EV_FALL_FAR 198 
#define  EV_FALL_MEDIUM 197 
#define  EV_FALL_SHORT 196 
#define  EV_FIRE_WEAPON 195 
#define  EV_FOOTSPLASH 194 
#define  EV_FOOTSTEP 193 
#define  EV_FOOTSTEP_METAL 192 
#define  EV_FOOTWADE 191 
#define  EV_GENERAL_SOUND 190 
#define  EV_GIB_PLAYER 189 
#define  EV_GLOBAL_ITEM_PICKUP 188 
#define  EV_GLOBAL_SOUND 187 
#define  EV_GLOBAL_TEAM_SOUND 186 
#define  EV_GRENADE_BOUNCE 185 
#define  EV_ITEM_PICKUP 184 
#define  EV_ITEM_POP 183 
#define  EV_ITEM_RESPAWN 182 
#define  EV_JUMP 181 
#define  EV_JUMP_PAD 180 
#define  EV_MISSILE_HIT 179 
#define  EV_MISSILE_MISS 178 
#define  EV_MISSILE_MISS_METAL 177 
#define  EV_NOAMMO 176 
#define  EV_OBITUARY 175 
#define  EV_PAIN 174 
#define  EV_PLAYER_TELEPORT_IN 173 
#define  EV_PLAYER_TELEPORT_OUT 172 
#define  EV_POWERUP_BATTLESUIT 171 
#define  EV_POWERUP_QUAD 170 
#define  EV_POWERUP_REGEN 169 
#define  EV_RAILTRAIL 168 
#define  EV_SCOREPLUM 167 
#define  EV_SHOTGUN 166 
#define  EV_STEP_12 165 
#define  EV_STEP_16 164 
#define  EV_STEP_4 163 
#define  EV_STEP_8 162 
#define  EV_STOPLOOPINGSOUND 161 
#define  EV_SWIM 160 
#define  EV_TAUNT 159 
#define  EV_USE_ITEM0 158 
#define  EV_USE_ITEM1 157 
#define  EV_USE_ITEM10 156 
#define  EV_USE_ITEM11 155 
#define  EV_USE_ITEM12 154 
#define  EV_USE_ITEM13 153 
#define  EV_USE_ITEM14 152 
#define  EV_USE_ITEM15 151 
#define  EV_USE_ITEM2 150 
#define  EV_USE_ITEM3 149 
#define  EV_USE_ITEM4 148 
#define  EV_USE_ITEM5 147 
#define  EV_USE_ITEM6 146 
#define  EV_USE_ITEM7 145 
#define  EV_USE_ITEM8 144 
#define  EV_USE_ITEM9 143 
#define  EV_WATER_CLEAR 142 
#define  EV_WATER_LEAVE 141 
#define  EV_WATER_TOUCH 140 
#define  EV_WATER_UNDER 139 
 size_t FOOTSTEP_METAL ; 
 size_t FOOTSTEP_SPLASH ; 
#define  GTS_BLUETEAM_SCORED 138 
#define  GTS_BLUETEAM_TOOK_LEAD 137 
#define  GTS_BLUE_CAPTURE 136 
#define  GTS_BLUE_RETURN 135 
#define  GTS_BLUE_TAKEN 134 
#define  GTS_REDTEAM_SCORED 133 
#define  GTS_REDTEAM_TOOK_LEAD 132 
#define  GTS_RED_CAPTURE 131 
#define  GTS_RED_RETURN 130 
#define  GTS_RED_TAKEN 129 
#define  GTS_TEAMS_ARE_TIED 128 
 int /*<<< orphan*/  IMPACTSOUND_DEFAULT ; 
 int /*<<< orphan*/  IMPACTSOUND_METAL ; 
 int /*<<< orphan*/  IT_PERSISTANT_POWERUP ; 
 int /*<<< orphan*/  IT_POWERUP ; 
 int /*<<< orphan*/  IT_TEAM ; 
 int /*<<< orphan*/  LEF_PUFF_DONT_SCALE ; 
 int MAX_CLIENTS ; 
 float MAX_STEP_CHANGE ; 
 size_t PERS_TEAM ; 
 int PMF_FOLLOW ; 
 int /*<<< orphan*/  PW_BATTLESUIT ; 
 size_t PW_BLUEFLAG ; 
 size_t PW_NEUTRALFLAG ; 
 int /*<<< orphan*/  PW_QUAD ; 
 size_t PW_REDFLAG ; 
 int /*<<< orphan*/  PW_REGEN ; 
 int STEP_TIME ; 
 int /*<<< orphan*/  TEAM_BLUE ; 
 int /*<<< orphan*/  TEAM_RED ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WP_RAILGUN ; 
 TYPE_9__* bg_itemlist ; 
 int bg_numItems ; 
 TYPE_19__ cg ; 
 TYPE_18__ cg_debugEvents ; 
 TYPE_17__ cg_drawGun ; 
 TYPE_16__ cg_footsteps ; 
 TYPE_15__ cg_nopredict ; 
 TYPE_14__ cg_synchronousClients ; 
 TYPE_13__ cgs ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int rand () ; 
 int /*<<< orphan*/  trap_S_RegisterSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_S_StartSound (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_S_StopLoopingSound (int) ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void CG_EntityEvent( centity_t *cent, vec3_t position ) {
	entityState_t	*es;
	int				event;
	vec3_t			dir;
	const char		*s;
	int				clientNum;
	clientInfo_t	*ci;

	es = &cent->currentState;
	event = es->event & ~EV_EVENT_BITS;

	if ( cg_debugEvents.integer ) {
		CG_Printf( "ent:%3i  event:%3i ", es->number, event );
	}

	if ( !event ) {
		DEBUGNAME("ZEROEVENT");
		return;
	}

	clientNum = es->clientNum;
	if ( clientNum < 0 || clientNum >= MAX_CLIENTS ) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[ clientNum ];

	switch ( event ) {
	//
	// movement generated events
	//
	case EV_FOOTSTEP:
		DEBUGNAME("EV_FOOTSTEP");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ ci->footsteps ][rand()&3] );
		}
		break;
	case EV_FOOTSTEP_METAL:
		DEBUGNAME("EV_FOOTSTEP_METAL");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_METAL ][rand()&3] );
		}
		break;
	case EV_FOOTSPLASH:
		DEBUGNAME("EV_FOOTSPLASH");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;
	case EV_FOOTWADE:
		DEBUGNAME("EV_FOOTWADE");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;
	case EV_SWIM:
		DEBUGNAME("EV_SWIM");
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;


	case EV_FALL_SHORT:
		DEBUGNAME("EV_FALL_SHORT");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.landSound );
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -8;
			cg.landTime = cg.time;
		}
		break;
	case EV_FALL_MEDIUM:
		DEBUGNAME("EV_FALL_MEDIUM");
		// use normal pain sound
		trap_S_StartSound( NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*pain100_1.wav" ) );
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -16;
			cg.landTime = cg.time;
		}
		break;
	case EV_FALL_FAR:
		DEBUGNAME("EV_FALL_FAR");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, CG_CustomSound( es->number, "*fall1.wav" ) );
		cent->pe.painTime = cg.time;	// don't play a pain sound right after this
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -24;
			cg.landTime = cg.time;
		}
		break;

	case EV_STEP_4:
	case EV_STEP_8:
	case EV_STEP_12:
	case EV_STEP_16:		// smooth out step up transitions
		DEBUGNAME("EV_STEP");
	{
		float	oldStep;
		int		delta;
		int		step;

		if ( clientNum != cg.predictedPlayerState.clientNum ) {
			break;
		}
		// if we are interpolating, we don't need to smooth steps
		if ( cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW) ||
			cg_nopredict.integer || cg_synchronousClients.integer ) {
			break;
		}
		// check for stepping up before a previous step is completed
		delta = cg.time - cg.stepTime;
		if (delta < STEP_TIME) {
			oldStep = cg.stepChange * (STEP_TIME - delta) / STEP_TIME;
		} else {
			oldStep = 0;
		}

		// add this amount
		step = 4 * (event - EV_STEP_4 + 1 );
		cg.stepChange = oldStep + step;
		if ( cg.stepChange > MAX_STEP_CHANGE ) {
			cg.stepChange = MAX_STEP_CHANGE;
		}
		cg.stepTime = cg.time;
		break;
	}

	case EV_JUMP_PAD:
		DEBUGNAME("EV_JUMP_PAD");
//		CG_Printf( "EV_JUMP_PAD w/effect #%i\n", es->eventParm );
		{
			vec3_t			up = {0, 0, 1};


			CG_SmokePuff( cent->lerpOrigin, up, 
						  32, 
						  1, 1, 1, 0.33f,
						  1000, 
						  cg.time, 0,
						  LEF_PUFF_DONT_SCALE, 
						  cgs.media.smokePuffShader );
		}

		// boing sound at origin, jump sound on player
		trap_S_StartSound ( cent->lerpOrigin, -1, CHAN_VOICE, cgs.media.jumpPadSound );
		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
		break;

	case EV_JUMP:
		DEBUGNAME("EV_JUMP");
		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
		break;
	case EV_TAUNT:
		DEBUGNAME("EV_TAUNT");
		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*taunt.wav" ) );
		break;
#ifdef MISSIONPACK
	case EV_TAUNT_YES:
		DEBUGNAME("EV_TAUNT_YES");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_YES);
		break;
	case EV_TAUNT_NO:
		DEBUGNAME("EV_TAUNT_NO");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_NO);
		break;
	case EV_TAUNT_FOLLOWME:
		DEBUGNAME("EV_TAUNT_FOLLOWME");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_FOLLOWME);
		break;
	case EV_TAUNT_GETFLAG:
		DEBUGNAME("EV_TAUNT_GETFLAG");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONGETFLAG);
		break;
	case EV_TAUNT_GUARDBASE:
		DEBUGNAME("EV_TAUNT_GUARDBASE");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONDEFENSE);
		break;
	case EV_TAUNT_PATROL:
		DEBUGNAME("EV_TAUNT_PATROL");
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONPATROL);
		break;
#endif
	case EV_WATER_TOUCH:
		DEBUGNAME("EV_WATER_TOUCH");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrInSound );
		break;
	case EV_WATER_LEAVE:
		DEBUGNAME("EV_WATER_LEAVE");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrOutSound );
		break;
	case EV_WATER_UNDER:
		DEBUGNAME("EV_WATER_UNDER");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrUnSound );
		break;
	case EV_WATER_CLEAR:
		DEBUGNAME("EV_WATER_CLEAR");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, CG_CustomSound( es->number, "*gasp.wav" ) );
		break;

	case EV_ITEM_PICKUP:
		DEBUGNAME("EV_ITEM_PICKUP");
		{
			gitem_t	*item;
			int		index;

			index = es->eventParm;		// player predicted

			if ( index < 1 || index >= bg_numItems ) {
				break;
			}
			item = &bg_itemlist[ index ];

			// powerups and team items will have a separate global sound, this one
			// will be played at prediction time
			if ( item->giType == IT_POWERUP || item->giType == IT_TEAM) {
				trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.n_healthSound );
			} else if (item->giType == IT_PERSISTANT_POWERUP) {
#ifdef MISSIONPACK
				switch (item->giTag ) {
					case PW_SCOUT:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.scoutSound );
					break;
					case PW_GUARD:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.guardSound );
					break;
					case PW_DOUBLER:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.doublerSound );
					break;
					case PW_AMMOREGEN:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.ammoregenSound );
					break;
				}
#endif
			} else {
				trap_S_StartSound (NULL, es->number, CHAN_AUTO,	trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			}

			// show icon and name on status bar
			if ( es->number == cg.snap->ps.clientNum ) {
				CG_ItemPickup( index );
			}
		}
		break;

	case EV_GLOBAL_ITEM_PICKUP:
		DEBUGNAME("EV_GLOBAL_ITEM_PICKUP");
		{
			gitem_t	*item;
			int		index;

			index = es->eventParm;		// player predicted

			if ( index < 1 || index >= bg_numItems ) {
				break;
			}
			item = &bg_itemlist[ index ];
			// powerup pickups are global
			if( item->pickup_sound ) {
				trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			}

			// show icon and name on status bar
			if ( es->number == cg.snap->ps.clientNum ) {
				CG_ItemPickup( index );
			}
		}
		break;

	//
	// weapon events
	//
	case EV_NOAMMO:
		DEBUGNAME("EV_NOAMMO");
//		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.noAmmoSound );
		if ( es->number == cg.snap->ps.clientNum ) {
			CG_OutOfAmmoChange();
		}
		break;
	case EV_CHANGE_WEAPON:
		DEBUGNAME("EV_CHANGE_WEAPON");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.selectSound );
		break;
	case EV_FIRE_WEAPON:
		DEBUGNAME("EV_FIRE_WEAPON");
		CG_FireWeapon( cent );
		break;

	case EV_USE_ITEM0:
		DEBUGNAME("EV_USE_ITEM0");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM1:
		DEBUGNAME("EV_USE_ITEM1");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM2:
		DEBUGNAME("EV_USE_ITEM2");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM3:
		DEBUGNAME("EV_USE_ITEM3");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM4:
		DEBUGNAME("EV_USE_ITEM4");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM5:
		DEBUGNAME("EV_USE_ITEM5");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM6:
		DEBUGNAME("EV_USE_ITEM6");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM7:
		DEBUGNAME("EV_USE_ITEM7");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM8:
		DEBUGNAME("EV_USE_ITEM8");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM9:
		DEBUGNAME("EV_USE_ITEM9");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM10:
		DEBUGNAME("EV_USE_ITEM10");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM11:
		DEBUGNAME("EV_USE_ITEM11");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM12:
		DEBUGNAME("EV_USE_ITEM12");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM13:
		DEBUGNAME("EV_USE_ITEM13");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM14:
		DEBUGNAME("EV_USE_ITEM14");
		CG_UseItem( cent );
		break;
	case EV_USE_ITEM15:
		DEBUGNAME("EV_USE_ITEM15");
		CG_UseItem( cent );
		break;

	//=================================================================

	//
	// other events
	//
	case EV_PLAYER_TELEPORT_IN:
		DEBUGNAME("EV_PLAYER_TELEPORT_IN");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.teleInSound );
		CG_SpawnEffect( position);
		break;

	case EV_PLAYER_TELEPORT_OUT:
		DEBUGNAME("EV_PLAYER_TELEPORT_OUT");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.teleOutSound );
		CG_SpawnEffect(  position);
		break;

	case EV_ITEM_POP:
		DEBUGNAME("EV_ITEM_POP");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.respawnSound );
		break;
	case EV_ITEM_RESPAWN:
		DEBUGNAME("EV_ITEM_RESPAWN");
		cent->miscTime = cg.time;	// scale up from this
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.respawnSound );
		break;

	case EV_GRENADE_BOUNCE:
		DEBUGNAME("EV_GRENADE_BOUNCE");
		if ( rand() & 1 ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.hgrenb1aSound );
		} else {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.hgrenb2aSound );
		}
		break;

#ifdef MISSIONPACK
	case EV_PROXIMITY_MINE_STICK:
		DEBUGNAME("EV_PROXIMITY_MINE_STICK");
		if( es->eventParm & SURF_FLESH ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimplSound );
		} else 	if( es->eventParm & SURF_METALSTEPS ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimpmSound );
		} else {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimpdSound );
		}
		break;

	case EV_PROXIMITY_MINE_TRIGGER:
		DEBUGNAME("EV_PROXIMITY_MINE_TRIGGER");
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbactvSound );
		break;
	case EV_KAMIKAZE:
		DEBUGNAME("EV_KAMIKAZE");
		CG_KamikazeEffect( cent->lerpOrigin );
		break;
	case EV_OBELISKEXPLODE:
		DEBUGNAME("EV_OBELISKEXPLODE");
		CG_ObeliskExplode( cent->lerpOrigin, es->eventParm );
		break;
	case EV_OBELISKPAIN:
		DEBUGNAME("EV_OBELISKPAIN");
		CG_ObeliskPain( cent->lerpOrigin );
		break;
	case EV_INVUL_IMPACT:
		DEBUGNAME("EV_INVUL_IMPACT");
		CG_InvulnerabilityImpact( cent->lerpOrigin, cent->currentState.angles );
		break;
	case EV_JUICED:
		DEBUGNAME("EV_JUICED");
		CG_InvulnerabilityJuiced( cent->lerpOrigin );
		break;
	case EV_LIGHTNINGBOLT:
		DEBUGNAME("EV_LIGHTNINGBOLT");
		CG_LightningBoltBeam(es->origin2, es->pos.trBase);
		break;
#endif
	case EV_SCOREPLUM:
		DEBUGNAME("EV_SCOREPLUM");
		CG_ScorePlum( cent->currentState.otherEntityNum, cent->lerpOrigin, cent->currentState.time );
		break;

	//
	// missile impacts
	//
	case EV_MISSILE_HIT:
		DEBUGNAME("EV_MISSILE_HIT");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitPlayer( es->weapon, position, dir, es->otherEntityNum );
		break;

	case EV_MISSILE_MISS:
		DEBUGNAME("EV_MISSILE_MISS");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, IMPACTSOUND_DEFAULT );
		break;

	case EV_MISSILE_MISS_METAL:
		DEBUGNAME("EV_MISSILE_MISS_METAL");
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, IMPACTSOUND_METAL );
		break;

	case EV_RAILTRAIL:
		DEBUGNAME("EV_RAILTRAIL");
		cent->currentState.weapon = WP_RAILGUN;
		
		if(es->clientNum == cg.snap->ps.clientNum && !cg.renderingThirdPerson)
		{
			if(cg_drawGun.integer == 2)
				VectorMA(es->origin2, 8, cg.refdef.viewaxis[1], es->origin2);
			else if(cg_drawGun.integer == 3)
				VectorMA(es->origin2, 4, cg.refdef.viewaxis[1], es->origin2);
		}

		CG_RailTrail(ci, es->origin2, es->pos.trBase);

		// if the end was on a nomark surface, don't make an explosion
		if ( es->eventParm != 255 ) {
			ByteToDir( es->eventParm, dir );
			CG_MissileHitWall( es->weapon, es->clientNum, position, dir, IMPACTSOUND_DEFAULT );
		}
		break;

	case EV_BULLET_HIT_WALL:
		DEBUGNAME("EV_BULLET_HIT_WALL");
		ByteToDir( es->eventParm, dir );
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qfalse, ENTITYNUM_WORLD );
		break;

	case EV_BULLET_HIT_FLESH:
		DEBUGNAME("EV_BULLET_HIT_FLESH");
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qtrue, es->eventParm );
		break;

	case EV_SHOTGUN:
		DEBUGNAME("EV_SHOTGUN");
		CG_ShotgunFire( es );
		break;

	case EV_GENERAL_SOUND:
		DEBUGNAME("EV_GENERAL_SOUND");
		if ( cgs.gameSounds[ es->eventParm ] ) {
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, cgs.gameSounds[ es->eventParm ] );
		} else {
			s = CG_ConfigString( CS_SOUNDS + es->eventParm );
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, s ) );
		}
		break;

	case EV_GLOBAL_SOUND:	// play from the player's head so it never diminishes
		DEBUGNAME("EV_GLOBAL_SOUND");
		if ( cgs.gameSounds[ es->eventParm ] ) {
			trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, cgs.gameSounds[ es->eventParm ] );
		} else {
			s = CG_ConfigString( CS_SOUNDS + es->eventParm );
			trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, CG_CustomSound( es->number, s ) );
		}
		break;

	case EV_GLOBAL_TEAM_SOUND:	// play from the player's head so it never diminishes
		{
			DEBUGNAME("EV_GLOBAL_TEAM_SOUND");
			switch( es->eventParm ) {
				case GTS_RED_CAPTURE: // CTF: red team captured the blue flag, 1FCTF: red team captured the neutral flag
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED )
						CG_AddBufferedSound( cgs.media.captureYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.captureOpponentSound );
					break;
				case GTS_BLUE_CAPTURE: // CTF: blue team captured the red flag, 1FCTF: blue team captured the neutral flag
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE )
						CG_AddBufferedSound( cgs.media.captureYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.captureOpponentSound );
					break;
				case GTS_RED_RETURN: // CTF: blue flag returned, 1FCTF: never used
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED )
						CG_AddBufferedSound( cgs.media.returnYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.returnOpponentSound );
					//
					CG_AddBufferedSound( cgs.media.blueFlagReturnedSound );
					break;
				case GTS_BLUE_RETURN: // CTF red flag returned, 1FCTF: neutral flag returned
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE )
						CG_AddBufferedSound( cgs.media.returnYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.returnOpponentSound );
					//
					CG_AddBufferedSound( cgs.media.redFlagReturnedSound );
					break;

				case GTS_RED_TAKEN: // CTF: red team took blue flag, 1FCTF: blue team took the neutral flag
					// if this player picked up the flag then a sound is played in CG_CheckLocalSounds
					if (cg.snap->ps.powerups[PW_BLUEFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
					}
					else {
						if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF) 
								CG_AddBufferedSound( cgs.media.yourTeamTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.enemyTookYourFlagSound );
						}
						else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
 							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
						}
					}
					break;
				case GTS_BLUE_TAKEN: // CTF: blue team took the red flag, 1FCTF red team took the neutral flag
					// if this player picked up the flag then a sound is played in CG_CheckLocalSounds
					if (cg.snap->ps.powerups[PW_REDFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
					}
					else {
						if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.yourTeamTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.enemyTookYourFlagSound );
						}
						else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
						}
					}
					break;
#ifdef MISSIONPACK
				case GTS_REDOBELISK_ATTACKED: // Overload: red obelisk is being attacked
					if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
						CG_AddBufferedSound( cgs.media.yourBaseIsUnderAttackSound );
					}
					break;
				case GTS_BLUEOBELISK_ATTACKED: // Overload: blue obelisk is being attacked
					if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
						CG_AddBufferedSound( cgs.media.yourBaseIsUnderAttackSound );
					}
					break;
#endif

				case GTS_REDTEAM_SCORED:
					CG_AddBufferedSound(cgs.media.redScoredSound);
					break;
				case GTS_BLUETEAM_SCORED:
					CG_AddBufferedSound(cgs.media.blueScoredSound);
					break;
				case GTS_REDTEAM_TOOK_LEAD:
					CG_AddBufferedSound(cgs.media.redLeadsSound);
					break;
				case GTS_BLUETEAM_TOOK_LEAD:
					CG_AddBufferedSound(cgs.media.blueLeadsSound);
					break;
				case GTS_TEAMS_ARE_TIED:
					CG_AddBufferedSound( cgs.media.teamsTiedSound );
					break;
#ifdef MISSIONPACK
				case GTS_KAMIKAZE:
					trap_S_StartLocalSound(cgs.media.kamikazeFarSound, CHAN_ANNOUNCER);
					break;
#endif
				default:
					break;
			}
			break;
		}

	case EV_PAIN:
		// local player sounds are triggered in CG_CheckLocalSounds,
		// so ignore events on the player
		DEBUGNAME("EV_PAIN");
		if ( cent->currentState.number != cg.snap->ps.clientNum ) {
			CG_PainEvent( cent, es->eventParm );
		}
		break;

	case EV_DEATH1:
	case EV_DEATH2:
	case EV_DEATH3:
		DEBUGNAME("EV_DEATHx");

		if (CG_WaterLevel(cent) == 3) {
			trap_S_StartSound(NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, "*drown.wav"));
		} else {
			trap_S_StartSound(NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, va("*death%i.wav", event - EV_DEATH1 + 1)));
		}

		break;


	case EV_OBITUARY:
		DEBUGNAME("EV_OBITUARY");
		CG_Obituary( es );
		break;

	//
	// powerup events
	//
	case EV_POWERUP_QUAD:
		DEBUGNAME("EV_POWERUP_QUAD");
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_QUAD;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.quadSound );
		break;
	case EV_POWERUP_BATTLESUIT:
		DEBUGNAME("EV_POWERUP_BATTLESUIT");
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_BATTLESUIT;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.protectSound );
		break;
	case EV_POWERUP_REGEN:
		DEBUGNAME("EV_POWERUP_REGEN");
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_REGEN;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.regenSound );
		break;

	case EV_GIB_PLAYER:
		DEBUGNAME("EV_GIB_PLAYER");
		// don't play gib sound when using the kamikaze because it interferes
		// with the kamikaze sound, downside is that the gib sound will also
		// not be played when someone is gibbed while just carrying the kamikaze
		if ( !(es->eFlags & EF_KAMIKAZE) ) {
			trap_S_StartSound( NULL, es->number, CHAN_BODY, cgs.media.gibSound );
		}
		CG_GibPlayer( cent->lerpOrigin );
		break;

	case EV_STOPLOOPINGSOUND:
		DEBUGNAME("EV_STOPLOOPINGSOUND");
		trap_S_StopLoopingSound( es->number );
		es->loopSound = 0;
		break;

	case EV_DEBUG_LINE:
		DEBUGNAME("EV_DEBUG_LINE");
		CG_Beam( cent );
		break;

	default:
		DEBUGNAME("UNKNOWN");
		CG_Error( "Unknown event: %i", event );
		break;
	}

}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* playerViewangles; int* playerMoveangles; int /*<<< orphan*/  playerChat; int /*<<< orphan*/  playerWeapon; void* playerTorso; void* playerLegs; int /*<<< orphan*/  playerinfo; } ;

/* Variables and functions */
#define  ANIM_ATTACK 152 
#define  ANIM_BACK 151 
#define  ANIM_CHAT 150 
#define  ANIM_CROUCH 149 
#define  ANIM_DIE 148 
#define  ANIM_GESTURE 147 
#define  ANIM_JUMP 146 
#define  ANIM_LOOKDOWN 145 
#define  ANIM_LOOKUP 144 
#define  ANIM_RUN 143 
#define  ANIM_STEPLEFT 142 
#define  ANIM_STEPRIGHT 141 
#define  ANIM_TURNLEFT 140 
#define  ANIM_TURNRIGHT 139 
#define  ANIM_WALK 138 
#define  ANIM_WEAPON1 137 
#define  ANIM_WEAPON10 136 
#define  ANIM_WEAPON2 135 
#define  ANIM_WEAPON3 134 
#define  ANIM_WEAPON4 133 
#define  ANIM_WEAPON5 132 
#define  ANIM_WEAPON6 131 
#define  ANIM_WEAPON7 130 
#define  ANIM_WEAPON8 129 
#define  ANIM_WEAPON9 128 
 void* BOTH_DEATH1 ; 
 void* LEGS_BACK ; 
 void* LEGS_IDLE ; 
 void* LEGS_IDLECR ; 
 void* LEGS_JUMP ; 
 void* LEGS_RUN ; 
 void* LEGS_WALK ; 
 size_t PITCH ; 
 void* TORSO_ATTACK ; 
 void* TORSO_GESTURE ; 
 void* TORSO_STAND ; 
 int /*<<< orphan*/  UI_PlayerInfo_SetInfo (int /*<<< orphan*/ *,void*,void*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  WP_BFG ; 
 int /*<<< orphan*/  WP_GAUNTLET ; 
 int /*<<< orphan*/  WP_GRAPPLING_HOOK ; 
 int /*<<< orphan*/  WP_GRENADE_LAUNCHER ; 
 int /*<<< orphan*/  WP_LIGHTNING ; 
 int /*<<< orphan*/  WP_MACHINEGUN ; 
 int /*<<< orphan*/  WP_NONE ; 
 int /*<<< orphan*/  WP_NUM_WEAPONS ; 
 int /*<<< orphan*/  WP_PLASMAGUN ; 
 int /*<<< orphan*/  WP_RAILGUN ; 
 int /*<<< orphan*/  WP_ROCKET_LAUNCHER ; 
 int /*<<< orphan*/  WP_SHOTGUN ; 
 size_t YAW ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ s_controls ; 

__attribute__((used)) static void Controls_UpdateModel( int anim ) {
	VectorClear( s_controls.playerViewangles );
	VectorClear( s_controls.playerMoveangles );
	s_controls.playerViewangles[YAW] = 180 - 30;
	s_controls.playerMoveangles[YAW] = s_controls.playerViewangles[YAW];
	s_controls.playerLegs		     = LEGS_IDLE;
	s_controls.playerTorso			 = TORSO_STAND;
	s_controls.playerWeapon			 = WP_NUM_WEAPONS;
	s_controls.playerChat			 = qfalse;

	switch( anim ) {
	case ANIM_RUN:	
		s_controls.playerLegs = LEGS_RUN;
		break;

	case ANIM_WALK:	
		s_controls.playerLegs = LEGS_WALK;
		break;

	case ANIM_BACK:	
		s_controls.playerLegs = LEGS_BACK;
		break;

	case ANIM_JUMP:	
		s_controls.playerLegs = LEGS_JUMP;
		break;

	case ANIM_CROUCH:	
		s_controls.playerLegs = LEGS_IDLECR;
		break;

	case ANIM_TURNLEFT:
		s_controls.playerViewangles[YAW] += 90;
		break;

	case ANIM_TURNRIGHT:
		s_controls.playerViewangles[YAW] -= 90;
		break;

	case ANIM_STEPLEFT:
		s_controls.playerLegs = LEGS_WALK;
		s_controls.playerMoveangles[YAW] = s_controls.playerViewangles[YAW] + 90;
		break;

	case ANIM_STEPRIGHT:
		s_controls.playerLegs = LEGS_WALK;
		s_controls.playerMoveangles[YAW] = s_controls.playerViewangles[YAW] - 90;
		break;

	case ANIM_LOOKUP:
		s_controls.playerViewangles[PITCH] = -45;
		break;

	case ANIM_LOOKDOWN:
		s_controls.playerViewangles[PITCH] = 45;
		break;

	case ANIM_WEAPON1:
		s_controls.playerWeapon = WP_GAUNTLET;
		break;

	case ANIM_WEAPON2:
		s_controls.playerWeapon = WP_MACHINEGUN;
		break;

	case ANIM_WEAPON3:
		s_controls.playerWeapon = WP_SHOTGUN;
		break;

	case ANIM_WEAPON4:
		s_controls.playerWeapon = WP_GRENADE_LAUNCHER;
		break;

	case ANIM_WEAPON5:
		s_controls.playerWeapon = WP_ROCKET_LAUNCHER;
		break;

	case ANIM_WEAPON6:
		s_controls.playerWeapon = WP_LIGHTNING;
		break;

	case ANIM_WEAPON7:
		s_controls.playerWeapon = WP_RAILGUN;
		break;

	case ANIM_WEAPON8:
		s_controls.playerWeapon = WP_PLASMAGUN;
		break;

	case ANIM_WEAPON9:
		s_controls.playerWeapon = WP_BFG;
		break;

	case ANIM_WEAPON10:
		s_controls.playerWeapon = WP_GRAPPLING_HOOK;
		break;

	case ANIM_ATTACK:
		s_controls.playerTorso = TORSO_ATTACK;
		break;

	case ANIM_GESTURE:
		s_controls.playerTorso = TORSO_GESTURE;
		break;

	case ANIM_DIE:
		s_controls.playerLegs = BOTH_DEATH1;
		s_controls.playerTorso = BOTH_DEATH1;
		s_controls.playerWeapon = WP_NONE;
		break;

	case ANIM_CHAT:
		s_controls.playerChat = qtrue;
		break;

	default:
		break;
	}

	UI_PlayerInfo_SetInfo( &s_controls.playerinfo, s_controls.playerLegs, s_controls.playerTorso, s_controls.playerViewangles, s_controls.playerMoveangles, s_controls.playerWeapon, s_controls.playerChat );
}
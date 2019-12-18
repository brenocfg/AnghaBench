#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_6__ {int serverTime; int* angles; float forwardmove; float rightmove; float upmove; int /*<<< orphan*/  weapon; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ usercmd_t ;
struct TYPE_7__ {int actionflags; float* viewangles; int* dir; int speed; int /*<<< orphan*/  weapon; } ;
typedef  TYPE_2__ bot_input_t ;

/* Variables and functions */
 int ACTION_AFFIRMATIVE ; 
 int ACTION_ATTACK ; 
 int ACTION_CROUCH ; 
 int ACTION_DELAYEDJUMP ; 
 int ACTION_FOLLOWME ; 
 int ACTION_GESTURE ; 
 int ACTION_GETFLAG ; 
 int ACTION_GUARDBASE ; 
 int ACTION_JUMP ; 
 int ACTION_MOVEBACK ; 
 int ACTION_MOVEFORWARD ; 
 int ACTION_MOVELEFT ; 
 int ACTION_MOVERIGHT ; 
 int ACTION_NEGATIVE ; 
 int ACTION_PATROL ; 
 int ACTION_RESPAWN ; 
 int ACTION_TALK ; 
 int ACTION_USE ; 
 int ACTION_WALK ; 
 void* ANGLE2SHORT (float) ; 
 int /*<<< orphan*/  AngleVectors (float*,float*,float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUTTON_AFFIRMATIVE ; 
 int /*<<< orphan*/  BUTTON_ATTACK ; 
 int /*<<< orphan*/  BUTTON_FOLLOWME ; 
 int /*<<< orphan*/  BUTTON_GESTURE ; 
 int /*<<< orphan*/  BUTTON_GETFLAG ; 
 int /*<<< orphan*/  BUTTON_GUARDBASE ; 
 int /*<<< orphan*/  BUTTON_NEGATIVE ; 
 int /*<<< orphan*/  BUTTON_PATROL ; 
 int /*<<< orphan*/  BUTTON_TALK ; 
 int /*<<< orphan*/  BUTTON_USE_HOLDABLE ; 
 int /*<<< orphan*/  BUTTON_WALKING ; 
 float DotProduct (float*,int*) ; 
 size_t PITCH ; 
 size_t ROLL ; 
 size_t YAW ; 
 float fabs (float) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void BotInputToUserCommand(bot_input_t *bi, usercmd_t *ucmd, int delta_angles[3], int time) {
	vec3_t angles, forward, right;
	short temp;
	int j;
	float f, r, u, m;

	//clear the whole structure
	memset(ucmd, 0, sizeof(usercmd_t));
	//the duration for the user command in milli seconds
	ucmd->serverTime = time;
	//
	if (bi->actionflags & ACTION_DELAYEDJUMP) {
		bi->actionflags |= ACTION_JUMP;
		bi->actionflags &= ~ACTION_DELAYEDJUMP;
	}
	//set the buttons
	if (bi->actionflags & ACTION_RESPAWN) ucmd->buttons = BUTTON_ATTACK;
	if (bi->actionflags & ACTION_ATTACK) ucmd->buttons |= BUTTON_ATTACK;
	if (bi->actionflags & ACTION_TALK) ucmd->buttons |= BUTTON_TALK;
	if (bi->actionflags & ACTION_GESTURE) ucmd->buttons |= BUTTON_GESTURE;
	if (bi->actionflags & ACTION_USE) ucmd->buttons |= BUTTON_USE_HOLDABLE;
	if (bi->actionflags & ACTION_WALK) ucmd->buttons |= BUTTON_WALKING;
	if (bi->actionflags & ACTION_AFFIRMATIVE) ucmd->buttons |= BUTTON_AFFIRMATIVE;
	if (bi->actionflags & ACTION_NEGATIVE) ucmd->buttons |= BUTTON_NEGATIVE;
	if (bi->actionflags & ACTION_GETFLAG) ucmd->buttons |= BUTTON_GETFLAG;
	if (bi->actionflags & ACTION_GUARDBASE) ucmd->buttons |= BUTTON_GUARDBASE;
	if (bi->actionflags & ACTION_PATROL) ucmd->buttons |= BUTTON_PATROL;
	if (bi->actionflags & ACTION_FOLLOWME) ucmd->buttons |= BUTTON_FOLLOWME;
	//
	ucmd->weapon = bi->weapon;
	//set the view angles
	//NOTE: the ucmd->angles are the angles WITHOUT the delta angles
	ucmd->angles[PITCH] = ANGLE2SHORT(bi->viewangles[PITCH]);
	ucmd->angles[YAW] = ANGLE2SHORT(bi->viewangles[YAW]);
	ucmd->angles[ROLL] = ANGLE2SHORT(bi->viewangles[ROLL]);
	//subtract the delta angles
	for (j = 0; j < 3; j++) {
		temp = ucmd->angles[j] - delta_angles[j];
		/*NOTE: disabled because temp should be mod first
		if ( j == PITCH ) {
			// don't let the player look up or down more than 90 degrees
			if ( temp > 16000 ) temp = 16000;
			else if ( temp < -16000 ) temp = -16000;
		}
		*/
		ucmd->angles[j] = temp;
	}
	//NOTE: movement is relative to the REAL view angles
	//get the horizontal forward and right vector
	//get the pitch in the range [-180, 180]
	if (bi->dir[2]) angles[PITCH] = bi->viewangles[PITCH];
	else angles[PITCH] = 0;
	angles[YAW] = bi->viewangles[YAW];
	angles[ROLL] = 0;
	AngleVectors(angles, forward, right, NULL);
	//bot input speed is in the range [0, 400]
	bi->speed = bi->speed * 127 / 400;
	//set the view independent movement
	f = DotProduct(forward, bi->dir);
	r = DotProduct(right, bi->dir);
	u = fabs(forward[2]) * bi->dir[2];
	m = fabs(f);

	if (fabs(r) > m) {
		m = fabs(r);
	}

	if (fabs(u) > m) {
		m = fabs(u);
	}

	if (m > 0) {
		f *= bi->speed / m;
		r *= bi->speed / m;
		u *= bi->speed / m;
	}

	ucmd->forwardmove = f;
	ucmd->rightmove = r;
	ucmd->upmove = u;

	if (bi->actionflags & ACTION_MOVEFORWARD) ucmd->forwardmove = 127;
	if (bi->actionflags & ACTION_MOVEBACK) ucmd->forwardmove = -127;
	if (bi->actionflags & ACTION_MOVELEFT) ucmd->rightmove = -127;
	if (bi->actionflags & ACTION_MOVERIGHT) ucmd->rightmove = 127;
	//jump/moveup
	if (bi->actionflags & ACTION_JUMP) ucmd->upmove = 127;
	//crouch/movedown
	if (bi->actionflags & ACTION_CROUCH) ucmd->upmove = -127;
}
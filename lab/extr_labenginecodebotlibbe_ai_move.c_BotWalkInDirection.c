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
typedef  double* vec3_t ;
struct TYPE_6__ {double* origin; int moveflags; double* velocity; float thinktime; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  presencetype; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_7__ {int frames; int stopevent; double* endpos; int /*<<< orphan*/  velocity; } ;
typedef  TYPE_2__ aas_clientmove_t ;

/* Variables and functions */
 scalar_t__ AAS_OnGround (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_PredictClientMovement (TYPE_2__*,int /*<<< orphan*/ ,double*,int,int,double*,double*,int,int,float,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BotCheckBarrierJump (TYPE_1__*,double*,float) ; 
 float BotGapDistance (double*,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Crouch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_Move (int /*<<< orphan*/ ,double*,float) ; 
 int MFL_BARRIERJUMP ; 
 int MFL_ONGROUND ; 
 int MOVE_CROUCH ; 
 int MOVE_JUMP ; 
 double PREDICTIONTIME_JUMP ; 
 int PRESENCE_CROUCH ; 
 int PRESENCE_NORMAL ; 
 int SE_ENTERLAVA ; 
 int SE_ENTERSLIME ; 
 int SE_ENTERWATER ; 
 int SE_HITGROUND ; 
 int SE_HITGROUNDDAMAGE ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 float VectorLength (double*) ; 
 int /*<<< orphan*/  VectorNormalize (double*) ; 
 int /*<<< orphan*/  VectorNormalize2 (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  VectorScale (double*,float,double*) ; 
 int qfalse ; 
 int qtrue ; 

int BotWalkInDirection(bot_movestate_t *ms, vec3_t dir, float speed, int type)
{
	vec3_t hordir, cmdmove, velocity, tmpdir, origin;
	int presencetype, maxframes, cmdframes, stopevent;
	aas_clientmove_t move;
	float dist;

	if (AAS_OnGround(ms->origin, ms->presencetype, ms->entitynum)) ms->moveflags |= MFL_ONGROUND;
	//if the bot is on the ground
	if (ms->moveflags & MFL_ONGROUND)
	{
		//if there is a barrier the bot can jump on
		if (BotCheckBarrierJump(ms, dir, speed)) return qtrue;
		//remove barrier jump flag
		ms->moveflags &= ~MFL_BARRIERJUMP;
		//get the presence type for the movement
		if ((type & MOVE_CROUCH) && !(type & MOVE_JUMP)) presencetype = PRESENCE_CROUCH;
		else presencetype = PRESENCE_NORMAL;
		//horizontal direction
		hordir[0] = dir[0];
		hordir[1] = dir[1];
		hordir[2] = 0;
		VectorNormalize(hordir);
		//if the bot is not supposed to jump
		if (!(type & MOVE_JUMP))
		{
			//if there is a gap, try to jump over it
			if (BotGapDistance(ms->origin, hordir, ms->entitynum) > 0) type |= MOVE_JUMP;
		} //end if
		//get command movement
		VectorScale(hordir, speed, cmdmove);
		VectorCopy(ms->velocity, velocity);
		//
		if (type & MOVE_JUMP)
		{
			//botimport.Print(PRT_MESSAGE, "trying jump\n");
			cmdmove[2] = 400;
			maxframes = PREDICTIONTIME_JUMP / 0.1;
			cmdframes = 1;
			stopevent = SE_HITGROUND|SE_HITGROUNDDAMAGE|
						SE_ENTERWATER|SE_ENTERSLIME|SE_ENTERLAVA;
		} //end if
		else
		{
			maxframes = 2;
			cmdframes = 2;
			stopevent = SE_HITGROUNDDAMAGE|
						SE_ENTERWATER|SE_ENTERSLIME|SE_ENTERLAVA;
		} //end else
		//AAS_ClearShownDebugLines();
		//
		VectorCopy(ms->origin, origin);
		origin[2] += 0.5;
		AAS_PredictClientMovement(&move, ms->entitynum, origin, presencetype, qtrue,
									velocity, cmdmove, cmdframes, maxframes, 0.1f,
									stopevent, 0, qfalse);//qtrue);
		//if prediction time wasn't enough to fully predict the movement
		if (move.frames >= maxframes && (type & MOVE_JUMP))
		{
			//botimport.Print(PRT_MESSAGE, "client %d: max prediction frames\n", ms->client);
			return qfalse;
		} //end if
		//don't enter slime or lava and don't fall from too high
		if (move.stopevent & (SE_ENTERSLIME|SE_ENTERLAVA|SE_HITGROUNDDAMAGE))
		{
			//botimport.Print(PRT_MESSAGE, "client %d: would be hurt ", ms->client);
			//if (move.stopevent & SE_ENTERSLIME) botimport.Print(PRT_MESSAGE, "slime\n");
			//if (move.stopevent & SE_ENTERLAVA) botimport.Print(PRT_MESSAGE, "lava\n");
			//if (move.stopevent & SE_HITGROUNDDAMAGE) botimport.Print(PRT_MESSAGE, "hitground\n");
			return qfalse;
		} //end if
		//if ground was hit
		if (move.stopevent & SE_HITGROUND)
		{
			//check for nearby gap
			VectorNormalize2(move.velocity, tmpdir);
			dist = BotGapDistance(move.endpos, tmpdir, ms->entitynum);
			if (dist > 0) return qfalse;
			//
			dist = BotGapDistance(move.endpos, hordir, ms->entitynum);
			if (dist > 0) return qfalse;
		} //end if
		//get horizontal movement
		tmpdir[0] = move.endpos[0] - ms->origin[0];
		tmpdir[1] = move.endpos[1] - ms->origin[1];
		tmpdir[2] = 0;
		//
		//AAS_DrawCross(move.endpos, 4, LINECOLOR_BLUE);
		//the bot is blocked by something
		if (VectorLength(tmpdir) < speed * ms->thinktime * 0.5) return qfalse;
		//perform the movement
		if (type & MOVE_JUMP) EA_Jump(ms->client);
		if (type & MOVE_CROUCH) EA_Crouch(ms->client);
		EA_Move(ms->client, hordir, speed);
		//movement was succesfull
		return qtrue;
	} //end if
	else
	{
		if (ms->moveflags & MFL_BARRIERJUMP)
		{
			//if near the top or going down
			if (ms->velocity[2] < 50)
			{
				EA_Move(ms->client, dir, speed);
			} //end if
		} //end if
		//FIXME: do air control to avoid hazards
		return qtrue;
	} //end else
}
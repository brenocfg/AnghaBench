#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_4__ {int stopevent; } ;
typedef  TYPE_1__ aas_clientmove_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ClearShownDebugLines () ; 
 int /*<<< orphan*/  AAS_PredictClientMovement (TYPE_1__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_Swimming (int*) ; 
 int /*<<< orphan*/  PRESENCE_NORMAL ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  SE_HITGROUND ; 
 int SE_LEAVEGROUND ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,int,int*) ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void AAS_TestMovementPrediction(int entnum, vec3_t origin, vec3_t dir)
{
	vec3_t velocity, cmdmove;
	aas_clientmove_t move;

	VectorClear(velocity);
	if (!AAS_Swimming(origin)) dir[2] = 0;
	VectorNormalize(dir);
	VectorScale(dir, 400, cmdmove);
	cmdmove[2] = 224;
	AAS_ClearShownDebugLines();
	AAS_PredictClientMovement(&move, entnum, origin, PRESENCE_NORMAL, qtrue,
									velocity, cmdmove, 13, 13, 0.1f, SE_HITGROUND, 0, qtrue);//SE_LEAVEGROUND);
	if (move.stopevent & SE_LEAVEGROUND)
	{
		botimport.Print(PRT_MESSAGE, "leave ground\n");
	} //end if
}
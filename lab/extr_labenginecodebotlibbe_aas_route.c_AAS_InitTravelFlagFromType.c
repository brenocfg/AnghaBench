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
struct TYPE_2__ {void** travelflagfortype; } ;

/* Variables and functions */
 int MAX_TRAVELTYPES ; 
 void* TFL_BARRIERJUMP ; 
 void* TFL_BFGJUMP ; 
 void* TFL_CROUCH ; 
 void* TFL_DOUBLEJUMP ; 
 void* TFL_ELEVATOR ; 
 void* TFL_FUNCBOB ; 
 void* TFL_GRAPPLEHOOK ; 
 void* TFL_INVALID ; 
 void* TFL_JUMP ; 
 void* TFL_JUMPPAD ; 
 void* TFL_LADDER ; 
 void* TFL_RAMPJUMP ; 
 void* TFL_ROCKETJUMP ; 
 void* TFL_STRAFEJUMP ; 
 void* TFL_SWIM ; 
 void* TFL_TELEPORT ; 
 void* TFL_WALK ; 
 void* TFL_WALKOFFLEDGE ; 
 void* TFL_WATERJUMP ; 
 size_t TRAVEL_BARRIERJUMP ; 
 size_t TRAVEL_BFGJUMP ; 
 size_t TRAVEL_CROUCH ; 
 size_t TRAVEL_DOUBLEJUMP ; 
 size_t TRAVEL_ELEVATOR ; 
 size_t TRAVEL_FUNCBOB ; 
 size_t TRAVEL_GRAPPLEHOOK ; 
 size_t TRAVEL_INVALID ; 
 size_t TRAVEL_JUMP ; 
 size_t TRAVEL_JUMPPAD ; 
 size_t TRAVEL_LADDER ; 
 size_t TRAVEL_RAMPJUMP ; 
 size_t TRAVEL_ROCKETJUMP ; 
 size_t TRAVEL_STRAFEJUMP ; 
 size_t TRAVEL_SWIM ; 
 size_t TRAVEL_TELEPORT ; 
 size_t TRAVEL_WALK ; 
 size_t TRAVEL_WALKOFFLEDGE ; 
 size_t TRAVEL_WATERJUMP ; 
 TYPE_1__ aasworld ; 

void AAS_InitTravelFlagFromType(void)
{
	int i;

	for (i = 0; i < MAX_TRAVELTYPES; i++)
	{
		aasworld.travelflagfortype[i] = TFL_INVALID;
	} //end for
	aasworld.travelflagfortype[TRAVEL_INVALID] = TFL_INVALID;
	aasworld.travelflagfortype[TRAVEL_WALK] = TFL_WALK;
	aasworld.travelflagfortype[TRAVEL_CROUCH] = TFL_CROUCH;
	aasworld.travelflagfortype[TRAVEL_BARRIERJUMP] = TFL_BARRIERJUMP;
	aasworld.travelflagfortype[TRAVEL_JUMP] = TFL_JUMP;
	aasworld.travelflagfortype[TRAVEL_LADDER] = TFL_LADDER;
	aasworld.travelflagfortype[TRAVEL_WALKOFFLEDGE] = TFL_WALKOFFLEDGE;
	aasworld.travelflagfortype[TRAVEL_SWIM] = TFL_SWIM;
	aasworld.travelflagfortype[TRAVEL_WATERJUMP] = TFL_WATERJUMP;
	aasworld.travelflagfortype[TRAVEL_TELEPORT] = TFL_TELEPORT;
	aasworld.travelflagfortype[TRAVEL_ELEVATOR] = TFL_ELEVATOR;
	aasworld.travelflagfortype[TRAVEL_ROCKETJUMP] = TFL_ROCKETJUMP;
	aasworld.travelflagfortype[TRAVEL_BFGJUMP] = TFL_BFGJUMP;
	aasworld.travelflagfortype[TRAVEL_GRAPPLEHOOK] = TFL_GRAPPLEHOOK;
	aasworld.travelflagfortype[TRAVEL_DOUBLEJUMP] = TFL_DOUBLEJUMP;
	aasworld.travelflagfortype[TRAVEL_RAMPJUMP] = TFL_RAMPJUMP;
	aasworld.travelflagfortype[TRAVEL_STRAFEJUMP] = TFL_STRAFEJUMP;
	aasworld.travelflagfortype[TRAVEL_JUMPPAD] = TFL_JUMPPAD;
	aasworld.travelflagfortype[TRAVEL_FUNCBOB] = TFL_FUNCBOB;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void AAS_PrintTravelType(int traveltype)
{
#ifdef DEBUG
	char *str;
	//
	switch(traveltype & TRAVELTYPE_MASK)
	{
		case TRAVEL_INVALID: str = "TRAVEL_INVALID"; break;
		case TRAVEL_WALK: str = "TRAVEL_WALK"; break;
		case TRAVEL_CROUCH: str = "TRAVEL_CROUCH"; break;
		case TRAVEL_BARRIERJUMP: str = "TRAVEL_BARRIERJUMP"; break;
		case TRAVEL_JUMP: str = "TRAVEL_JUMP"; break;
		case TRAVEL_LADDER: str = "TRAVEL_LADDER"; break;
		case TRAVEL_WALKOFFLEDGE: str = "TRAVEL_WALKOFFLEDGE"; break;
		case TRAVEL_SWIM: str = "TRAVEL_SWIM"; break;
		case TRAVEL_WATERJUMP: str = "TRAVEL_WATERJUMP"; break;
		case TRAVEL_TELEPORT: str = "TRAVEL_TELEPORT"; break;
		case TRAVEL_ELEVATOR: str = "TRAVEL_ELEVATOR"; break;
		case TRAVEL_ROCKETJUMP: str = "TRAVEL_ROCKETJUMP"; break;
		case TRAVEL_BFGJUMP: str = "TRAVEL_BFGJUMP"; break;
		case TRAVEL_GRAPPLEHOOK: str = "TRAVEL_GRAPPLEHOOK"; break;
		case TRAVEL_JUMPPAD: str = "TRAVEL_JUMPPAD"; break;
		case TRAVEL_FUNCBOB: str = "TRAVEL_FUNCBOB"; break;
		default: str = "UNKNOWN TRAVEL TYPE"; break;
	} //end switch
	botimport.Print(PRT_MESSAGE, "%s", str);
#endif
}
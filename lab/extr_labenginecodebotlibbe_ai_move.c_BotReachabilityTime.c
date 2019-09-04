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
struct TYPE_4__ {int traveltype; } ;
typedef  TYPE_1__ aas_reachability_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 int TRAVELTYPE_MASK ; 
#define  TRAVEL_BARRIERJUMP 142 
#define  TRAVEL_BFGJUMP 141 
#define  TRAVEL_CROUCH 140 
#define  TRAVEL_ELEVATOR 139 
#define  TRAVEL_FUNCBOB 138 
#define  TRAVEL_GRAPPLEHOOK 137 
#define  TRAVEL_JUMP 136 
#define  TRAVEL_JUMPPAD 135 
#define  TRAVEL_LADDER 134 
#define  TRAVEL_ROCKETJUMP 133 
#define  TRAVEL_SWIM 132 
#define  TRAVEL_TELEPORT 131 
#define  TRAVEL_WALK 130 
#define  TRAVEL_WALKOFFLEDGE 129 
#define  TRAVEL_WATERJUMP 128 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

int BotReachabilityTime(aas_reachability_t *reach)
{
	switch(reach->traveltype & TRAVELTYPE_MASK)
	{
		case TRAVEL_WALK: return 5;
		case TRAVEL_CROUCH: return 5;
		case TRAVEL_BARRIERJUMP: return 5;
		case TRAVEL_LADDER: return 6;
		case TRAVEL_WALKOFFLEDGE: return 5;
		case TRAVEL_JUMP: return 5;
		case TRAVEL_SWIM: return 5;
		case TRAVEL_WATERJUMP: return 5;
		case TRAVEL_TELEPORT: return 5;
		case TRAVEL_ELEVATOR: return 10;
		case TRAVEL_GRAPPLEHOOK: return 8;
		case TRAVEL_ROCKETJUMP: return 6;
		case TRAVEL_BFGJUMP: return 6;
		case TRAVEL_JUMPPAD: return 10;
		case TRAVEL_FUNCBOB: return 10;
		default:
		{
			botimport.Print(PRT_ERROR, "travel type %d not implemented yet\n", reach->traveltype);
			return 8;
		} //end case
	} //end switch
}
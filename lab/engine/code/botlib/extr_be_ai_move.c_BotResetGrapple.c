#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int moveflags; scalar_t__ grapplevisible_time; int /*<<< orphan*/  client; int /*<<< orphan*/  lastreachnum; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_9__ {int traveltype; } ;
typedef  TYPE_2__ aas_reachability_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  string; } ;
struct TYPE_10__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ReachabilityFromNum (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EA_Command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MFL_ACTIVEGRAPPLE ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TRAVELTYPE_MASK ; 
 int TRAVEL_GRAPPLEHOOK ; 
 TYPE_5__ botimport ; 
 TYPE_4__* cmd_grappleoff ; 
 TYPE_3__* offhandgrapple ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void BotResetGrapple(bot_movestate_t *ms)
{
	aas_reachability_t reach;

	AAS_ReachabilityFromNum(ms->lastreachnum, &reach);
	//if not using the grapple hook reachability anymore
	if ((reach.traveltype & TRAVELTYPE_MASK) != TRAVEL_GRAPPLEHOOK)
	{
		if ((ms->moveflags & MFL_ACTIVEGRAPPLE) || ms->grapplevisible_time)
		{
			if (offhandgrapple->value)
				EA_Command(ms->client, cmd_grappleoff->string);
			ms->moveflags &= ~MFL_ACTIVEGRAPPLE;
			ms->grapplevisible_time = 0;
#ifdef DEBUG_GRAPPLE
			botimport.Print(PRT_MESSAGE, "reset grapple\n");
#endif //DEBUG_GRAPPLE
		} //end if
	} //end if
}
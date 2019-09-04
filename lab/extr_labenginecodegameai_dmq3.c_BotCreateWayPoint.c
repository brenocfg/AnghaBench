#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_2__ vec3_t ;
struct TYPE_8__ {int areanum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  origin; } ;
struct TYPE_10__ {int /*<<< orphan*/ * prev; struct TYPE_10__* next; TYPE_1__ goal; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ bot_waypoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRT_WARNING ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VectorCopy (TYPE_2__,int /*<<< orphan*/ ) ; 
 TYPE_3__* botai_freewaypoints ; 

bot_waypoint_t *BotCreateWayPoint(char *name, vec3_t origin, int areanum) {
	bot_waypoint_t *wp;
	vec3_t waypointmins = {-8, -8, -8}, waypointmaxs = {8, 8, 8};

	wp = botai_freewaypoints;
	if ( !wp ) {
		BotAI_Print( PRT_WARNING, "BotCreateWayPoint: Out of waypoints\n" );
		return NULL;
	}
	botai_freewaypoints = botai_freewaypoints->next;

	Q_strncpyz( wp->name, name, sizeof(wp->name) );
	VectorCopy(origin, wp->goal.origin);
	VectorCopy(waypointmins, wp->goal.mins);
	VectorCopy(waypointmaxs, wp->goal.maxs);
	wp->goal.areanum = areanum;
	wp->next = NULL;
	wp->prev = NULL;
	return wp;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int torsoAnim; } ;
struct TYPE_7__ {int /*<<< orphan*/  think; scalar_t__ nextthink; TYPE_1__ s; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_8__ {scalar_t__ time; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int /*<<< orphan*/  CelebrateStop ; 
 int /*<<< orphan*/  EV_TAUNT ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TIMER_GESTURE ; 
 int TORSO_GESTURE ; 
 TYPE_3__ level ; 

__attribute__((used)) static void CelebrateStart( gentity_t *player ) {
	player->s.torsoAnim = ( ( player->s.torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | TORSO_GESTURE;
	player->nextthink = level.time + TIMER_GESTURE;
	player->think = CelebrateStop;

	/*
	player->client->ps.events[player->client->ps.eventSequence & (MAX_PS_EVENTS-1)] = EV_TAUNT;
	player->client->ps.eventParms[player->client->ps.eventSequence & (MAX_PS_EVENTS-1)] = 0;
	player->client->ps.eventSequence++;
	*/
	G_AddEvent(player, EV_TAUNT, 0);
}
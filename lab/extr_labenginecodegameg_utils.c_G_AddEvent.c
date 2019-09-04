#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int event; int eventParm; int /*<<< orphan*/  number; } ;
struct TYPE_10__ {int /*<<< orphan*/  eventTime; TYPE_3__ s; TYPE_2__* client; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_11__ {int /*<<< orphan*/  time; } ;
struct TYPE_7__ {int externalEvent; int externalEventParm; int /*<<< orphan*/  externalEventTime; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int EV_EVENT_BIT1 ; 
 int EV_EVENT_BITS ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ level ; 

void G_AddEvent( gentity_t *ent, int event, int eventParm ) {
	int		bits;

	if ( !event ) {
		G_Printf( "G_AddEvent: zero event added for entity %i\n", ent->s.number );
		return;
	}

	// clients need to add the event in playerState_t instead of entityState_t
	if ( ent->client ) {
		bits = ent->client->ps.externalEvent & EV_EVENT_BITS;
		bits = ( bits + EV_EVENT_BIT1 ) & EV_EVENT_BITS;
		ent->client->ps.externalEvent = event | bits;
		ent->client->ps.externalEventParm = eventParm;
		ent->client->ps.externalEventTime = level.time;
	} else {
		bits = ent->s.event & EV_EVENT_BITS;
		bits = ( bits + EV_EVENT_BIT1 ) & EV_EVENT_BITS;
		ent->s.event = event | bits;
		ent->s.eventParm = eventParm;
	}
	ent->eventTime = level.time;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int entityEventSequence; int eventSequence; int* events; int externalEvent; int /*<<< orphan*/  clientNum; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ playerState_t ;
struct TYPE_8__ {int /*<<< orphan*/  singleClient; int /*<<< orphan*/  svFlags; } ;
struct TYPE_11__ {int number; int /*<<< orphan*/  otherEntityNum; int /*<<< orphan*/  eFlags; scalar_t__ eType; } ;
struct TYPE_10__ {TYPE_1__ r; TYPE_7__ s; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_2__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_PLAYER_EVENT ; 
 scalar_t__ ET_EVENTS ; 
 TYPE_3__* G_TempEntity (int /*<<< orphan*/ ,int) ; 
 int MAX_PS_EVENTS ; 
 int /*<<< orphan*/  SVF_NOTSINGLECLIENT ; 
 int /*<<< orphan*/  qtrue ; 

void SendPendingPredictableEvents( playerState_t *ps ) {
	gentity_t *t;
	int event, seq;
	int extEvent, number;

	// if there are still events pending
	if ( ps->entityEventSequence < ps->eventSequence ) {
		// create a temporary entity for this event which is sent to everyone
		// except the client who generated the event
		seq = ps->entityEventSequence & (MAX_PS_EVENTS-1);
		event = ps->events[ seq ] | ( ( ps->entityEventSequence & 3 ) << 8 );
		// set external event to zero before calling BG_PlayerStateToEntityState
		extEvent = ps->externalEvent;
		ps->externalEvent = 0;
		// create temporary entity for event
		t = G_TempEntity( ps->origin, event );
		number = t->s.number;
		BG_PlayerStateToEntityState( ps, &t->s, qtrue );
		t->s.number = number;
		t->s.eType = ET_EVENTS + event;
		t->s.eFlags |= EF_PLAYER_EVENT;
		t->s.otherEntityNum = ps->clientNum;
		// send to everyone except the client who generated the event
		t->r.svFlags |= SVF_NOTSINGLECLIENT;
		t->r.singleClient = ps->clientNum;
		// set back external event
		ps->externalEvent = extEvent;
	}
}
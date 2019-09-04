#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_22__ {size_t entityNum; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_20__ {int contents; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* look ) (TYPE_5__*,TYPE_5__*,TYPE_4__*) ;TYPE_3__* client; TYPE_2__ r; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_19__ {scalar_t__* stats; int /*<<< orphan*/  clientNum; int /*<<< orphan*/  viewangles; } ;
struct TYPE_21__ {int lastLookAt; TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONTENTS_LOOKAT ; 
 int CONTENTS_SOLID ; 
 int /*<<< orphan*/  CalcMuzzlePoint (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t STAT_HEALTH ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* g_entities ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  trap_Trace (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vec3_origin ; 

void ClientLookAtTriggers( gentity_t *ent ) {
	trace_t trace;
	vec3_t start, end;
	vec3_t forward, right, up;
	gentity_t* trigger;
	gentity_t* last_trigger;

	// Double check that we're definitely a player.
	if ( !ent->client ) {
		return;
	}

	// Ignore dead clients.
	if ( ent->client->ps.stats[STAT_HEALTH] <= 0 ) {
		// Clear the last lookat entity when dead.
		if ( ent->client->lastLookAt ) {
			last_trigger = &g_entities[ ent->client->lastLookAt ];
			if( last_trigger->look )
				last_trigger->look( last_trigger, ent, NULL );
			ent->client->lastLookAt = 0;
		}
		return;
	}

	// Calculate the start and end of the ray.
	AngleVectors( ent->client->ps.viewangles, forward, right, up );
	CalcMuzzlePoint( ent, forward, right, up, start );
	VectorMA( start, 131072, forward, end );

	trap_Trace( &trace, start, vec3_origin, vec3_origin, end,
		ent->client->ps.clientNum, CONTENTS_SOLID|CONTENTS_LOOKAT );

	// If the new trigger is not what the client was last looking at, invoke the
	// last trigger with 'trace' set to NULL & reset. This allows entites to
	// reset any internal state they may have.
	if ( ent->client->lastLookAt && ent->client->lastLookAt != trace.entityNum ) {
		last_trigger = &g_entities[ ent->client->lastLookAt ];
		if( last_trigger->look )
			last_trigger->look( last_trigger, ent, NULL );
		ent->client->lastLookAt = 0;
	}

	trigger = &g_entities[ trace.entityNum ];

	// Check ray hit a lookat trigger and not a wall.
	if ( !trace.entityNum || (trigger->r.contents & CONTENTS_LOOKAT) == 0 )
		return;

	// Store the trigger for the next frame, and call the look function (if it
	// exists).
	ent->client->lastLookAt = trace.entityNum;
	if (trigger->look) {
		trigger->look(trigger, ent, &trace);
	}
}
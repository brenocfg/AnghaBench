#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ freetime; int /*<<< orphan*/  classname; scalar_t__ inuse; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_9__ {int num_entities; scalar_t__ startTime; int time; TYPE_1__* clients; int /*<<< orphan*/  gentities; } ;
struct TYPE_7__ {int /*<<< orphan*/  ps; } ;

/* Variables and functions */
 int ENTITYNUM_MAX_NORMAL ; 
 int /*<<< orphan*/  G_Error (char*) ; 
 int /*<<< orphan*/  G_InitGentity (TYPE_2__*) ; 
 int /*<<< orphan*/  G_Printf (char*,int,int /*<<< orphan*/ ) ; 
 size_t MAX_CLIENTS ; 
 int MAX_GENTITIES ; 
 TYPE_2__* g_entities ; 
 TYPE_3__ level ; 
 int /*<<< orphan*/  trap_LocateGameData (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 

gentity_t *G_Spawn( void ) {
	int			i, force;
	gentity_t	*e;

	e = NULL;	// shut up warning
	for ( force = 0 ; force < 2 ; force++ ) {
		// if we go through all entities and can't find one to free,
		// override the normal minimum times before use
		e = &g_entities[MAX_CLIENTS];
		for ( i = MAX_CLIENTS ; i<level.num_entities ; i++, e++) {
			if ( e->inuse ) {
				continue;
			}

			// the first couple seconds of server time can involve a lot of
			// freeing and allocating, so relax the replacement policy
			if ( !force && e->freetime > level.startTime + 2000 && level.time - e->freetime < 1000 ) {
				continue;
			}

			// reuse this slot
			G_InitGentity( e );
			return e;
		}
		if ( level.num_entities < ENTITYNUM_MAX_NORMAL ) {
			break;
		}
	}
	if ( level.num_entities == ENTITYNUM_MAX_NORMAL ) {
		for (i = 0; i < MAX_GENTITIES; i++) {
			G_Printf("%4i: %s\n", i, g_entities[i].classname);
		}
		G_Error( "G_Spawn: no free entities" );
	}
	
	// open up a new slot
	level.num_entities++;

	// let the server system know that there are more entities
	trap_LocateGameData( level.gentities, level.num_entities, sizeof( gentity_t ), 
		&level.clients[0].ps, sizeof( level.clients[0] ) );

	G_InitGentity( e );
	return e;
}
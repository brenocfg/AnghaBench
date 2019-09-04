#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_23__ {double fraction; } ;
typedef  TYPE_7__ trace_t ;
struct TYPE_20__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_21__ {TYPE_4__ pos; } ;
struct TYPE_24__ {int count; TYPE_5__ s; TYPE_9__* client; TYPE_1__* item; } ;
typedef  TYPE_8__ gentity_t ;
struct TYPE_22__ {int* powerups; scalar_t__* stats; int /*<<< orphan*/ * persistant; int /*<<< orphan*/  origin; int /*<<< orphan*/  viewangles; } ;
struct TYPE_19__ {scalar_t__ sessionTeam; } ;
struct TYPE_18__ {scalar_t__ connected; } ;
struct TYPE_25__ {TYPE_6__ ps; TYPE_3__ sess; TYPE_2__ pers; } ;
typedef  TYPE_9__ gclient_t ;
struct TYPE_17__ {size_t giTag; int quantity; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {int time; int maxclients; TYPE_9__* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 scalar_t__ CON_DISCONNECTED ; 
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTITYNUM_NONE ; 
 scalar_t__ GT_TEAM ; 
 size_t PERS_PLAYEREVENTS ; 
 int /*<<< orphan*/  PLAYEREVENT_DENIEDREWARD ; 
 int RESPAWN_POWERUP ; 
 size_t STAT_HEALTH ; 
 float VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_12__ g_gametype ; 
 TYPE_11__ level ; 
 int /*<<< orphan*/  trap_Trace (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int Pickup_Powerup( gentity_t *ent, gentity_t *other ) {
	int			quantity;
	int			i;
	gclient_t	*client;

	if ( !other->client->ps.powerups[ent->item->giTag] ) {
		// round timing to seconds to make multiple powerup timers
		// count in sync
		other->client->ps.powerups[ent->item->giTag] = 
			level.time - ( level.time % 1000 );
	}

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	other->client->ps.powerups[ent->item->giTag] += quantity * 1000;

	// give any nearby players a "denied" anti-reward
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		vec3_t		delta;
		float		len;
		vec3_t		forward;
		trace_t		tr;

		client = &level.clients[i];
		if ( client == other->client ) {
			continue;
		}
		if ( client->pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
			continue;
		}

    // if same team in team game, no sound
    // cannot use OnSameTeam as it expects to g_entities, not clients
  	if ( g_gametype.integer >= GT_TEAM && other->client->sess.sessionTeam == client->sess.sessionTeam  ) {
      continue;
    }

		// if too far away, no sound
		VectorSubtract( ent->s.pos.trBase, client->ps.origin, delta );
		len = VectorNormalize( delta );
		if ( len > 192 ) {
			continue;
		}

		// if not facing, no sound
		AngleVectors( client->ps.viewangles, forward, NULL, NULL );
		if ( DotProduct( delta, forward ) < 0.4 ) {
			continue;
		}

		// if not line of sight, no sound
		trap_Trace( &tr, client->ps.origin, NULL, NULL, ent->s.pos.trBase, ENTITYNUM_NONE, CONTENTS_SOLID );
		if ( tr.fraction != 1.0 ) {
			continue;
		}

		// anti-reward
		client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_DENIEDREWARD;
	}
	return RESPAWN_POWERUP;
}
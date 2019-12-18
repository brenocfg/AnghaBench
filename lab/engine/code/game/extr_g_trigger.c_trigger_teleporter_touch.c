#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_13__ {int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; } ;
struct TYPE_14__ {int spawnflags; TYPE_3__ s; TYPE_2__* client; int /*<<< orphan*/  target; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_15__ {scalar_t__ pm_type; } ;
struct TYPE_11__ {scalar_t__ sessionTeam; } ;
struct TYPE_12__ {TYPE_7__ ps; TYPE_1__ sess; } ;

/* Variables and functions */
 TYPE_4__* G_PickTarget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 scalar_t__ PM_DEAD ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  TeleportPlayer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmlab_can_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ dmlab_override_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 

void trigger_teleporter_touch (gentity_t *self, gentity_t *other, trace_t *trace ) {
	gentity_t	*dest;

	if ( !other->client ) {
		return;
	}
	if ( other->client->ps.pm_type == PM_DEAD ) {
		return;
	}
	// Spectators only?
	if ( ( self->spawnflags & 1 ) && 
		other->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		return;
	}

	dest = 	G_PickTarget( self->target );
	if (!dest) {
		G_Printf ("Couldn't find teleporter destination\n");
		return;
	}

	if ( !dmlab_can_trigger( self->id, self->target, &other->client->ps ) ) {
		return;
	}
	if ( dmlab_override_trigger( self->id, self->target, &other->client->ps ) ) {
		return;
	}

	TeleportPlayer( other, dest->s.origin, dest->s.angles );
}
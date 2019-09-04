#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  double* vec3_t ;
typedef  int qboolean ;
struct TYPE_15__ {double* currentOrigin; } ;
struct TYPE_14__ {int /*<<< orphan*/  clientNum; } ;
struct TYPE_18__ {TYPE_3__* client; TYPE_1__ r; TYPE_12__ s; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_16__ {scalar_t__ sessionTeam; } ;
struct TYPE_13__ {double* origin; int pm_time; int /*<<< orphan*/  eFlags; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  velocity; } ;
struct TYPE_17__ {TYPE_2__ sess; TYPE_11__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_11__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_TELEPORT_BIT ; 
 int /*<<< orphan*/  EV_PLAYER_TELEPORT_IN ; 
 int /*<<< orphan*/  EV_PLAYER_TELEPORT_OUT ; 
 int /*<<< orphan*/  G_KillBox (TYPE_4__*) ; 
 TYPE_4__* G_TempEntity (double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMF_TIME_KNOCKBACK ; 
 int /*<<< orphan*/  SetClientViewAngle (TYPE_4__*,double*) ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_4__*) ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_4__*) ; 

void TeleportPlayer( gentity_t *player, vec3_t origin, vec3_t angles ) {
	gentity_t	*tent;
	qboolean noAngles;

	noAngles = (angles[0] > 999999.0);
	// use temp events at source and destination to prevent the effect
	// from getting dropped by a second player event
	if ( player->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		tent = G_TempEntity( player->client->ps.origin, EV_PLAYER_TELEPORT_OUT );
		tent->s.clientNum = player->s.clientNum;

		tent = G_TempEntity( origin, EV_PLAYER_TELEPORT_IN );
		tent->s.clientNum = player->s.clientNum;
	}

	// unlink to make sure it can't possibly interfere with G_KillBox
	trap_UnlinkEntity (player);

	VectorCopy ( origin, player->client->ps.origin );
	player->client->ps.origin[2] += 1;
	if (!noAngles) {
	// spit the player out
	AngleVectors( angles, player->client->ps.velocity, NULL, NULL );
	VectorScale( player->client->ps.velocity, 400, player->client->ps.velocity );
	player->client->ps.pm_time = 160;		// hold time
	player->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
	// set angles
	SetClientViewAngle(player, angles);
	}
	// toggle the teleport bit so the client knows to not lerp
	player->client->ps.eFlags ^= EF_TELEPORT_BIT;
	// kill anything at the destination
	if ( player->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		G_KillBox (player);
	}

	// save results of pmove
	BG_PlayerStateToEntityState( &player->client->ps, &player->s, qtrue );

	// use the precise origin for linking
	VectorCopy( player->client->ps.origin, player->r.currentOrigin );

	if ( player->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		trap_LinkEntity (player);
	}
}
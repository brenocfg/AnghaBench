#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* client; int /*<<< orphan*/  s; int /*<<< orphan*/  health; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_19__ {scalar_t__* powerups; int /*<<< orphan*/  commandTime; int /*<<< orphan*/ * stats; int /*<<< orphan*/  eFlags; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {scalar_t__ time; scalar_t__ intermissiontime; } ;
struct TYPE_14__ {scalar_t__ sessionTeam; } ;
struct TYPE_15__ {int lastCmdTime; TYPE_7__ ps; TYPE_1__ sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BG_PlayerStateToEntityStateExtraPolate (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_CONNECTION ; 
 int /*<<< orphan*/  G_SetClientSound (TYPE_3__*) ; 
 int MAX_POWERUPS ; 
 int /*<<< orphan*/  P_DamageFeedback (TYPE_3__*) ; 
 int /*<<< orphan*/  P_WorldEffects (TYPE_3__*) ; 
 size_t STAT_HEALTH ; 
 int /*<<< orphan*/  SendPendingPredictableEvents (TYPE_7__*) ; 
 int /*<<< orphan*/  SpectatorClientEndFrame (TYPE_3__*) ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_5__ g_smoothClients ; 
 TYPE_4__ level ; 
 int /*<<< orphan*/  qtrue ; 

void ClientEndFrame( gentity_t *ent ) {
	int			i;

	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		SpectatorClientEndFrame( ent );
		return;
	}

	// turn off any expired powerups
	for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
		if ( ent->client->ps.powerups[ i ] < level.time ) {
			ent->client->ps.powerups[ i ] = 0;
		}
	}

#ifdef MISSIONPACK
	// set powerup for player animation
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		ent->client->ps.powerups[PW_GUARD] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		ent->client->ps.powerups[PW_SCOUT] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_DOUBLER ) {
		ent->client->ps.powerups[PW_DOUBLER] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		ent->client->ps.powerups[PW_AMMOREGEN] = level.time;
	}
	if ( ent->client->invulnerabilityTime > level.time ) {
		ent->client->ps.powerups[PW_INVULNERABILITY] = level.time;
	}
#endif

	// save network bandwidth
#if 0
	if ( !g_synchronousClients->integer && ent->client->ps.pm_type == PM_NORMAL ) {
		// FIXME: this must change eventually for non-sync demo recording
		VectorClear( ent->client->ps.viewangles );
	}
#endif

	//
	// If the end of unit layout is displayed, don't give
	// the player any normal movement attributes
	//
	if ( level.intermissiontime ) {
		return;
	}

	// burn from lava, etc
	P_WorldEffects (ent);

	// apply all the damage taken this frame
	P_DamageFeedback (ent);

	// add the EF_CONNECTION flag if we haven't gotten commands recently
	if ( level.time - ent->client->lastCmdTime > 1000 ) {
		ent->client->ps.eFlags |= EF_CONNECTION;
	} else {
		ent->client->ps.eFlags &= ~EF_CONNECTION;
	}

	ent->client->ps.stats[STAT_HEALTH] = ent->health;	// FIXME: get rid of ent->health...

	G_SetClientSound (ent);

	// set the latest infor
	if (g_smoothClients.integer) {
		BG_PlayerStateToEntityStateExtraPolate( &ent->client->ps, &ent->s, ent->client->ps.commandTime, qtrue );
	}
	else {
		BG_PlayerStateToEntityState( &ent->client->ps, &ent->s, qtrue );
	}
	SendPendingPredictableEvents( &ent->client->ps );

	// set the bit for the reachability area the client is currently in
//	i = trap_AAS_PointReachabilityAreaIndex( ent->client->ps.origin );
//	ent->client->areabits[i >> 3] |= 1 << (i & 7);
}
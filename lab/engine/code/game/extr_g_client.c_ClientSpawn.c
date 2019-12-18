#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_30__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  userinfo ;
struct TYPE_37__ {int /*<<< orphan*/  clientNum; int /*<<< orphan*/  groundEntityNum; int /*<<< orphan*/  eFlags; } ;
struct TYPE_35__ {int svFlags; int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  contents; } ;
struct TYPE_38__ {char* classname; int health; TYPE_30__ s; TYPE_4__* client; TYPE_1__ r; int /*<<< orphan*/  flags; scalar_t__ watertype; scalar_t__ waterlevel; int /*<<< orphan*/  die; int /*<<< orphan*/  clipmask; void* inuse; void* takedamage; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_34__ {int eFlags; int ping; int* persistant; int eventSequence; int* stats; int clientNum; int* ammo; int pm_time; int weapon; scalar_t__ commandTime; int /*<<< orphan*/  origin; int /*<<< orphan*/  weaponstate; int /*<<< orphan*/  legsAnim; int /*<<< orphan*/  torsoAnim; int /*<<< orphan*/  pm_flags; } ;
struct TYPE_40__ {scalar_t__ sessionTeam; scalar_t__ spectatorState; } ;
struct TYPE_42__ {scalar_t__ serverTime; } ;
struct TYPE_36__ {int /*<<< orphan*/  state; } ;
struct TYPE_41__ {int maxHealth; TYPE_8__ cmd; TYPE_2__ teamState; void* initialSpawn; scalar_t__ localClient; } ;
struct TYPE_39__ {int accuracy_hits; int accuracy_shots; int lastkilled_client; TYPE_14__ ps; TYPE_5__ sess; TYPE_6__ pers; scalar_t__ latched_buttons; scalar_t__ inactivityTime; scalar_t__ respawnTime; scalar_t__ airOutTime; } ;
typedef  TYPE_4__ gclient_t ;
typedef  TYPE_5__ clientSession_t ;
typedef  TYPE_6__ clientPersistant_t ;
struct TYPE_43__ {scalar_t__ time; int /*<<< orphan*/  intermissiontime; TYPE_4__* clients; } ;
struct TYPE_33__ {scalar_t__ integer; } ;
struct TYPE_32__ {int integer; } ;
struct TYPE_31__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_PlayerStateToEntityState (TYPE_14__*,TYPE_30__*,void*) ; 
 int /*<<< orphan*/  CONTENTS_BODY ; 
 int /*<<< orphan*/  ClientEndFrame (TYPE_3__*) ; 
 int /*<<< orphan*/  ClientThink (int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EF_KAMIKAZE ; 
 int EF_TEAMVOTED ; 
 int EF_TELEPORT_BIT ; 
 int EF_VOTED ; 
 int /*<<< orphan*/  ENTITYNUM_NONE ; 
 int /*<<< orphan*/  EV_PLAYER_TELEPORT_IN ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_TEAM ; 
 int /*<<< orphan*/  G_KillBox (TYPE_3__*) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_UseTargets (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int /*<<< orphan*/  LEGS_IDLE ; 
 int /*<<< orphan*/  MASK_PLAYERSOLID ; 
 int MAX_INFO_STRING ; 
 int MAX_PERSISTANT ; 
 int /*<<< orphan*/  MoveClientToIntermission (TYPE_3__*) ; 
 size_t PERS_SPAWN_COUNT ; 
 size_t PERS_TEAM ; 
 int /*<<< orphan*/  PMF_RESPAWNED ; 
 int /*<<< orphan*/  PMF_TIME_KNOCKBACK ; 
 scalar_t__ SPECTATOR_FOLLOW ; 
 size_t STAT_HEALTH ; 
 size_t STAT_MAX_HEALTH ; 
 size_t STAT_WEAPONS ; 
 int SVF_BOT ; 
 TYPE_3__* SelectCTFSpawnPoint (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* SelectInitialSpawnPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* SelectSpawnPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* SelectSpectatorSpawnPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClientViewAngle (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEAM_ACTIVE ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  TORSO_STAND ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEAPON_READY ; 
 int WP_GAUNTLET ; 
 size_t WP_GRAPPLING_HOOK ; 
 int WP_MACHINEGUN ; 
 int WP_NUM_WEAPONS ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmlab_spawn_inventory (TYPE_14__*,int) ; 
 TYPE_3__* g_entities ; 
 TYPE_12__ g_gametype ; 
 TYPE_11__ g_inactivity ; 
 TYPE_10__ g_unlimitedAmmo ; 
 TYPE_9__ level ; 
 int /*<<< orphan*/  playerMaxs ; 
 int /*<<< orphan*/  playerMins ; 
 int /*<<< orphan*/  player_die ; 
 void* qtrue ; 
 int /*<<< orphan*/  trap_GetUsercmd (int,TYPE_8__*) ; 
 int /*<<< orphan*/  trap_GetUserinfo (int,char*,int) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_3__*) ; 

void ClientSpawn(gentity_t *ent) {
	int		index;
	vec3_t	spawn_origin, spawn_angles;
	gclient_t	*client;
	int		i;
	clientPersistant_t	saved;
	clientSession_t		savedSess;
	int		persistant[MAX_PERSISTANT];
	gentity_t	*spawnPoint;
	gentity_t *tent;
	int		flags;
	int		savedPing;
//	char	*savedAreaBits;
	int		accuracy_hits, accuracy_shots;
	int		eventSequence;
	char	userinfo[MAX_INFO_STRING];

	index = ent - g_entities;
	client = ent->client;

	VectorClear(spawn_origin);

	// find a spawn point
	// do it before setting health back up, so farthest
	// ranging doesn't count this client
	if ( client->sess.sessionTeam == TEAM_SPECTATOR ) {
		spawnPoint = SelectSpectatorSpawnPoint ( 
						spawn_origin, spawn_angles);
	} else if (g_gametype.integer >= GT_CTF ) {
		// all base oriented team games use the CTF spawn points
		spawnPoint = SelectCTFSpawnPoint ( 
						client->sess.sessionTeam, 
						client->pers.teamState.state, 
						spawn_origin, spawn_angles,
						!!(ent->r.svFlags & SVF_BOT));
	}
	else
	{
		// the first spawn should be at a good looking spot
		if ( !client->pers.initialSpawn && client->pers.localClient )
		{
			client->pers.initialSpawn = qtrue;
			spawnPoint = SelectInitialSpawnPoint(spawn_origin, spawn_angles,
							     !!(ent->r.svFlags & SVF_BOT));
		}
		else
		{
			// don't spawn near existing origin if possible
			spawnPoint = SelectSpawnPoint ( 
				client->ps.origin, 
				spawn_origin, spawn_angles, !!(ent->r.svFlags & SVF_BOT));
		}
	}
	client->pers.teamState.state = TEAM_ACTIVE;

	// always clear the kamikaze flag
	ent->s.eFlags &= ~EF_KAMIKAZE;

	// toggle the teleport bit so the client knows to not lerp
	// and never clear the voted flag
	flags = ent->client->ps.eFlags & (EF_TELEPORT_BIT | EF_VOTED | EF_TEAMVOTED);
	flags ^= EF_TELEPORT_BIT;

	// clear everything but the persistant data

	saved = client->pers;
	savedSess = client->sess;
	savedPing = client->ps.ping;
//	savedAreaBits = client->areabits;
	accuracy_hits = client->accuracy_hits;
	accuracy_shots = client->accuracy_shots;
	for ( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
		persistant[i] = client->ps.persistant[i];
	}
	eventSequence = client->ps.eventSequence;

	Com_Memset (client, 0, sizeof(*client));

	client->pers = saved;
	client->sess = savedSess;
	client->ps.ping = savedPing;
//	client->areabits = savedAreaBits;
	client->accuracy_hits = accuracy_hits;
	client->accuracy_shots = accuracy_shots;
	client->lastkilled_client = -1;

	for ( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
		client->ps.persistant[i] = persistant[i];
	}
	client->ps.eventSequence = eventSequence;
	// increment the spawncount so the client will detect the respawn
	client->ps.persistant[PERS_SPAWN_COUNT]++;
	client->ps.persistant[PERS_TEAM] = client->sess.sessionTeam;

	client->airOutTime = level.time + 12000;

	trap_GetUserinfo( index, userinfo, sizeof(userinfo) );
	// set max health
	client->pers.maxHealth = atoi( Info_ValueForKey( userinfo, "handicap" ) );
	if ( client->pers.maxHealth < 1 || client->pers.maxHealth > 100 ) {
		client->pers.maxHealth = 100;
	}
	// clear entity values
	client->ps.stats[STAT_MAX_HEALTH] = client->pers.maxHealth;
	client->ps.eFlags = flags;

	ent->s.groundEntityNum = ENTITYNUM_NONE;
	ent->client = &level.clients[index];
	ent->takedamage = qtrue;
	ent->inuse = qtrue;
	ent->classname = "player";
	ent->r.contents = CONTENTS_BODY;
	ent->clipmask = MASK_PLAYERSOLID;
	ent->die = player_die;
	ent->waterlevel = 0;
	ent->watertype = 0;
	ent->flags = 0;
	
	VectorCopy (playerMins, ent->r.mins);
	VectorCopy (playerMaxs, ent->r.maxs);

	client->ps.clientNum = index;

	client->ps.stats[STAT_WEAPONS] = ( 1 << WP_MACHINEGUN );
	if ( g_unlimitedAmmo.integer != 0 ) {
		client->ps.ammo[WP_MACHINEGUN] = -1;
	} else if ( g_gametype.integer == GT_TEAM ) {
		client->ps.ammo[WP_MACHINEGUN] = 50;
	} else {
		client->ps.ammo[WP_MACHINEGUN] = 100;
	}

	client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_GAUNTLET );
	client->ps.ammo[WP_GAUNTLET] = -1;
	client->ps.ammo[WP_GRAPPLING_HOOK] = -1;

	// health will count down towards max_health
	client->ps.stats[STAT_HEALTH] = client->ps.stats[STAT_MAX_HEALTH] + 25;

	G_SetOrigin( ent, spawn_origin );
	VectorCopy( spawn_origin, client->ps.origin );

	dmlab_spawn_inventory(&client->ps, !!(ent->r.svFlags & SVF_BOT));
	ent->health = client->ps.stats[STAT_HEALTH];

	// the respawned flag will be cleared after the attack and jump keys come up
	client->ps.pm_flags |= PMF_RESPAWNED;

	trap_GetUsercmd( client - level.clients, &ent->client->pers.cmd );
	SetClientViewAngle( ent, spawn_angles );
	// don't allow full run speed for a bit
	client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
	client->ps.pm_time = 100;

	client->respawnTime = level.time;
	client->inactivityTime = level.time + g_inactivity.integer * 1000;
	client->latched_buttons = 0;

	// set default animations
	client->ps.torsoAnim = TORSO_STAND;
	client->ps.legsAnim = LEGS_IDLE;

	if (!level.intermissiontime) {
		if (ent->client->sess.sessionTeam != TEAM_SPECTATOR) {
			G_KillBox(ent);
			// force the base weapon up
			client->ps.weapon = WP_MACHINEGUN;
			client->ps.weaponstate = WEAPON_READY;
			// fire the targets of the spawn point
			G_UseTargets(spawnPoint, ent);
			// select the highest weapon number available, after any spawn given items have fired
			client->ps.weapon = 1;

			for (i = WP_NUM_WEAPONS - 1 ; i > 0 ; i--) {
				if (client->ps.stats[STAT_WEAPONS] & (1 << i)) {
					client->ps.weapon = i;
					break;
				}
			}
			// positively link the client, even if the command times are weird
			VectorCopy(ent->client->ps.origin, ent->r.currentOrigin);

			tent = G_TempEntity(ent->client->ps.origin, EV_PLAYER_TELEPORT_IN);
			tent->s.clientNum = ent->s.clientNum;

			trap_LinkEntity (ent);
		}
	} else {
		// move players to intermission
		MoveClientToIntermission(ent);
	}
	// run a client frame to drop exactly to the floor,
	// initialize animations and other things
	client->ps.commandTime = level.time - 100;
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink( ent-g_entities );
	// run the presend to set anything else, follow spectators wait
	// until all clients have been reconnected after map_restart
	if ( ent->client->sess.spectatorState != SPECTATOR_FOLLOW ) {
		ClientEndFrame( ent );
	}

	// clear entity state values
	BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );
}
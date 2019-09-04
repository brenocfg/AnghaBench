#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  systemInfo ;
struct TYPE_18__ {int number; } ;
struct TYPE_19__ {TYPE_3__ s; } ;
typedef  TYPE_4__ sharedEntity_t ;
typedef  void* qboolean ;
typedef  int /*<<< orphan*/  entityState_t ;
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_17__ {TYPE_1__ remoteAddress; } ;
struct TYPE_20__ {scalar_t__ state; int oldServerTime; int deltaMessage; scalar_t__ lastSnapshotTime; TYPE_4__* gentity; TYPE_2__ netchan; } ;
typedef  TYPE_5__ client_t ;
struct TYPE_24__ {void* modified; } ;
struct TYPE_23__ {int integer; scalar_t__ modified; } ;
struct TYPE_22__ {scalar_t__ integer; } ;
struct TYPE_21__ {int numSnapshotEntities; int time; TYPE_5__* clients; int /*<<< orphan*/  snapFlagServerBit; scalar_t__ nextSnapshotEntities; int /*<<< orphan*/  snapshotEntities; } ;
struct TYPE_15__ {scalar_t__ integer; } ;
struct TYPE_14__ {int time; unsigned int checksumFeed; int serverId; int restartedServerId; int checksumFeedServerId; int /*<<< orphan*/  state; int /*<<< orphan*/ * configstrings; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_MapLoading () ; 
 int /*<<< orphan*/  CL_ShutdownAll (void*) ; 
 int /*<<< orphan*/  CL_StartHunkUsers (void*) ; 
 int /*<<< orphan*/  CM_ClearMap () ; 
 int /*<<< orphan*/  CM_LoadMap (char const*,void*,int*) ; 
 scalar_t__ CS_ACTIVE ; 
 scalar_t__ CS_CONNECTED ; 
 int /*<<< orphan*/  CS_SERVERINFO ; 
 int /*<<< orphan*/  CS_SYSTEMINFO ; 
 int /*<<< orphan*/  CVAR_SERVERINFO ; 
 int /*<<< orphan*/  CVAR_SYSTEMINFO ; 
 unsigned int Com_Milliseconds () ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  CopyString (char*) ; 
 char* Cvar_InfoString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_InfoString_Big (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char const*) ; 
 int /*<<< orphan*/  Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  FS_ClearPakReferences (int /*<<< orphan*/ ) ; 
 char* FS_LoadedPakChecksums () ; 
 char* FS_LoadedPakNames () ; 
 char* FS_ReferencedPakChecksums () ; 
 char* FS_ReferencedPakNames () ; 
 int /*<<< orphan*/  FS_Restart (unsigned int) ; 
 int /*<<< orphan*/  GAME_CLIENT_BEGIN ; 
 int /*<<< orphan*/  GAME_CLIENT_CONNECT ; 
 int /*<<< orphan*/  GAME_RUN_FRAME ; 
 int /*<<< orphan*/  Hunk_Alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hunk_Clear () ; 
 int /*<<< orphan*/  Hunk_SetMark () ; 
 int MAX_CONFIGSTRINGS ; 
 scalar_t__ NA_BOT ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SNAPFLAG_SERVERCOUNT ; 
 int /*<<< orphan*/  SS_GAME ; 
 int /*<<< orphan*/  SS_LOADING ; 
 int /*<<< orphan*/  SV_BotFrame (int) ; 
 int /*<<< orphan*/  SV_ChangeMaxClients () ; 
 int /*<<< orphan*/  SV_ClearServer () ; 
 int /*<<< orphan*/  SV_ClearWorld () ; 
 int /*<<< orphan*/  SV_CreateBaseline () ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_5__*,char*) ; 
 TYPE_4__* SV_GentityNum (int) ; 
 int /*<<< orphan*/  SV_Heartbeat_f () ; 
 int /*<<< orphan*/  SV_InitGameProgs () ; 
 int /*<<< orphan*/  SV_SetConfigstring (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SV_ShutdownGameProgs () ; 
 int /*<<< orphan*/  SV_Startup () ; 
 int /*<<< orphan*/  SV_TouchFile (char*) ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 char* VM_ExplicitArgPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__* com_dedicated ; 
 int com_frameTime ; 
 int /*<<< orphan*/  cvar_modifiedFlags ; 
 int /*<<< orphan*/  gvm ; 
 int /*<<< orphan*/  h_high ; 
 void* qfalse ; 
 void* qtrue ; 
 scalar_t__ rand () ; 
 scalar_t__ strlen (char const*) ; 
 TYPE_10__ sv ; 
 TYPE_9__* sv_gametype ; 
 TYPE_8__* sv_maxclients ; 
 TYPE_7__* sv_pure ; 
 TYPE_6__ svs ; 
 char const* va (char*,...) ; 

void SV_SpawnServer( char *server, qboolean killBots ) {
	int			i;
	int			checksum;
	qboolean	isBot;
	char		systemInfo[16384];
	const char	*p;

	// shut down the existing game if it is running
	SV_ShutdownGameProgs();

	Com_Printf ("------ Server Initialization ------\n");
	Com_Printf ("Server: %s\n",server);

	// if not running a dedicated server CL_MapLoading will connect the client to the server
	// also print some status stuff
	CL_MapLoading();

	// make sure all the client stuff is unloaded
	CL_ShutdownAll(qfalse);

	// clear the whole hunk because we're (re)loading the server
	Hunk_Clear();

	// clear collision map data
	CM_ClearMap();

	// init client structures and svs.numSnapshotEntities 
	if ( !Cvar_VariableValue("sv_running") ) {
		SV_Startup();
	} else {
		// check for maxclients change
		if ( sv_maxclients->modified ) {
			SV_ChangeMaxClients();
		}
	}

	// clear pak references
	FS_ClearPakReferences(0);

	// allocate the snapshot entities on the hunk
	svs.snapshotEntities = Hunk_Alloc( sizeof(entityState_t)*svs.numSnapshotEntities, h_high );
	svs.nextSnapshotEntities = 0;

	// toggle the server bit so clients can detect that a
	// server has changed
	svs.snapFlagServerBit ^= SNAPFLAG_SERVERCOUNT;

	// set nextmap to the same map, but it may be overriden
	// by the game startup or another console command
	Cvar_Set( "nextmap", "map_restart 0");
//	Cvar_Set( "nextmap", va("map %s", server) );

	for (i=0 ; i<sv_maxclients->integer ; i++) {
		// save when the server started for each client already connected
		if (svs.clients[i].state >= CS_CONNECTED) {
			svs.clients[i].oldServerTime = sv.time;
		}
	}

	// wipe the entire per-level structure
	SV_ClearServer();
	for ( i = 0 ; i < MAX_CONFIGSTRINGS ; i++ ) {
		sv.configstrings[i] = CopyString("");
	}

	// make sure we are not paused
	Cvar_Set("cl_paused", "0");

	// get a new checksum feed and restart the file system
	sv.checksumFeed = ( ((unsigned int)rand() << 16) ^ (unsigned int)rand() ) ^ Com_Milliseconds();
	FS_Restart( sv.checksumFeed );

	CM_LoadMap( va("maps/%s.bsp", server), qfalse, &checksum );

	// set serverinfo visible name
	Cvar_Set( "mapname", server );

	Cvar_Set( "sv_mapChecksum", va("%i",checksum) );

	// serverid should be different each time
	sv.serverId = com_frameTime;
	sv.restartedServerId = sv.serverId; // I suppose the init here is just to be safe
	sv.checksumFeedServerId = sv.serverId;
	Cvar_Set( "sv_serverid", va("%i", sv.serverId ) );

	// clear physics interaction links
	SV_ClearWorld ();
	
	// media configstring setting should be done during
	// the loading stage, so connected clients don't have
	// to load during actual gameplay
	sv.state = SS_LOADING;

	// load and spawn all other entities
	SV_InitGameProgs();

	// don't allow a map_restart if game is modified
	sv_gametype->modified = qfalse;

	// run a few frames to allow everything to settle
	for (i = 0;i < 3; i++)
	{
		VM_Call (gvm, GAME_RUN_FRAME, sv.time);
		SV_BotFrame (sv.time);
		sv.time += 100;
		svs.time += 100;
	}

	// create a baseline for more efficient communications
	SV_CreateBaseline ();

	for (i=0 ; i<sv_maxclients->integer ; i++) {
		// send the new gamestate to all connected clients
		if (svs.clients[i].state >= CS_CONNECTED) {
			char	*denied;

			if ( svs.clients[i].netchan.remoteAddress.type == NA_BOT ) {
				if ( killBots ) {
					SV_DropClient( &svs.clients[i], "" );
					continue;
				}
				isBot = qtrue;
			}
			else {
				isBot = qfalse;
			}

			// connect the client again
			denied = VM_ExplicitArgPtr( gvm, VM_Call( gvm, GAME_CLIENT_CONNECT, i, qfalse, isBot ) );	// firstTime = qfalse
			if ( denied ) {
				// this generally shouldn't happen, because the client
				// was connected before the level change
				SV_DropClient( &svs.clients[i], denied );
			} else {
				if( !isBot ) {
					// when we get the next packet from a connected client,
					// the new gamestate will be sent
					svs.clients[i].state = CS_CONNECTED;
				}
				else {
					client_t		*client;
					sharedEntity_t	*ent;

					client = &svs.clients[i];
					client->state = CS_ACTIVE;
					ent = SV_GentityNum( i );
					ent->s.number = i;
					client->gentity = ent;

					client->deltaMessage = -1;
					client->lastSnapshotTime = 0;	// generate a snapshot immediately

					VM_Call( gvm, GAME_CLIENT_BEGIN, i );
				}
			}
		}
	}	

	// run another frame to allow things to look at all the players
	VM_Call (gvm, GAME_RUN_FRAME, sv.time);
	SV_BotFrame (sv.time);
	sv.time += 100;
	svs.time += 100;

	if ( sv_pure->integer ) {
		// the server sends these to the clients so they will only
		// load pk3s also loaded at the server
		p = FS_LoadedPakChecksums();
		Cvar_Set( "sv_paks", p );
		if (strlen(p) == 0) {
			Com_Printf( "WARNING: sv_pure set but no PK3 files loaded\n" );
		}
		p = FS_LoadedPakNames();
		Cvar_Set( "sv_pakNames", p );

		// we need to touch the cgame and ui qvm because they could be in
		// separate pk3 files and the client will need to download the pk3
		// files with the latest cgame and ui qvm to pass the pure check
		SV_TouchFile( "vm/cgame.qvm" );
		SV_TouchFile( "vm/ui.qvm" );
	}
	else {
		Cvar_Set( "sv_paks", "" );
		Cvar_Set( "sv_pakNames", "" );
	}
	// the server sends these to the clients so they can figure
	// out which pk3s should be auto-downloaded
	p = FS_ReferencedPakChecksums();
	Cvar_Set( "sv_referencedPaks", p );
	p = FS_ReferencedPakNames();
	Cvar_Set( "sv_referencedPakNames", p );

	// save systeminfo and serverinfo strings
	Q_strncpyz( systemInfo, Cvar_InfoString_Big( CVAR_SYSTEMINFO ), sizeof( systemInfo ) );
	cvar_modifiedFlags &= ~CVAR_SYSTEMINFO;
	SV_SetConfigstring( CS_SYSTEMINFO, systemInfo );

	SV_SetConfigstring( CS_SERVERINFO, Cvar_InfoString( CVAR_SERVERINFO ) );
	cvar_modifiedFlags &= ~CVAR_SERVERINFO;

	// any media configstring setting now should issue a warning
	// and any configstring changes should be reliably transmitted
	// to all clients
	sv.state = SS_GAME;

	// send a heartbeat now so the master will get up to date info
	SV_Heartbeat_f();

	Hunk_SetMark();

#ifndef DEDICATED
	if ( com_dedicated->integer ) {
		// restart renderer in order to show console for dedicated servers
		// launched through the regular binary
		CL_StartHunkUsers( qtrue );
	}
#endif

	Com_Printf ("-----------------------------------\n");
}
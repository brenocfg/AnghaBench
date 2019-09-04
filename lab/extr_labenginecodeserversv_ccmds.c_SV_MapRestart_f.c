#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
typedef  int /*<<< orphan*/  mapname ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_13__ {TYPE_1__ remoteAddress; } ;
struct TYPE_14__ {scalar_t__ state; int oldServerTime; int /*<<< orphan*/  lastUsercmd; TYPE_2__ netchan; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_19__ {int /*<<< orphan*/  integer; } ;
struct TYPE_18__ {scalar_t__ serverId; int restartTime; int time; void* restarting; int /*<<< orphan*/  state; } ;
struct TYPE_17__ {scalar_t__ modified; } ;
struct TYPE_16__ {int integer; scalar_t__ modified; } ;
struct TYPE_15__ {int time; TYPE_3__* clients; int /*<<< orphan*/  snapFlagServerBit; } ;

/* Variables and functions */
 scalar_t__ CS_ACTIVE ; 
 scalar_t__ CS_CONNECTED ; 
 scalar_t__ CS_PRIMED ; 
 int /*<<< orphan*/  CS_WARMUP ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  GAME_CLIENT_CONNECT ; 
 int /*<<< orphan*/  GAME_RUN_FRAME ; 
 int MAX_QPATH ; 
 scalar_t__ NA_BOT ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SNAPFLAG_SERVERCOUNT ; 
 int /*<<< orphan*/  SS_GAME ; 
 int /*<<< orphan*/  SS_LOADING ; 
 int /*<<< orphan*/  SV_AddServerCommand (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  SV_ClientEnterWorld (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  SV_RestartGameProgs () ; 
 int /*<<< orphan*/  SV_SetConfigstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_SpawnServer (char*,void*) ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 char* VM_ExplicitArgPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ com_frameTime ; 
 TYPE_8__* com_sv_running ; 
 int /*<<< orphan*/  gvm ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_7__ sv ; 
 TYPE_6__* sv_gametype ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 
 int /*<<< orphan*/  va (char*,int) ; 

__attribute__((used)) static void SV_MapRestart_f( void ) {
	int			i;
	client_t	*client;
	char		*denied;
	qboolean	isBot;
	int			delay;

	// make sure we aren't restarting twice in the same frame
	if ( com_frameTime == sv.serverId ) {
		return;
	}

	// make sure server is running
	if ( !com_sv_running->integer ) {
		Com_Printf( "Server is not running.\n" );
		return;
	}

	if ( sv.restartTime ) {
		return;
	}

	if (Cmd_Argc() > 1 ) {
		delay = atoi( Cmd_Argv(1) );
	}
	else {
		delay = 5;
	}
	if( delay && !Cvar_VariableValue("g_doWarmup") ) {
		sv.restartTime = sv.time + delay * 1000;
		SV_SetConfigstring( CS_WARMUP, va("%i", sv.restartTime) );
		return;
	}

	// check for changes in variables that can't just be restarted
	// check for maxclients change
	if ( sv_maxclients->modified || sv_gametype->modified ) {
		char	mapname[MAX_QPATH];

		Com_Printf( "variable change -- restarting.\n" );
		// restart the map the slow way
		Q_strncpyz( mapname, Cvar_VariableString( "mapname" ), sizeof( mapname ) );

		SV_SpawnServer( mapname, qfalse );
		return;
	}

	// toggle the server bit so clients can detect that a
	// map_restart has happened
	svs.snapFlagServerBit ^= SNAPFLAG_SERVERCOUNT;

	// generate a new serverid	
	// TTimo - don't update restartedserverId there, otherwise we won't deal correctly with multiple map_restart
	sv.serverId = com_frameTime;
	Cvar_Set( "sv_serverid", va("%i", sv.serverId ) );

	// if a map_restart occurs while a client is changing maps, we need
	// to give them the correct time so that when they finish loading
	// they don't violate the backwards time check in cl_cgame.c
	for (i=0 ; i<sv_maxclients->integer ; i++) {
		if (svs.clients[i].state == CS_PRIMED) {
			svs.clients[i].oldServerTime = sv.restartTime;
		}
	}

	// reset all the vm data in place without changing memory allocation
	// note that we do NOT set sv.state = SS_LOADING, so configstrings that
	// had been changed from their default values will generate broadcast updates
	sv.state = SS_LOADING;
	sv.restarting = qtrue;

	SV_RestartGameProgs();

	// run a few frames to allow everything to settle
	for (i = 0; i < 3; i++)
	{
		VM_Call (gvm, GAME_RUN_FRAME, sv.time);
		sv.time += 100;
		svs.time += 100;
	}

	sv.state = SS_GAME;
	sv.restarting = qfalse;

	// connect and begin all the clients
	for (i=0 ; i<sv_maxclients->integer ; i++) {
		client = &svs.clients[i];

		// send the new gamestate to all connected clients
		if ( client->state < CS_CONNECTED) {
			continue;
		}

		if ( client->netchan.remoteAddress.type == NA_BOT ) {
			isBot = qtrue;
		} else {
			isBot = qfalse;
		}

		// add the map_restart command
		SV_AddServerCommand( client, "map_restart\n" );

		// connect the client again, without the firstTime flag
		denied = VM_ExplicitArgPtr( gvm, VM_Call( gvm, GAME_CLIENT_CONNECT, i, qfalse, isBot ) );
		if ( denied ) {
			// this generally shouldn't happen, because the client
			// was connected before the level change
			SV_DropClient( client, denied );
			Com_Printf( "SV_MapRestart_f(%d): dropped client %i - denied!\n", delay, i );
			continue;
		}

		if(client->state == CS_ACTIVE)
			SV_ClientEnterWorld(client, &client->lastUsercmd);
		else
		{
			// If we don't reset client->lastUsercmd and are restarting during map load,
			// the client will hang because we'll use the last Usercmd from the previous map,
			// which is wrong obviously.
			SV_ClientEnterWorld(client, NULL);
		}
	}	

	// run another frame to allow things to look at all the players
	VM_Call (gvm, GAME_RUN_FRAME, sv.time);
	sv.time += 100;
	svs.time += 100;
}
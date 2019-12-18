#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {scalar_t__ integer; } ;
struct TYPE_14__ {int /*<<< orphan*/  integer; } ;
struct TYPE_13__ {int value; } ;
struct TYPE_12__ {int timeResidual; scalar_t__ time; scalar_t__ restartTime; } ;
struct TYPE_11__ {int integer; } ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {int time; int nextSnapshotEntities; int numSnapshotEntities; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SERVERINFO ; 
 int /*<<< orphan*/  CS_SYSTEMINFO ; 
 int CVAR_SERVERINFO ; 
 int CVAR_SYSTEMINFO ; 
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 int /*<<< orphan*/  Cvar_InfoString (int) ; 
 int /*<<< orphan*/  Cvar_InfoString_Big (int) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 float Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  GAME_RUN_FRAME ; 
 int /*<<< orphan*/  HEARTBEAT_FOR_MASTER ; 
 int /*<<< orphan*/  SV_BotFrame (scalar_t__) ; 
 int /*<<< orphan*/  SV_CalcPings () ; 
 scalar_t__ SV_CheckPaused () ; 
 int /*<<< orphan*/  SV_CheckTimeouts () ; 
 int /*<<< orphan*/  SV_MasterHeartbeat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_SendClientMessages () ; 
 int /*<<< orphan*/  SV_SetConfigstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_Shutdown (char*) ; 
 int Sys_Milliseconds () ; 
 int /*<<< orphan*/  Sys_Sleep (int) ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_8__* com_dedicated ; 
 TYPE_7__* com_speeds ; 
 TYPE_6__* com_sv_running ; 
 TYPE_5__* com_timescale ; 
 int cvar_modifiedFlags ; 
 int /*<<< orphan*/  gvm ; 
 TYPE_4__ sv ; 
 TYPE_3__* sv_fps ; 
 TYPE_2__* sv_killserver ; 
 TYPE_1__ svs ; 
 int time_game ; 
 char* va (char*,float) ; 

void SV_Frame( int msec ) {
	int		frameMsec;
	int		startTime;

	// the menu kills the server with this cvar
	if ( sv_killserver->integer ) {
		SV_Shutdown ("Server was killed");
		Cvar_Set( "sv_killserver", "0" );
		return;
	}

	if (!com_sv_running->integer)
	{
		// Running as a server, but no map loaded
#ifdef DEDICATED
		// Block until something interesting happens
		Sys_Sleep(-1);
#endif

		return;
	}

	// allow pause if only the local client is connected
	if ( SV_CheckPaused() ) {
		return;
	}

	// if it isn't time for the next frame, do nothing
	if ( sv_fps->integer < 1 ) {
		Cvar_Set( "sv_fps", "10" );
	}

	frameMsec = 1000 / sv_fps->integer * com_timescale->value;
	// don't let it scale below 1ms
	if(frameMsec < 1)
	{
		Cvar_Set("timescale", va("%f", sv_fps->integer / 1000.0f));
		frameMsec = 1;
	}

	sv.timeResidual += msec;

	if (!com_dedicated->integer) SV_BotFrame (sv.time + sv.timeResidual);

	// if time is about to hit the 32nd bit, kick all clients
	// and clear sv.time, rather
	// than checking for negative time wraparound everywhere.
	// 2giga-milliseconds = 23 days, so it won't be too often
	if ( svs.time > 0x70000000 ) {
		SV_Shutdown( "Restarting server due to time wrapping" );
		Cbuf_AddText( va( "map %s\n", Cvar_VariableString( "mapname" ) ) );
		return;
	}
	// this can happen considerably earlier when lots of clients play and the map doesn't change
	if ( svs.nextSnapshotEntities >= 0x7FFFFFFE - svs.numSnapshotEntities ) {
		SV_Shutdown( "Restarting server due to numSnapshotEntities wrapping" );
		Cbuf_AddText( va( "map %s\n", Cvar_VariableString( "mapname" ) ) );
		return;
	}

	if( sv.restartTime && sv.time >= sv.restartTime ) {
		sv.restartTime = 0;
		Cbuf_AddText( "map_restart 0\n" );
		return;
	}

	// update infostrings if anything has been changed
	if ( cvar_modifiedFlags & CVAR_SERVERINFO ) {
		SV_SetConfigstring( CS_SERVERINFO, Cvar_InfoString( CVAR_SERVERINFO ) );
		cvar_modifiedFlags &= ~CVAR_SERVERINFO;
	}
	if ( cvar_modifiedFlags & CVAR_SYSTEMINFO ) {
		SV_SetConfigstring( CS_SYSTEMINFO, Cvar_InfoString_Big( CVAR_SYSTEMINFO ) );
		cvar_modifiedFlags &= ~CVAR_SYSTEMINFO;
	}

	if ( com_speeds->integer ) {
		startTime = Sys_Milliseconds ();
	} else {
		startTime = 0;	// quite a compiler warning
	}

	// update ping based on the all received frames
	SV_CalcPings();

	if (com_dedicated->integer) SV_BotFrame (sv.time);

	// run the game simulation in chunks
	while ( sv.timeResidual >= frameMsec ) {
		sv.timeResidual -= frameMsec;
		svs.time += frameMsec;
		sv.time += frameMsec;

		// let everything in the world think and move
		VM_Call (gvm, GAME_RUN_FRAME, sv.time);
	}

	if ( com_speeds->integer ) {
		time_game = Sys_Milliseconds () - startTime;
	}

	// check timeouts
	SV_CheckTimeouts();

	// send messages back to the clients
	SV_SendClientMessages();

	// send a heartbeat to the master if needed
	SV_MasterHeartbeat(HEARTBEAT_FOR_MASTER);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_6__ {scalar_t__ integer; } ;
struct TYPE_5__ {scalar_t__ modificationCount; int integer; } ;
struct TYPE_4__ {int numPlayingClients; int warmupTime; scalar_t__ warmupModificationCount; int time; void* restarted; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddTournamentPlayer () ; 
 int /*<<< orphan*/  CS_WARMUP ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 scalar_t__ GT_TEAM ; 
 scalar_t__ GT_TOURNAMENT ; 
 int /*<<< orphan*/  G_LogPrintf (char*) ; 
 size_t TEAM_BLUE ; 
 int TEAM_NUM_TEAMS ; 
 size_t TEAM_RED ; 
 int TeamCount (int,size_t) ; 
 TYPE_3__ g_gametype ; 
 TYPE_2__ g_warmup ; 
 TYPE_1__ level ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_SetConfigstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int) ; 

void CheckTournament( void ) {
	// check because we run 3 game frames before calling Connect and/or ClientBegin
	// for clients on a map_restart
	if ( level.numPlayingClients == 0 ) {
		return;
	}

	if ( g_gametype.integer == GT_TOURNAMENT ) {

		// pull in a spectator if needed
		if ( level.numPlayingClients < 2 ) {
			AddTournamentPlayer();
		}

		// if we don't have two players, go back to "waiting for players"
		if ( level.numPlayingClients != 2 ) {
			if ( level.warmupTime != -1 ) {
				level.warmupTime = -1;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
				G_LogPrintf( "Warmup:\n" );
			}
			return;
		}

		if ( level.warmupTime == 0 ) {
			return;
		}

		// if the warmup is changed at the console, restart it
		if ( g_warmup.modificationCount != level.warmupModificationCount ) {
			level.warmupModificationCount = g_warmup.modificationCount;
			level.warmupTime = -1;
		}

		// if all players have arrived, start the countdown
		if ( level.warmupTime < 0 ) {
			if ( level.numPlayingClients == 2 ) {
				// fudge by -1 to account for extra delays
				if ( g_warmup.integer > 1 ) {
					level.warmupTime = level.time + ( g_warmup.integer - 1 ) * 1000;
				} else {
					level.warmupTime = 0;
				}

				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
			}
			return;
		}

		// if the warmup time has counted down, restart
		if ( level.time > level.warmupTime ) {
			level.warmupTime += 10000;
			trap_Cvar_Set( "g_restarted", "1" );
			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			level.restarted = qtrue;
			return;
		}
	} else if ( g_gametype.integer != GT_SINGLE_PLAYER && level.warmupTime != 0 ) {
		int		counts[TEAM_NUM_TEAMS];
		qboolean	notEnough = qfalse;

		if ( g_gametype.integer >= GT_TEAM ) {
			counts[TEAM_BLUE] = TeamCount( -1, TEAM_BLUE );
			counts[TEAM_RED] = TeamCount( -1, TEAM_RED );

			if (counts[TEAM_RED] < 1 || counts[TEAM_BLUE] < 1) {
				notEnough = qtrue;
			}
		} else if ( level.numPlayingClients < 2 ) {
			notEnough = qtrue;
		}

		if ( notEnough ) {
			if ( level.warmupTime != -1 ) {
				level.warmupTime = -1;
				trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
				G_LogPrintf( "Warmup:\n" );
			}
			return; // still waiting for team members
		}

		if ( level.warmupTime == 0 ) {
			return;
		}

		// if the warmup is changed at the console, restart it
		if ( g_warmup.modificationCount != level.warmupModificationCount ) {
			level.warmupModificationCount = g_warmup.modificationCount;
			level.warmupTime = -1;
		}

		// if all players have arrived, start the countdown
		if ( level.warmupTime < 0 ) {
			// fudge by -1 to account for extra delays
			if ( g_warmup.integer > 1 ) {
				level.warmupTime = level.time + ( g_warmup.integer - 1 ) * 1000;
			} else {
				level.warmupTime = 0;
			}

			trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
			return;
		}

		// if the warmup time has counted down, restart
		if ( level.time > level.warmupTime ) {
			level.warmupTime += 10000;
			trap_Cvar_Set( "g_restarted", "1" );
			trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
			level.restarted = qtrue;
			return;
		}
	}
}
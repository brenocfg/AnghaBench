#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_9__ {size_t ownerNum; } ;
struct TYPE_8__ {size_t number; } ;
struct TYPE_13__ {char* classname; TYPE_2__ r; TYPE_1__ s; } ;
struct TYPE_12__ {char* string; } ;
struct TYPE_11__ {scalar_t__ integer; } ;
struct TYPE_10__ {int startTime; int warmupTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_GAME_VERSION ; 
 int /*<<< orphan*/  CS_LEVEL_START_TIME ; 
 int /*<<< orphan*/  CS_MESSAGE ; 
 int /*<<< orphan*/  CS_MOTD ; 
 int /*<<< orphan*/  CS_MUSIC ; 
 int /*<<< orphan*/  CS_WARMUP ; 
 size_t ENTITYNUM_NONE ; 
 size_t ENTITYNUM_WORLD ; 
 char* GAME_VERSION ; 
 int /*<<< orphan*/  G_Error (char*) ; 
 int /*<<< orphan*/  G_LogPrintf (char*) ; 
 int /*<<< orphan*/  G_SpawnString (char*,char*,char**) ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 TYPE_7__ g_doWarmup ; 
 TYPE_6__* g_entities ; 
 TYPE_5__ g_motd ; 
 TYPE_4__ g_restarted ; 
 TYPE_3__ level ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_SetConfigstring (int /*<<< orphan*/ ,char*) ; 
 char* va (char*,int) ; 

void SP_worldspawn( void ) {
	char	*s;

	G_SpawnString( "classname", "", &s );
	if ( Q_stricmp( s, "worldspawn" ) ) {
		G_Error( "SP_worldspawn: The first entity isn't 'worldspawn'" );
	}

	// make some data visible to connecting client
	trap_SetConfigstring( CS_GAME_VERSION, GAME_VERSION );

	trap_SetConfigstring( CS_LEVEL_START_TIME, va("%i", level.startTime ) );

	G_SpawnString( "music", "", &s );
	trap_SetConfigstring( CS_MUSIC, s );

	G_SpawnString( "message", "", &s );
	trap_SetConfigstring( CS_MESSAGE, s );				// map specific message

	trap_SetConfigstring( CS_MOTD, g_motd.string );		// message of the day

	G_SpawnString( "gravity", "800", &s );
	trap_Cvar_Set( "g_gravity", s );

	G_SpawnString( "enableDust", "0", &s );
	trap_Cvar_Set( "g_enableDust", s );

	G_SpawnString( "enableBreath", "0", &s );
	trap_Cvar_Set( "g_enableBreath", s );

	g_entities[ENTITYNUM_WORLD].s.number = ENTITYNUM_WORLD;
	g_entities[ENTITYNUM_WORLD].r.ownerNum = ENTITYNUM_NONE;
	g_entities[ENTITYNUM_WORLD].classname = "worldspawn";

	g_entities[ENTITYNUM_NONE].s.number = ENTITYNUM_NONE;
	g_entities[ENTITYNUM_NONE].r.ownerNum = ENTITYNUM_NONE;
	g_entities[ENTITYNUM_NONE].classname = "nothing";

	// see if we want a warmup time
	trap_SetConfigstring( CS_WARMUP, "" );
	if ( g_restarted.integer ) {
		trap_Cvar_Set( "g_restarted", "0" );
		level.warmupTime = 0;
	} else if ( g_doWarmup.integer ) { // Turn it on
		level.warmupTime = -1;
		trap_SetConfigstring( CS_WARMUP, va("%i", level.warmupTime) );
		G_LogPrintf( "Warmup:\n" );
	}

}
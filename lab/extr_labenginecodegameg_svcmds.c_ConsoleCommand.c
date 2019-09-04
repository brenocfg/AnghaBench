#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConcatArgs (int) ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 int MAX_TOKEN_CHARS ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Svcmd_AbortPodium_f () ; 
 int /*<<< orphan*/  Svcmd_AddBot_f () ; 
 int /*<<< orphan*/  Svcmd_AddIP_f () ; 
 int /*<<< orphan*/  Svcmd_BotList_f () ; 
 int /*<<< orphan*/  Svcmd_EntityList_f () ; 
 int /*<<< orphan*/  Svcmd_ForceTeam_f () ; 
 int /*<<< orphan*/  Svcmd_GameMem_f () ; 
 int /*<<< orphan*/  Svcmd_RemoveIP_f () ; 
 TYPE_1__ g_dedicated ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Argv (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

qboolean	ConsoleCommand( void ) {
	char	cmd[MAX_TOKEN_CHARS];

	trap_Argv( 0, cmd, sizeof( cmd ) );

	if ( Q_stricmp (cmd, "entitylist") == 0 ) {
		Svcmd_EntityList_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "forceteam") == 0 ) {
		Svcmd_ForceTeam_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "game_memory") == 0) {
		Svcmd_GameMem_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "addbot") == 0) {
		Svcmd_AddBot_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "botlist") == 0) {
		Svcmd_BotList_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "abort_podium") == 0) {
		Svcmd_AbortPodium_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "addip") == 0) {
		Svcmd_AddIP_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "removeip") == 0) {
		Svcmd_RemoveIP_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "listip") == 0) {
		trap_SendConsoleCommand( EXEC_NOW, "g_banIPs\n" );
		return qtrue;
	}

	if (g_dedicated.integer) {
		if (Q_stricmp (cmd, "say") == 0) {
			trap_SendServerCommand( -1, va("print \"server: %s\n\"", ConcatArgs(1) ) );
			return qtrue;
		}
		// everything else will also be printed as a say command
		trap_SendServerCommand( -1, va("print \"server: %s\n\"", ConcatArgs(0) ) );
		return qtrue;
	}

	return qfalse;
}
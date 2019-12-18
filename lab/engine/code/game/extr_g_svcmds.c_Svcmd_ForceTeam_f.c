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
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  gclient_t ;
struct TYPE_2__ {int /*<<< orphan*/ * clients; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ClientForString (char*) ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 int MAX_TOKEN_CHARS ; 
 int /*<<< orphan*/  SetTeam (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * g_entities ; 
 TYPE_1__ level ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 

void	Svcmd_ForceTeam_f( void ) {
	gclient_t	*cl;
	char		str[MAX_TOKEN_CHARS];

	if ( trap_Argc() < 3 ) {
		G_Printf("Usage: forceteam <player> <team>\n");
		return;
	}

	// find the player
	trap_Argv( 1, str, sizeof( str ) );
	cl = ClientForString( str );
	if ( !cl ) {
		return;
	}

	// set the team
	trap_Argv( 2, str, sizeof( str ) );
	SetTeam( &g_entities[cl - level.clients], str );
}
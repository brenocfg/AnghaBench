#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  team_t ;
typedef  int /*<<< orphan*/  spectatorState_t ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  teamLeader; int /*<<< orphan*/  spectatorState; int /*<<< orphan*/  sessionTeam; int /*<<< orphan*/  losses; int /*<<< orphan*/  wins; int /*<<< orphan*/  spectatorClient; int /*<<< orphan*/  spectatorNum; } ;
struct TYPE_6__ {TYPE_1__ sess; } ;
typedef  TYPE_2__ gclient_t ;
struct TYPE_7__ {TYPE_2__* clients; } ;

/* Variables and functions */
 int MAX_STRING_CHARS ; 
 TYPE_3__ level ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char const*,char*,int) ; 
 char* va (char*,int) ; 

void G_ReadSessionData( gclient_t *client ) {
	char	s[MAX_STRING_CHARS];
	const char	*var;
	int teamLeader;
	int spectatorState;
	int sessionTeam;

	var = va( "session%i", (int)(client - level.clients) );
	trap_Cvar_VariableStringBuffer( var, s, sizeof(s) );

	sscanf( s, "%i %i %i %i %i %i %i",
		&sessionTeam,
		&client->sess.spectatorNum,
		&spectatorState,
		&client->sess.spectatorClient,
		&client->sess.wins,
		&client->sess.losses,
		&teamLeader
		);

	client->sess.sessionTeam = (team_t)sessionTeam;
	client->sess.spectatorState = (spectatorState_t)spectatorState;
	client->sess.teamLeader = (qboolean)teamLeader;
}
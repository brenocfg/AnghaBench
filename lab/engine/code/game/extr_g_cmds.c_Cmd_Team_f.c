#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_11__ {TYPE_2__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {scalar_t__ time; } ;
struct TYPE_9__ {int sessionTeam; int /*<<< orphan*/  losses; } ;
struct TYPE_10__ {scalar_t__ switchTeamTime; TYPE_1__ sess; } ;

/* Variables and functions */
 scalar_t__ GT_TOURNAMENT ; 
 int MAX_TOKEN_CHARS ; 
 int /*<<< orphan*/  SetTeam (TYPE_3__*,char*) ; 
#define  TEAM_BLUE 131 
#define  TEAM_FREE 130 
#define  TEAM_RED 129 
#define  TEAM_SPECTATOR 128 
 int g_entities ; 
 TYPE_6__ g_gametype ; 
 TYPE_5__ level ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 
 int /*<<< orphan*/  trap_SendServerCommand (TYPE_3__*,char*) ; 

void Cmd_Team_f( gentity_t *ent ) {
	int			oldTeam;
	char		s[MAX_TOKEN_CHARS];

	if ( trap_Argc() != 2 ) {
		oldTeam = ent->client->sess.sessionTeam;
		switch ( oldTeam ) {
		case TEAM_BLUE:
			trap_SendServerCommand( ent-g_entities, "print \"Blue team\n\"" );
			break;
		case TEAM_RED:
			trap_SendServerCommand( ent-g_entities, "print \"Red team\n\"" );
			break;
		case TEAM_FREE:
			trap_SendServerCommand( ent-g_entities, "print \"Free team\n\"" );
			break;
		case TEAM_SPECTATOR:
			trap_SendServerCommand( ent-g_entities, "print \"Spectator team\n\"" );
			break;
		}
		return;
	}

	if ( ent->client->switchTeamTime > level.time ) {
		trap_SendServerCommand( ent-g_entities, "print \"May not switch teams more than once per 5 seconds.\n\"" );
		return;
	}

	// if they are playing a tournement game, count as a loss
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& ent->client->sess.sessionTeam == TEAM_FREE ) {
		ent->client->sess.losses++;
	}

	trap_Argv( 1, s, sizeof( s ) );

	SetTeam( ent, s );

	ent->client->switchTeamTime = level.time + 5000;
}
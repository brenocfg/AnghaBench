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
struct TYPE_12__ {scalar_t__ localClient; } ;
struct TYPE_14__ {void* spectatorState; void* sessionTeam; } ;
struct TYPE_13__ {TYPE_1__ pers; TYPE_3__ sess; } ;
typedef  TYPE_2__ gclient_t ;
typedef  TYPE_3__ clientSession_t ;
struct TYPE_19__ {int integer; } ;
struct TYPE_18__ {char* string; } ;
struct TYPE_17__ {int integer; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {int numNonSpectatorClients; TYPE_2__* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddTournamentQueue (TYPE_2__*) ; 
#define  GT_FFA 130 
#define  GT_SINGLE_PLAYER 129 
 int GT_TEAM ; 
#define  GT_TOURNAMENT 128 
 int /*<<< orphan*/  G_WriteClientSessionData (TYPE_2__*) ; 
 char* Info_ValueForKey (char*,char*) ; 
 void* SPECTATOR_FREE ; 
 int /*<<< orphan*/  SetTeam (int /*<<< orphan*/ *,char const*) ; 
 void* TEAM_FREE ; 
 void* TEAM_SPECTATOR ; 
 char dmlab_select_team (int,char*) ; 
 int /*<<< orphan*/ * g_entities ; 
 TYPE_8__ g_gametype ; 
 TYPE_7__ g_localTeamPref ; 
 TYPE_6__ g_maxGameClients ; 
 TYPE_5__ g_teamAutoJoin ; 
 TYPE_4__ level ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 

void G_InitSessionData( gclient_t *client, char *userinfo ) {
	clientSession_t	*sess;
	const char		*value;
	char	team[2] = {'\0', '\0'};
	sess = &client->sess;

	// check for team preference, mainly for bots
	value = Info_ValueForKey( userinfo, "teampref" );

	// check for human's team preference set by start server menu
	if ( !value[0] && g_localTeamPref.string[0] && client->pers.localClient ) {
		value = g_localTeamPref.string;

		// clear team so it's only used once
		trap_Cvar_Set( "g_localTeamPref", "" );
	}

	team[0] = dmlab_select_team( client - level.clients, Info_ValueForKey (userinfo, "name") );
	if ( team[0] ){
		value = team;
	}

	// initial team determination
	if ( g_gametype.integer >= GT_TEAM ) {
		// always spawn as spectator in team games
		sess->sessionTeam = TEAM_SPECTATOR;
		sess->spectatorState = SPECTATOR_FREE;

		if ( value[0] || g_teamAutoJoin.integer ) {
			SetTeam( &g_entities[client - level.clients], value );
		}
	} else {
		if ( value[0] == 's' ) {
			// a willing spectator, not a waiting-in-line
			sess->sessionTeam = TEAM_SPECTATOR;
		} else {
			switch ( g_gametype.integer ) {
			default:
			case GT_FFA:
			case GT_SINGLE_PLAYER:
				if ( g_maxGameClients.integer > 0 && 
					level.numNonSpectatorClients >= g_maxGameClients.integer ) {
					sess->sessionTeam = TEAM_SPECTATOR;
				} else {
					sess->sessionTeam = TEAM_FREE;
				}
				break;
			case GT_TOURNAMENT:
				// if the game is full, go into a waiting mode
				if ( level.numNonSpectatorClients >= 2 ) {
					sess->sessionTeam = TEAM_SPECTATOR;
				} else {
					sess->sessionTeam = TEAM_FREE;
				}
				break;
			}
		}

		sess->spectatorState = SPECTATOR_FREE;
	}

	AddTournamentQueue(client);

	G_WriteClientSessionData( client );
}
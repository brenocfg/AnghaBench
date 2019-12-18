#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int grank_status_t ;
struct TYPE_20__ {int svFlags; } ;
struct TYPE_18__ {int /*<<< orphan*/  clientNum; } ;
struct TYPE_24__ {TYPE_6__* client; TYPE_3__ r; int /*<<< orphan*/  inuse; TYPE_1__ s; } ;
typedef  TYPE_7__ gentity_t ;
struct TYPE_26__ {int integer; } ;
struct TYPE_25__ {int maxclients; scalar_t__ intermissiontime; int time; } ;
struct TYPE_22__ {int* persistant; } ;
struct TYPE_21__ {int netname; int enterTime; } ;
struct TYPE_19__ {int /*<<< orphan*/  sessionTeam; int /*<<< orphan*/  spectatorState; } ;
struct TYPE_23__ {int client_status; TYPE_5__ ps; TYPE_4__ pers; TYPE_2__ sess; } ;
struct TYPE_17__ {int integer; } ;
struct TYPE_16__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientSpawn (TYPE_7__*) ; 
 int /*<<< orphan*/  DeathmatchScoreboardMessage (TYPE_7__*) ; 
 int /*<<< orphan*/  EXEC_INSERT ; 
 int /*<<< orphan*/  GR_GAMEKEY ; 
 int /*<<< orphan*/  GT_TEAM ; 
 size_t PERS_MATCH_TIME ; 
 int /*<<< orphan*/  QGR_KEY_PLAYED_WITH ; 
#define  QGR_STATUS_ACTIVE 136 
#define  QGR_STATUS_BAD_PASSWORD 135 
#define  QGR_STATUS_ERROR 134 
#define  QGR_STATUS_INVALIDUSER 133 
#define  QGR_STATUS_NEW 132 
#define  QGR_STATUS_NO_MEMBERSHIP 131 
#define  QGR_STATUS_NO_USER 130 
#define  QGR_STATUS_SPECTATOR 129 
#define  QGR_STATUS_TIMEOUT 128 
 int /*<<< orphan*/  SPECTATOR_FREE ; 
 int SVF_BOT ; 
 int /*<<< orphan*/  SetTeam (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  TEAM_SPECTATOR ; 
 TYPE_7__* g_entities ; 
 TYPE_11__ g_fraglimit ; 
 TYPE_10__ g_gametype ; 
 TYPE_9__ g_timelimit ; 
 TYPE_8__ level ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 scalar_t__ trap_RankActive () ; 
 int /*<<< orphan*/  trap_RankBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_RankCheckInit () ; 
 int /*<<< orphan*/  trap_RankPoll () ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_RankUserReset (int /*<<< orphan*/ ) ; 
 int const trap_RankUserStatus (int) ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,char*) ; 
 char* va (char*,int) ; 

void G_RankRunFrame()
{
	gentity_t*		ent;
	gentity_t*		ent2;
	grank_status_t	old_status;
	grank_status_t	status;
	int				time;
	int				i;
	int				j;

	if( !trap_RankCheckInit() ) 
	{
		trap_RankBegin( GR_GAMEKEY );
	}

	trap_RankPoll();
	
	if( trap_RankActive() )
	{
		for( i = 0; i < level.maxclients; i++ )
		{
			ent = &(g_entities[i]);
			if ( !ent->inuse )
				continue;
			if ( ent->client == NULL )
				continue;
			if ( ent->r.svFlags & SVF_BOT)
			{
				// no bots in ranked games
				trap_SendConsoleCommand( EXEC_INSERT, va("kick %s\n", 
					ent->client->pers.netname) );
				continue;
			}

			old_status = ent->client->client_status;
			status = trap_RankUserStatus( i );
			
			if( ent->client->client_status != status )
			{
				// inform client of current status
				// not needed for client side log in
				trap_SendServerCommand( i, va("rank_status %i\n",status) );
				if ( i == 0 )
				{
					int j = 0;
				}
				ent->client->client_status = status;
			}
			
			switch( status )
			{
			case QGR_STATUS_NEW:
			case QGR_STATUS_SPECTATOR:
				if( ent->client->sess.sessionTeam != TEAM_SPECTATOR )
				{
					ent->client->sess.sessionTeam = TEAM_SPECTATOR;
					ent->client->sess.spectatorState = SPECTATOR_FREE;
					ClientSpawn( ent );
					// make sure by now CS_GRAND rankingsGameID is ready
					trap_SendServerCommand( i, va("rank_status %i\n",status) );
					trap_SendServerCommand( i, "rank_menu\n" );
				}
				break;
			case QGR_STATUS_NO_USER:
			case QGR_STATUS_BAD_PASSWORD:
			case QGR_STATUS_TIMEOUT:
			case QGR_STATUS_NO_MEMBERSHIP:
			case QGR_STATUS_INVALIDUSER:
			case QGR_STATUS_ERROR:
				if( (ent->r.svFlags & SVF_BOT) == 0 )
				{
					trap_RankUserReset( ent->s.clientNum );
				}
				break;
			case QGR_STATUS_ACTIVE:
				if( (ent->client->sess.sessionTeam == TEAM_SPECTATOR) &&
					(g_gametype.integer < GT_TEAM) )
				{
					SetTeam( ent, "free" );
				}

				if( old_status != QGR_STATUS_ACTIVE )
				{
					// player has just become active
					for( j = 0; j < level.maxclients; j++ )
					{
						ent2 = &(g_entities[j]);
						if ( !ent2->inuse )
							continue;
						if ( ent2->client == NULL )
							continue;
						if ( ent2->r.svFlags & SVF_BOT)
							continue;

						if( (i != j) && (trap_RankUserStatus( j ) == QGR_STATUS_ACTIVE) )
						{
							trap_RankReportInt( i, j, QGR_KEY_PLAYED_WITH, 1, 0 );
						}

						// send current scores so the player's rank will show 
						// up under the crosshair immediately
						DeathmatchScoreboardMessage( ent2 );
					}
				}
				break;
			default:
				break;
			}
		}

		// don't let ranked games last forever
		if( ((g_fraglimit.integer == 0) || (g_fraglimit.integer > 100)) && 
			((g_timelimit.integer == 0) || (g_timelimit.integer > 1000)) )
		{
			trap_Cvar_Set( "timelimit", "1000" );
		}
	}

	// tell time to clients so they can show current match rating
	if( level.intermissiontime == 0 )
	{
		for( i = 0; i < level.maxclients; i++ )
		{
			ent = &(g_entities[i]);
			if( ent->client == NULL )
			{
				continue;
			}

			time = (level.time - ent->client->pers.enterTime) / 1000;
			ent->client->ps.persistant[PERS_MATCH_TIME] = time;
		}
	}
}
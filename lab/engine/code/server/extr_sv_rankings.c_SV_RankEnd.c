#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ context; scalar_t__ grank_status; } ;
struct TYPE_4__ {int value; } ;
typedef  scalar_t__ GR_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,...) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  GR_OPT_END ; 
 scalar_t__ GR_STATUS_PENDING ; 
 scalar_t__ GRankSendReportsAsync (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ QGR_STATUS_ACTIVE ; 
 int /*<<< orphan*/  SV_RankCloseContext (TYPE_2__*) ; 
 int /*<<< orphan*/  SV_RankError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_RankSendReportsCBF ; 
 int /*<<< orphan*/  SV_RankStatusString (scalar_t__) ; 
 int /*<<< orphan*/  SV_RankUserLogout (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ qfalse ; 
 TYPE_2__* s_ranked_players ; 
 scalar_t__ s_rankings_active ; 
 scalar_t__ s_server_context ; 
 TYPE_1__* sv_maxclients ; 

void SV_RankEnd( void )
{
	GR_STATUS	status;
	int			i;
	
	Com_DPrintf( "SV_RankEnd();\n" );

	if( !s_rankings_active )
	{
		// cleanup after error during game
		if( s_ranked_players != NULL )
		{
			for( i = 0; i < sv_maxclients->value; i++ )
			{
				if( s_ranked_players[i].context != 0 )
				{
					SV_RankCloseContext( &(s_ranked_players[i]) );
				}
			}
		}
		if( s_server_context != 0 )
		{
			SV_RankCloseContext( NULL );
		}

		return;
	}

	for( i = 0; i < sv_maxclients->value; i++ )
	{
		if( s_ranked_players[i].grank_status == QGR_STATUS_ACTIVE )
		{
			SV_RankUserLogout( i );
			Com_DPrintf( "SV_RankEnd: SV_RankUserLogout %d\n",i );
		}
	}

	assert( s_server_context != 0 );
	
	// send match reports, proceed to SV_RankSendReportsCBF
	status = GRankSendReportsAsync
		( 
			s_server_context,
			0,
			SV_RankSendReportsCBF,
			NULL, 
			GR_OPT_END
		);
			
	if( status != GR_STATUS_PENDING )
	{
		SV_RankError( "SV_RankEnd: Expected GR_STATUS_PENDING, got %s", 
			SV_RankStatusString( status ) );
	}

	s_rankings_active = qfalse;
	Cvar_Set( "sv_rankingsActive", "0" );
}
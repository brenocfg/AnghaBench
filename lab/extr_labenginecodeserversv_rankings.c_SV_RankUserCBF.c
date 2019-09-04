#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ final_status; struct TYPE_9__* context; } ;
typedef  TYPE_1__ ranked_player_t ;
struct TYPE_10__ {int status; } ;
typedef  scalar_t__ GR_STATUS ;
typedef  TYPE_2__ GR_LOGIN ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  GR_OPT_END ; 
#define  GR_STATUS_BADPASSWORD 131 
#define  GR_STATUS_NOUSER 130 
#define  GR_STATUS_OK 129 
 scalar_t__ GR_STATUS_PENDING ; 
#define  GR_STATUS_TIMEOUT 128 
 scalar_t__ GRankCleanupAsync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ GRankJoinGameAsync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ QGR_STATUS_BAD_PASSWORD ; 
 scalar_t__ QGR_STATUS_ERROR ; 
 scalar_t__ QGR_STATUS_NEW ; 
 scalar_t__ QGR_STATUS_NO_USER ; 
 scalar_t__ QGR_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  SV_RankCleanupCBF ; 
 int /*<<< orphan*/  SV_RankCloseContext (TYPE_1__*) ; 
 int /*<<< orphan*/  SV_RankError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_RankJoinGameCBF ; 
 int /*<<< orphan*/  SV_RankStatusString (scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  s_rankings_game_id ; 

__attribute__((used)) static void SV_RankUserCBF( GR_LOGIN* gr_login, void* cbf_arg )
{
	ranked_player_t*	ranked_player;
	GR_STATUS			join_status;
	GR_STATUS			cleanup_status;
	
	assert( gr_login != NULL );
	assert( cbf_arg != NULL );

	Com_DPrintf( "SV_RankUserCBF( %08X, %08X );\n", gr_login, cbf_arg );
	
	ranked_player = (ranked_player_t*)cbf_arg;
	assert(ranked_player);
	assert( ranked_player->context );
	
	switch( gr_login->status )
	{
		case GR_STATUS_OK:
			// attempt to join the game, proceed to SV_RankJoinGameCBF
			join_status = GRankJoinGameAsync
				( 
					ranked_player->context,
					s_rankings_game_id,
					SV_RankJoinGameCBF,
					cbf_arg,
					GR_OPT_END
				);

			if( join_status != GR_STATUS_PENDING )
			{
				SV_RankError( "SV_RankUserCBF: Expected GR_STATUS_PENDING "
					"from GRankJoinGameAsync, got %s", 
					SV_RankStatusString( join_status ) );
			}
			break;
		case GR_STATUS_NOUSER:
			Com_DPrintf( "SV_RankUserCBF: Got status %s\n",
				SV_RankStatusString( gr_login->status ) );
			ranked_player->final_status = QGR_STATUS_NO_USER;
			break;
		case GR_STATUS_BADPASSWORD:
			Com_DPrintf( "SV_RankUserCBF: Got status %s\n",
				SV_RankStatusString( gr_login->status ) );
			ranked_player->final_status = QGR_STATUS_BAD_PASSWORD;
			break;
		case GR_STATUS_TIMEOUT:
			Com_DPrintf( "SV_RankUserCBF: Got status %s\n",
				SV_RankStatusString( gr_login->status ) );
			ranked_player->final_status = QGR_STATUS_TIMEOUT;
			break;
		default:
			Com_DPrintf( "SV_RankUserCBF: Unexpected status %s\n",
				SV_RankStatusString( gr_login->status ) );
			ranked_player->final_status = QGR_STATUS_ERROR;
			break;
	}

	if( ranked_player->final_status != QGR_STATUS_NEW )
	{
		// login or create failed, so clean up before the next attempt
		cleanup_status = GRankCleanupAsync
			(
				ranked_player->context,
				0,
				SV_RankCleanupCBF,
				(void*)ranked_player,
				GR_OPT_END
			);
			
		if( cleanup_status != GR_STATUS_PENDING )
		{
			SV_RankError( "SV_RankUserCBF: Expected GR_STATUS_PENDING "
				"from GRankCleanupAsync, got %s", 
				SV_RankStatusString( cleanup_status ) );
			SV_RankCloseContext( ranked_player );
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ranked_player_t ;
typedef  scalar_t__ GR_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,scalar_t__*,void*) ; 
 scalar_t__ GR_STATUS_OK ; 
 int /*<<< orphan*/  SV_RankCloseContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SV_RankError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_RankStatusString (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SV_RankCleanupCBF( GR_STATUS* status, void* cbf_arg )
{
	ranked_player_t*	ranked_player;
	ranked_player = (ranked_player_t*)cbf_arg;

	assert( status != NULL );
	// NULL cbf_arg means server is cleaning up

	Com_DPrintf( "SV_RankCleanupCBF( %08X, %08X );\n", status, cbf_arg );
	
	if( *status != GR_STATUS_OK )
	{
		SV_RankError( "SV_RankCleanupCBF: Unexpected status %s",
			SV_RankStatusString( *status ) );
	}

	SV_RankCloseContext( ranked_player );
}
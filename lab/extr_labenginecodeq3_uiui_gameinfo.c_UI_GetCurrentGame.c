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

/* Variables and functions */
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 int /*<<< orphan*/  UI_GetBestScore (int,int*,int*) ; 
 char* UI_GetSpecialArenaInfo (char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int ui_numSinglePlayerArenas ; 

int UI_GetCurrentGame( void ) {
	int		level;
	int		rank = 0;
	int		skill;
	const char *info;

	info = UI_GetSpecialArenaInfo( "training" );
	if( info ) {
		level = atoi( Info_ValueForKey( info, "num" ) );
		UI_GetBestScore( level, &rank, &skill );
		if ( !rank || rank > 1 ) {
			return level;
		}
	}

	for( level = 0; level < ui_numSinglePlayerArenas; level++ ) {
		UI_GetBestScore( level, &rank, &skill );
		if ( !rank || rank > 1 ) {
			return level;
		}
	}

	info = UI_GetSpecialArenaInfo( "final" );
	if( !info ) {
		return -1;
	}
	return atoi( Info_ValueForKey( info, "num" ) );
}
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
 int ARENAS_PER_TIER ; 
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 int /*<<< orphan*/  UI_GetBestScore (int,int*,int*) ; 
 int UI_GetNumSPTiers () ; 
 char* UI_GetSpecialArenaInfo (char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 

int UI_TierCompleted( int levelWon ) {
	int			level;
	int			n;
	int			tier;
	int			score;
	int			skill;
	const char	*info;

	tier = levelWon / ARENAS_PER_TIER;
	level = tier * ARENAS_PER_TIER;

	if( tier == UI_GetNumSPTiers() ) {
		info = UI_GetSpecialArenaInfo( "training" );
		if( levelWon == atoi( Info_ValueForKey( info, "num" ) ) ) {
			return 0;
		}
		info = UI_GetSpecialArenaInfo( "final" );
		if( !info || levelWon == atoi( Info_ValueForKey( info, "num" ) ) ) {
			return tier + 1;
		}
		return -1;
	}

	for( n = 0; n < ARENAS_PER_TIER; n++, level++ ) {
		UI_GetBestScore( level, &score, &skill );
		if ( score != 1 ) {
			return -1;
		}
	}
	return tier + 1;
}
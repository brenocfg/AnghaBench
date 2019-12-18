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
struct TYPE_2__ {scalar_t__ won; int level; } ;

/* Variables and functions */
 int ARENAS_PER_TIER ; 
 int QM_ACTIVATED ; 
 char* UI_GetArenaInfoByNumber (int) ; 
 int UI_GetCurrentGame () ; 
 int UI_GetNumSPTiers () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_SPArena_Start (char const*) ; 
 TYPE_1__ postgameMenuInfo ; 

__attribute__((used)) static void UI_SPPostgameMenu_NextEvent( void* ptr, int event ) {
	int			currentSet;
	int			levelSet;
	int			level;
	int			currentLevel;
	const char	*arenaInfo;

	if (event != QM_ACTIVATED) {
		return;
	}
	UI_PopMenu();

	// handle specially if we just won the training map
	if( postgameMenuInfo.won == 0 ) {
		level = 0;
	}
	else {
		level = postgameMenuInfo.level + 1;
	}
	levelSet = level / ARENAS_PER_TIER;

	currentLevel = UI_GetCurrentGame();
	if( currentLevel == -1 ) {
		currentLevel = postgameMenuInfo.level;
	}
	currentSet = currentLevel / ARENAS_PER_TIER;

	if( levelSet > currentSet || levelSet == UI_GetNumSPTiers() ) {
		level = currentLevel;
	}

	arenaInfo = UI_GetArenaInfoByNumber( level );
	if ( !arenaInfo ) {
		return;
	}

	UI_SPArena_Start( arenaInfo );
}
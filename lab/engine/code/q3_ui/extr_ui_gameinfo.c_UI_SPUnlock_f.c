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
typedef  int /*<<< orphan*/  arenaKey ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,char*) ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  UI_SPLevelMenu_ReInit () ; 
 int /*<<< orphan*/  UI_ShowTierVideo (int) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 int /*<<< orphan*/  trap_Print (char*) ; 
 int ui_numSinglePlayerArenas ; 
 int ui_numSpecialSinglePlayerArenas ; 

void UI_SPUnlock_f( void ) {
	char	arenaKey[16];
	char	scores[MAX_INFO_VALUE];
	int		level;
	int		tier;

	// get scores for skill 1
	trap_Cvar_VariableStringBuffer( "g_spScores1", scores, MAX_INFO_VALUE );

	// update scores
	for( level = 0; level < ui_numSinglePlayerArenas + ui_numSpecialSinglePlayerArenas; level++ ) {
		Com_sprintf( arenaKey, sizeof( arenaKey ), "l%i", level );
		Info_SetValueForKey( scores, arenaKey, "1" );
	}
	trap_Cvar_Set( "g_spScores1", scores );

	// unlock cinematics
	for( tier = 1; tier <= 8; tier++ ) {
		UI_ShowTierVideo( tier );
	}

	trap_Print( "All levels unlocked at skill level 1\n" );

	UI_SPLevelMenu_ReInit();
}
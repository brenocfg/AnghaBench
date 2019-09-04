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
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_VALUE ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  va (char*,int) ; 

void UI_SetBestScore( int level, int score ) {
	int		skill;
	int		oldScore;
	char	arenaKey[16];
	char	scores[MAX_INFO_VALUE];

	// validate score
	if( score < 1 || score > 8 ) {
		return;
	}

	// validate skill
	skill = (int)trap_Cvar_VariableValue( "g_spSkill" );
	if( skill < 1 || skill > 5 ) {
		return;
	}

	// get scores
	trap_Cvar_VariableStringBuffer( va( "g_spScores%i", skill ), scores, MAX_INFO_VALUE );

	// see if this is better
	Com_sprintf( arenaKey, sizeof( arenaKey ), "l%i", level );
	oldScore = atoi( Info_ValueForKey( scores, arenaKey ) );
	if( oldScore && oldScore <= score ) {
		return;
	}

	// update scores
	Info_SetValueForKey( scores, arenaKey, va( "%i", score ) );
	trap_Cvar_Set( va( "g_spScores%i", skill ), scores );
}
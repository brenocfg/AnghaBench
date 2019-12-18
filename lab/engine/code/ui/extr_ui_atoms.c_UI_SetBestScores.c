#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_3__ {int time; int /*<<< orphan*/  captures; int /*<<< orphan*/  shutoutBonus; int /*<<< orphan*/  skillBonus; int /*<<< orphan*/  timeBonus; int /*<<< orphan*/  baseScore; int /*<<< orphan*/  blueScore; int /*<<< orphan*/  redScore; int /*<<< orphan*/  perfects; int /*<<< orphan*/  score; int /*<<< orphan*/  gauntlets; int /*<<< orphan*/  assists; int /*<<< orphan*/  defends; int /*<<< orphan*/  excellents; int /*<<< orphan*/  impressives; int /*<<< orphan*/  accuracy; } ;
typedef  TYPE_1__ postGameInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int,...) ; 

void UI_SetBestScores(postGameInfo_t *newInfo, qboolean postGame) {
	trap_Cvar_Set("ui_scoreAccuracy",     va("%i%%", newInfo->accuracy));
	trap_Cvar_Set("ui_scoreImpressives",	va("%i", newInfo->impressives));
	trap_Cvar_Set("ui_scoreExcellents", 	va("%i", newInfo->excellents));
	trap_Cvar_Set("ui_scoreDefends", 			va("%i", newInfo->defends));
	trap_Cvar_Set("ui_scoreAssists", 			va("%i", newInfo->assists));
	trap_Cvar_Set("ui_scoreGauntlets", 		va("%i", newInfo->gauntlets));
	trap_Cvar_Set("ui_scoreScore", 				va("%i", newInfo->score));
	trap_Cvar_Set("ui_scorePerfect",	 		va("%i", newInfo->perfects));
	trap_Cvar_Set("ui_scoreTeam",					va("%i to %i", newInfo->redScore, newInfo->blueScore));
	trap_Cvar_Set("ui_scoreBase",					va("%i", newInfo->baseScore));
	trap_Cvar_Set("ui_scoreTimeBonus",		va("%i", newInfo->timeBonus));
	trap_Cvar_Set("ui_scoreSkillBonus",		va("%i", newInfo->skillBonus));
	trap_Cvar_Set("ui_scoreShutoutBonus",	va("%i", newInfo->shutoutBonus));
	trap_Cvar_Set("ui_scoreTime",					va("%02i:%02i", newInfo->time / 60, newInfo->time % 60));
	trap_Cvar_Set("ui_scoreCaptures",		va("%i", newInfo->captures));
  if (postGame) {
		trap_Cvar_Set("ui_scoreAccuracy2",     va("%i%%", newInfo->accuracy));
		trap_Cvar_Set("ui_scoreImpressives2",	va("%i", newInfo->impressives));
		trap_Cvar_Set("ui_scoreExcellents2", 	va("%i", newInfo->excellents));
		trap_Cvar_Set("ui_scoreDefends2", 			va("%i", newInfo->defends));
		trap_Cvar_Set("ui_scoreAssists2", 			va("%i", newInfo->assists));
		trap_Cvar_Set("ui_scoreGauntlets2", 		va("%i", newInfo->gauntlets));
		trap_Cvar_Set("ui_scoreScore2", 				va("%i", newInfo->score));
		trap_Cvar_Set("ui_scorePerfect2",	 		va("%i", newInfo->perfects));
		trap_Cvar_Set("ui_scoreTeam2",					va("%i to %i", newInfo->redScore, newInfo->blueScore));
		trap_Cvar_Set("ui_scoreBase2",					va("%i", newInfo->baseScore));
		trap_Cvar_Set("ui_scoreTimeBonus2",		va("%i", newInfo->timeBonus));
		trap_Cvar_Set("ui_scoreSkillBonus2",		va("%i", newInfo->skillBonus));
		trap_Cvar_Set("ui_scoreShutoutBonus2",	va("%i", newInfo->shutoutBonus));
		trap_Cvar_Set("ui_scoreTime2",					va("%02i:%02i", newInfo->time / 60, newInfo->time % 60));
		trap_Cvar_Set("ui_scoreCaptures2",		va("%i", newInfo->captures));
	}
}
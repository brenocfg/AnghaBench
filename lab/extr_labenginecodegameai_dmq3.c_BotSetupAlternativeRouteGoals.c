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
 scalar_t__ altroutegoals_setup ; 
 scalar_t__ qtrue ; 

void BotSetupAlternativeRouteGoals(void) {

	if (altroutegoals_setup)
		return;
#ifdef MISSIONPACK
	if (gametype == GT_CTF) {
		if (trap_BotGetLevelItemGoal(-1, "Neutral Flag", &ctf_neutralflag) < 0)
			BotAI_Print(PRT_WARNING, "No alt routes without Neutral Flag\n");
		if (ctf_neutralflag.areanum) {
			//
			red_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
										ctf_neutralflag.origin, ctf_neutralflag.areanum,
										ctf_redflag.origin, ctf_redflag.areanum, TFL_DEFAULT,
										red_altroutegoals, MAX_ALTROUTEGOALS,
										ALTROUTEGOAL_CLUSTERPORTALS|
										ALTROUTEGOAL_VIEWPORTALS);
			blue_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
										ctf_neutralflag.origin, ctf_neutralflag.areanum,
										ctf_blueflag.origin, ctf_blueflag.areanum, TFL_DEFAULT,
										blue_altroutegoals, MAX_ALTROUTEGOALS,
										ALTROUTEGOAL_CLUSTERPORTALS|
										ALTROUTEGOAL_VIEWPORTALS);
		}
	}
	else if (gametype == GT_1FCTF) {
		if (trap_BotGetLevelItemGoal(-1, "Neutral Obelisk", &neutralobelisk) < 0)
			BotAI_Print(PRT_WARNING, "One Flag CTF without Neutral Obelisk\n");
		red_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
									ctf_neutralflag.origin, ctf_neutralflag.areanum,
									ctf_redflag.origin, ctf_redflag.areanum, TFL_DEFAULT,
									red_altroutegoals, MAX_ALTROUTEGOALS,
									ALTROUTEGOAL_CLUSTERPORTALS|
									ALTROUTEGOAL_VIEWPORTALS);
		blue_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
									ctf_neutralflag.origin, ctf_neutralflag.areanum,
									ctf_blueflag.origin, ctf_blueflag.areanum, TFL_DEFAULT,
									blue_altroutegoals, MAX_ALTROUTEGOALS,
									ALTROUTEGOAL_CLUSTERPORTALS|
									ALTROUTEGOAL_VIEWPORTALS);
	}
	else if (gametype == GT_OBELISK) {
		if (trap_BotGetLevelItemGoal(-1, "Neutral Obelisk", &neutralobelisk) < 0)
			BotAI_Print(PRT_WARNING, "No alt routes without Neutral Obelisk\n");
		//
		red_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
									neutralobelisk.origin, neutralobelisk.areanum,
									redobelisk.origin, redobelisk.areanum, TFL_DEFAULT,
									red_altroutegoals, MAX_ALTROUTEGOALS,
									ALTROUTEGOAL_CLUSTERPORTALS|
									ALTROUTEGOAL_VIEWPORTALS);
		blue_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
									neutralobelisk.origin, neutralobelisk.areanum,
									blueobelisk.origin, blueobelisk.areanum, TFL_DEFAULT,
									blue_altroutegoals, MAX_ALTROUTEGOALS,
									ALTROUTEGOAL_CLUSTERPORTALS|
									ALTROUTEGOAL_VIEWPORTALS);
	}
	else if (gametype == GT_HARVESTER) {
		if (trap_BotGetLevelItemGoal(-1, "Neutral Obelisk", &neutralobelisk) < 0)
			BotAI_Print(PRT_WARNING, "Harvester without Neutral Obelisk\n");
		red_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
									neutralobelisk.origin, neutralobelisk.areanum,
									redobelisk.origin, redobelisk.areanum, TFL_DEFAULT,
									red_altroutegoals, MAX_ALTROUTEGOALS,
									ALTROUTEGOAL_CLUSTERPORTALS|
									ALTROUTEGOAL_VIEWPORTALS);
		blue_numaltroutegoals = trap_AAS_AlternativeRouteGoals(
									neutralobelisk.origin, neutralobelisk.areanum,
									blueobelisk.origin, blueobelisk.areanum, TFL_DEFAULT,
									blue_altroutegoals, MAX_ALTROUTEGOALS,
									ALTROUTEGOAL_CLUSTERPORTALS|
									ALTROUTEGOAL_VIEWPORTALS);
	}
#endif
	altroutegoals_setup = qtrue;
}
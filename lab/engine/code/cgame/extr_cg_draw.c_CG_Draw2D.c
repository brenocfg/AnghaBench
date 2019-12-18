#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ stereoFrame_t ;
struct TYPE_22__ {scalar_t__ integer; } ;
struct TYPE_21__ {scalar_t__ integer; } ;
struct TYPE_20__ {scalar_t__ integer; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {int /*<<< orphan*/  integer; } ;
struct TYPE_16__ {scalar_t__ orderTime; scalar_t__ gametype; scalar_t__ orderPending; } ;
struct TYPE_14__ {scalar_t__ pm_type; scalar_t__* persistant; scalar_t__* stats; } ;
struct TYPE_15__ {TYPE_1__ ps; } ;
struct TYPE_13__ {scalar_t__ time; int /*<<< orphan*/  scoreBoardShowing; TYPE_2__* snap; int /*<<< orphan*/  showScores; scalar_t__ levelShot; } ;
struct TYPE_12__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_CheckOrderPending () ; 
 int /*<<< orphan*/  CG_DrawAmmoWarning () ; 
 int /*<<< orphan*/  CG_DrawCenterString () ; 
 int /*<<< orphan*/  CG_DrawCrosshair () ; 
 int /*<<< orphan*/  CG_DrawCrosshairNames () ; 
 int /*<<< orphan*/  CG_DrawFollow () ; 
 int /*<<< orphan*/  CG_DrawHoldableItem () ; 
 int /*<<< orphan*/  CG_DrawIntermission () ; 
 int /*<<< orphan*/  CG_DrawLagometer () ; 
 int /*<<< orphan*/  CG_DrawLowerLeft () ; 
 int /*<<< orphan*/  CG_DrawLowerRight () ; 
 int /*<<< orphan*/  CG_DrawProxWarning () ; 
 int /*<<< orphan*/  CG_DrawReward () ; 
 int /*<<< orphan*/  CG_DrawScoreboard () ; 
 int /*<<< orphan*/  CG_DrawScriptFilledRectangles () ; 
 int /*<<< orphan*/  CG_DrawScriptMessage () ; 
 int /*<<< orphan*/  CG_DrawSpectator () ; 
 int /*<<< orphan*/  CG_DrawStatusBar () ; 
 int /*<<< orphan*/  CG_DrawStatusBarReduced () ; 
 int /*<<< orphan*/  CG_DrawTeamInfo () ; 
 int /*<<< orphan*/  CG_DrawTeamVote () ; 
 int /*<<< orphan*/  CG_DrawTimedMenus () ; 
 int /*<<< orphan*/  CG_DrawUpperRight (scalar_t__) ; 
 int /*<<< orphan*/  CG_DrawVote () ; 
 int /*<<< orphan*/  CG_DrawWarmup () ; 
 int /*<<< orphan*/  CG_DrawWeaponSelect () ; 
 scalar_t__ GT_TEAM ; 
 int /*<<< orphan*/  Menu_PaintAll () ; 
 size_t PERS_TEAM ; 
 scalar_t__ PM_INTERMISSION ; 
 size_t STAT_HEALTH ; 
 scalar_t__ STEREO_CENTER ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_11__ cg ; 
 TYPE_10__ cg_draw2D ; 
 TYPE_9__ cg_drawCrosshairAlways ; 
 TYPE_8__ cg_drawReducedUI ; 
 TYPE_7__ cg_drawScriptRectanglesAlways ; 
 TYPE_6__ cg_drawScriptTextAlways ; 
 TYPE_5__ cg_drawStatus ; 
 TYPE_4__ cg_paused ; 
 TYPE_3__ cgs ; 

__attribute__((used)) static void CG_Draw2D(stereoFrame_t stereoFrame)
{
#ifdef MISSIONPACK
	if (cgs.orderPending && cg.time > cgs.orderTime) {
		CG_CheckOrderPending();
	}
#endif
	// if we are taking a levelshot for the menu, don't draw anything
	if ( cg.levelShot ) {
		return;
	}

	if ( cg_draw2D.integer == 0 || cg_drawReducedUI.integer != 0) {
		if (stereoFrame == STEREO_CENTER) {
			if (cg_drawCrosshairAlways.integer != 0) CG_DrawCrosshair();
			if (cg_drawReducedUI.integer != 0) CG_DrawStatusBarReduced();
			if (cg_drawScriptTextAlways.integer !=0) CG_DrawScriptMessage();
			if (cg_drawScriptRectanglesAlways.integer !=0) CG_DrawScriptFilledRectangles();
		}
		return;
	}

	if ( cg.snap->ps.pm_type == PM_INTERMISSION ) {
		CG_DrawIntermission();
		return;
	}

/*
	if (cg.cameraMode) {
		return;
	}
*/
	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ) {
		CG_DrawSpectator();

		if(stereoFrame == STEREO_CENTER)
			CG_DrawCrosshair();

		CG_DrawCrosshairNames();
	} else {
		// don't draw any status if dead or the scoreboard is being explicitly shown
		if ( !cg.showScores && cg.snap->ps.stats[STAT_HEALTH] > 0 ) {

#ifdef MISSIONPACK
			if ( cg_drawStatus.integer ) {
				Menu_PaintAll();
				CG_DrawTimedMenus();
			}
#else
			CG_DrawStatusBar();
#endif
      
			CG_DrawAmmoWarning();

#ifdef MISSIONPACK
			CG_DrawProxWarning();
#endif      
			if(stereoFrame == STEREO_CENTER)
				CG_DrawCrosshair();
			CG_DrawCrosshairNames();
			CG_DrawWeaponSelect();

#ifndef MISSIONPACK
			CG_DrawHoldableItem();
#else
			//CG_DrawPersistantPowerup();
#endif
			CG_DrawReward();
		}
	}

	if ( cgs.gametype >= GT_TEAM ) {
#ifndef MISSIONPACK
		CG_DrawTeamInfo();
#endif
	}

	CG_DrawScriptMessage();
	CG_DrawScriptFilledRectangles();
	CG_DrawVote();
	CG_DrawTeamVote();

	CG_DrawLagometer();

#ifdef MISSIONPACK
	if (!cg_paused.integer) {
		CG_DrawUpperRight(stereoFrame);
	}
#else
	CG_DrawUpperRight(stereoFrame);
#endif

#ifndef MISSIONPACK
	CG_DrawLowerRight();
	CG_DrawLowerLeft();
#endif

	if ( !CG_DrawFollow() ) {
		CG_DrawWarmup();
	}

	// don't draw center string if scoreboard is up
	cg.scoreBoardShowing = CG_DrawScoreboard();
	if ( !cg.scoreBoardShowing) {
		CG_DrawCenterString();
	}
}
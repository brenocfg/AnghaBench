#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ stereoFrame_t ;
struct TYPE_6__ {int /*<<< orphan*/  refdef; TYPE_2__* snap; } ;
struct TYPE_4__ {scalar_t__* persistant; int pm_flags; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Draw2D (scalar_t__) ; 
 int /*<<< orphan*/  CG_DrawCrosshair3D () ; 
 int /*<<< orphan*/  CG_DrawInformation () ; 
 int /*<<< orphan*/  CG_DrawTourneyScoreboard () ; 
 int /*<<< orphan*/  CG_TileClear () ; 
 size_t PERS_TEAM ; 
 int PMF_SCOREBOARD ; 
 scalar_t__ STEREO_CENTER ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_3__ cg ; 
 int /*<<< orphan*/  trap_R_RenderScene (int /*<<< orphan*/ *) ; 

void CG_DrawActive( stereoFrame_t stereoView ) {
	// optionally draw the info screen instead
	if ( !cg.snap ) {
		CG_DrawInformation();
		return;
	}

	// optionally draw the tournement scoreboard instead
	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR &&
		( cg.snap->ps.pm_flags & PMF_SCOREBOARD ) ) {
		CG_DrawTourneyScoreboard();
		return;
	}

	// clear around the rendered view if sized down
	CG_TileClear();

	if(stereoView != STEREO_CENTER)
		CG_DrawCrosshair3D();

	// draw 3D view
	trap_R_RenderScene( &cg.refdef );

	// draw status bar and other floating elements
 	CG_Draw2D(stereoView);
}
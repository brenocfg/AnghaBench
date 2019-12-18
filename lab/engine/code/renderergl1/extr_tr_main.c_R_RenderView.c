#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ viewportWidth; scalar_t__ viewportHeight; int /*<<< orphan*/  frameCount; int /*<<< orphan*/  frameSceneNum; } ;
typedef  TYPE_2__ viewParms_t ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int numDrawSurfs; scalar_t__ drawSurfs; } ;
struct TYPE_9__ {TYPE_1__ refdef; TYPE_2__ viewParms; int /*<<< orphan*/  viewCount; int /*<<< orphan*/  frameCount; int /*<<< orphan*/  frameSceneNum; } ;

/* Variables and functions */
 int MAX_DRAWSURFS ; 
 int /*<<< orphan*/  R_DebugGraphics () ; 
 int /*<<< orphan*/  R_GenerateDrawSurfs () ; 
 int /*<<< orphan*/  R_RotateForViewer () ; 
 int /*<<< orphan*/  R_SetupProjection (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_SortDrawSurfs (scalar_t__,int) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__* r_zproj ; 
 TYPE_3__ tr ; 

void R_RenderView (viewParms_t *parms) {
	int		firstDrawSurf;
	int		numDrawSurfs;

	if ( parms->viewportWidth <= 0 || parms->viewportHeight <= 0 ) {
		return;
	}

	tr.viewCount++;

	tr.viewParms = *parms;
	tr.viewParms.frameSceneNum = tr.frameSceneNum;
	tr.viewParms.frameCount = tr.frameCount;

	firstDrawSurf = tr.refdef.numDrawSurfs;

	tr.viewCount++;

	// set viewParms.world
	R_RotateForViewer ();

	R_SetupProjection(&tr.viewParms, r_zproj->value, qtrue);

	R_GenerateDrawSurfs();

	// if we overflowed MAX_DRAWSURFS, the drawsurfs
	// wrapped around in the buffer and we will be missing
	// the first surfaces, not the last ones
	numDrawSurfs = tr.refdef.numDrawSurfs;
	if ( numDrawSurfs > MAX_DRAWSURFS ) {
		numDrawSurfs = MAX_DRAWSURFS;
	}

	R_SortDrawSurfs( tr.refdef.drawSurfs + firstDrawSurf, numDrawSurfs - firstDrawSurf );

	// draw main system development information (surface outlines, etc)
	R_DebugGraphics();
}
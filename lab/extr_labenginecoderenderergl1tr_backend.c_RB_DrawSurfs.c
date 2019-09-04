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
struct TYPE_4__ {int /*<<< orphan*/  numDrawSurfs; int /*<<< orphan*/  drawSurfs; int /*<<< orphan*/  viewParms; int /*<<< orphan*/  refdef; } ;
typedef  TYPE_1__ drawSurfsCommand_t ;
struct TYPE_6__ {int /*<<< orphan*/  viewParms; int /*<<< orphan*/  refdef; } ;
struct TYPE_5__ {scalar_t__ numIndexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_RenderDrawSurfList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ backEnd ; 
 TYPE_2__ tess ; 

const void	*RB_DrawSurfs( const void *data ) {
	const drawSurfsCommand_t	*cmd;

	// finish any 2D drawing if needed
	if ( tess.numIndexes ) {
		RB_EndSurface();
	}

	cmd = (const drawSurfsCommand_t *)data;

	backEnd.refdef = cmd->refdef;
	backEnd.viewParms = cmd->viewParms;

	RB_RenderDrawSurfList( cmd->drawSurfs, cmd->numDrawSurfs );

	return (const void *)(cmd + 1);
}
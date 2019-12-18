#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numDrawSurfs; int /*<<< orphan*/  viewParms; int /*<<< orphan*/  refdef; int /*<<< orphan*/ * drawSurfs; int /*<<< orphan*/  commandId; } ;
typedef  TYPE_1__ drawSurfsCommand_t ;
typedef  int /*<<< orphan*/  drawSurf_t ;
struct TYPE_5__ {int /*<<< orphan*/  viewParms; int /*<<< orphan*/  refdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_DRAW_SURFS ; 
 TYPE_1__* R_GetCommandBuffer (int) ; 
 TYPE_2__ tr ; 

void	R_AddDrawSurfCmd( drawSurf_t *drawSurfs, int numDrawSurfs ) {
	drawSurfsCommand_t	*cmd;

	cmd = R_GetCommandBuffer( sizeof( *cmd ) );
	if ( !cmd ) {
		return;
	}
	cmd->commandId = RC_DRAW_SURFS;

	cmd->drawSurfs = drawSurfs;
	cmd->numDrawSurfs = numDrawSurfs;

	cmd->refdef = tr.refdef;
	cmd->viewParms = tr.viewParms;
}
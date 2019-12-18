#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  commandId; } ;
typedef  TYPE_2__ swapBuffersCommand_t ;
struct TYPE_6__ {int msec; } ;
struct TYPE_9__ {TYPE_1__ pc; } ;
struct TYPE_8__ {int frontEndMsec; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_SWAP_BUFFERS ; 
 TYPE_2__* R_GetCommandBufferReserved (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_InitNextFrame () ; 
 int /*<<< orphan*/  R_IssueRenderCommands (int /*<<< orphan*/ ) ; 
 TYPE_4__ backEnd ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__ tr ; 

void RE_EndFrame( int *frontEndMsec, int *backEndMsec ) {
	swapBuffersCommand_t	*cmd;

	if ( !tr.registered ) {
		return;
	}
	cmd = R_GetCommandBufferReserved( sizeof( *cmd ), 0 );
	if ( !cmd ) {
		return;
	}
	cmd->commandId = RC_SWAP_BUFFERS;

	R_IssueRenderCommands( qtrue );

	R_InitNextFrame();

	if ( frontEndMsec ) {
		*frontEndMsec = tr.frontEndMsec;
	}
	tr.frontEndMsec = 0;
	if ( backEndMsec ) {
		*backEndMsec = backEnd.pc.msec;
	}
	backEnd.pc.msec = 0;
}
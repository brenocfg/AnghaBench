#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  usercmd_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_9__ {scalar_t__* viewangles; } ;
struct TYPE_8__ {int integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* issue_console_commands ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
typedef  TYPE_2__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AdjustAngles () ; 
 int /*<<< orphan*/  CL_CmdButtons (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_FinishMove (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_JoystickMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_KeyMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_MouseMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t PITCH ; 
 int /*<<< orphan*/  SCR_DebugGraph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 size_t YAW ; 
 TYPE_5__ cl ; 
 TYPE_4__* cl_debugMove ; 
 TYPE_2__* dmlab_context () ; 
 int /*<<< orphan*/  fabs (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

usercmd_t CL_CreateCmd( void ) {
	usercmd_t	cmd;
	vec3_t		oldAngles;
	DeepmindContext* ctx = dmlab_context();

	VectorCopy( cl.viewangles, oldAngles );

	// keyboard angle adjustment
	CL_AdjustAngles ();
	
	Com_Memset( &cmd, 0, sizeof( cmd ) );

	CL_CmdButtons( &cmd );

	// get basic movement from keyboard
	CL_KeyMove( &cmd );

	// get basic movement from mouse
	CL_MouseMove( &cmd );

	// get basic movement from joystick
	CL_JoystickMove( &cmd );

	// store out the final values
	CL_FinishMove( oldAngles, &cmd );

	ctx->hooks.issue_console_commands( ctx->userdata );

	// draw debug graphs of turning for mouse testing
	if ( cl_debugMove->integer ) {
		if ( cl_debugMove->integer == 1 ) {
			SCR_DebugGraph( fabs(cl.viewangles[YAW] - oldAngles[YAW]) );
		}
		if ( cl_debugMove->integer == 2 ) {
			SCR_DebugGraph( fabs(cl.viewangles[PITCH] - oldAngles[PITCH]) );
		}
	}

	return cmd;
}
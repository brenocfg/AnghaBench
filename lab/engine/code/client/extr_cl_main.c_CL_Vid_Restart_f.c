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
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  checksumFeed; scalar_t__ demorecording; } ;
struct TYPE_5__ {void* cgameStarted; void* soundRegistered; void* uiStarted; void* rendererStarted; } ;
struct TYPE_4__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ CA_CINEMATIC ; 
 scalar_t__ CA_CONNECTED ; 
 int /*<<< orphan*/  CL_CloseAVI () ; 
 int /*<<< orphan*/  CL_InitCGame () ; 
 int /*<<< orphan*/  CL_InitRef () ; 
 int /*<<< orphan*/  CL_ResetPureClientAtServer () ; 
 int /*<<< orphan*/  CL_SendPureChecksums () ; 
 int /*<<< orphan*/  CL_ShutdownCGame () ; 
 int /*<<< orphan*/  CL_ShutdownRef () ; 
 int /*<<< orphan*/  CL_ShutdownUI () ; 
 int /*<<< orphan*/  CL_StartHunkUsers (void*) ; 
 int /*<<< orphan*/  CL_StopRecord_f () ; 
 scalar_t__ CL_VideoRecording () ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int FS_CGAME_REF ; 
 int /*<<< orphan*/  FS_ClearPakReferences (int) ; 
 int /*<<< orphan*/  FS_ConditionalRestart (int /*<<< orphan*/ ,void*) ; 
 int FS_UI_REF ; 
 int /*<<< orphan*/  Hunk_Clear () ; 
 int /*<<< orphan*/  Hunk_ClearToMark () ; 
 int /*<<< orphan*/  S_StopAllSounds () ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 TYPE_1__* com_sv_running ; 
 void* qfalse ; 
 void* qtrue ; 

void CL_Vid_Restart_f( void ) {

	// Settings may have changed so stop recording now
	if( CL_VideoRecording( ) ) {
		CL_CloseAVI( );
	}

	if(clc.demorecording)
		CL_StopRecord_f();

	// don't let them loop during the restart
	S_StopAllSounds();

	if(!FS_ConditionalRestart(clc.checksumFeed, qtrue))
	{
		// if not running a server clear the whole hunk
		if(com_sv_running->integer)
		{
			// clear all the client data on the hunk
			Hunk_ClearToMark();
		}
		else
		{
			// clear the whole hunk
			Hunk_Clear();
		}
	
		// shutdown the UI
		CL_ShutdownUI();
		// shutdown the CGame
		CL_ShutdownCGame();
		// shutdown the renderer and clear the renderer interface
		CL_ShutdownRef();
		// client is no longer pure until new checksums are sent
		CL_ResetPureClientAtServer();
		// clear pak references
		FS_ClearPakReferences( FS_UI_REF | FS_CGAME_REF );
		// reinitialize the filesystem if the game directory or checksum has changed

		cls.rendererStarted = qfalse;
		cls.uiStarted = qfalse;
		cls.cgameStarted = qfalse;
		cls.soundRegistered = qfalse;

		// unpause so the cgame definitely gets a snapshot and renders a frame
		Cvar_Set("cl_paused", "0");

		// initialize the renderer interface
		CL_InitRef();

		// startup all the client stuff
		CL_StartHunkUsers(qfalse);

		// start the cgame if connected
		if(clc.state > CA_CONNECTED && clc.state != CA_CINEMATIC)
		{
			cls.cgameStarted = qtrue;
			CL_InitCGame();
			// send pure checksums
			CL_SendPureChecksums();
		}
	}
}
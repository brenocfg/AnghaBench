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
typedef  scalar_t__ qboolean ;
struct TYPE_6__ {scalar_t__ demorecording; } ;
struct TYPE_5__ {void* soundRegistered; void* rendererStarted; void* cgameStarted; void* uiStarted; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Shutdown ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CL_CloseAVI () ; 
 int /*<<< orphan*/  CL_ShutdownCGame () ; 
 int /*<<< orphan*/  CL_ShutdownRef () ; 
 int /*<<< orphan*/  CL_ShutdownUI () ; 
 int /*<<< orphan*/  CL_StopRecord_f () ; 
 scalar_t__ CL_VideoRecording () ; 
 int /*<<< orphan*/  CL_cURL_Shutdown () ; 
 int /*<<< orphan*/  S_DisableSounds () ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 void* qfalse ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void CL_ShutdownAll(qboolean shutdownRef)
{
	if(CL_VideoRecording())
		CL_CloseAVI();

	if(clc.demorecording)
		CL_StopRecord_f();

#ifdef USE_CURL
	CL_cURL_Shutdown();
#endif
	// clear sounds
	S_DisableSounds();
	// shutdown CGame
	CL_ShutdownCGame();
	// shutdown UI
	CL_ShutdownUI();

	// shutdown the renderer
	if(shutdownRef)
		CL_ShutdownRef();
	else if(re.Shutdown)
		re.Shutdown(qfalse);		// don't destroy window or context

	cls.uiStarted = qfalse;
	cls.cgameStarted = qfalse;
	cls.rendererStarted = qfalse;
	cls.soundRegistered = qfalse;
}
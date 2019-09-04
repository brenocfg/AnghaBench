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
struct TYPE_6__ {void* uiStarted; void* soundRegistered; void* soundStarted; void* rendererStarted; } ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_InitRenderer () ; 
 int /*<<< orphan*/  CL_InitUI () ; 
 int /*<<< orphan*/  S_BeginRegistration () ; 
 int /*<<< orphan*/  S_Init () ; 
 TYPE_3__ cls ; 
 TYPE_2__* com_cl_running ; 
 TYPE_1__* com_dedicated ; 
 void* qtrue ; 

void CL_StartHunkUsers( qboolean rendererOnly ) {
	if (!com_cl_running) {
		return;
	}

	if ( !com_cl_running->integer ) {
		return;
	}

	if ( !cls.rendererStarted ) {
		cls.rendererStarted = qtrue;
		CL_InitRenderer();
	}

	if ( rendererOnly ) {
		return;
	}

	if ( !cls.soundStarted ) {
		cls.soundStarted = qtrue;
		S_Init();
	}

	if ( !cls.soundRegistered ) {
		cls.soundRegistered = qtrue;
		S_BeginRegistration();
	}

	if( com_dedicated->integer ) {
		return;
	}

	if ( !cls.uiStarted ) {
		cls.uiStarted = qtrue;
		CL_InitUI();
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {void* integer; } ;
struct TYPE_3__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_Disconnect (void*) ; 
 int /*<<< orphan*/  CL_Init () ; 
 int /*<<< orphan*/  CL_Shutdown (char*,scalar_t__,void*) ; 
 int /*<<< orphan*/  CL_StartHunkUsers (void*) ; 
 int /*<<< orphan*/  Com_ExecuteCfg () ; 
 int /*<<< orphan*/  Cvar_Restart (void*) ; 
 int /*<<< orphan*/  FS_Restart (int) ; 
 int /*<<< orphan*/  NET_Restart_f () ; 
 int /*<<< orphan*/  SV_Shutdown (char*) ; 
 TYPE_2__* com_cl_running ; 
 scalar_t__ com_fullyInitialized ; 
 void* com_gameClientRestarting ; 
 void* com_gameRestarting ; 
 TYPE_1__* com_sv_running ; 
 void* qfalse ; 
 void* qtrue ; 

void Com_GameRestart(int checksumFeed, qboolean disconnect)
{
	// make sure no recursion can be triggered
	if(!com_gameRestarting && com_fullyInitialized)
	{
		com_gameRestarting = qtrue;
		com_gameClientRestarting = com_cl_running->integer;

		// Kill server if we have one
		if(com_sv_running->integer)
			SV_Shutdown("Game directory changed");

		if(com_gameClientRestarting)
		{
			if(disconnect)
				CL_Disconnect(qfalse);
				
			CL_Shutdown("Game directory changed", disconnect, qfalse);
		}

		FS_Restart(checksumFeed);
	
		// Clean out any user and VM created cvars
		Cvar_Restart(qtrue);
		Com_ExecuteCfg();

		if(disconnect)
		{
			// We don't want to change any network settings if gamedir
			// change was triggered by a connect to server because the
			// new network settings might make the connection fail.
			NET_Restart_f();
		}

		if(com_gameClientRestarting)
		{
			CL_Init();
			CL_StartHunkUsers(qfalse);
		}
		
		com_gameRestarting = qfalse;
		com_gameClientRestarting = qfalse;
	}
}
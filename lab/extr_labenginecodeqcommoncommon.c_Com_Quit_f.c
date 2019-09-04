#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CL_Shutdown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Cmd_Args () ; 
 int /*<<< orphan*/  Com_Shutdown () ; 
 int /*<<< orphan*/  FS_Shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_Shutdown (char*) ; 
 int /*<<< orphan*/  Sys_Quit () ; 
 int /*<<< orphan*/  VM_Forced_Unload_Done () ; 
 int /*<<< orphan*/  VM_Forced_Unload_Start () ; 
 int /*<<< orphan*/  com_errorEntered ; 
 int /*<<< orphan*/  qtrue ; 

void Com_Quit_f( void ) {
	// don't try to shutdown if we are in a recursive error
	char *p = Cmd_Args( );
	if ( !com_errorEntered ) {
		// Some VMs might execute "quit" command directly,
		// which would trigger an unload of active VM error.
		// Sys_Quit will kill this process anyways, so
		// a corrupt call stack makes no difference
		VM_Forced_Unload_Start();
		SV_Shutdown(p[0] ? p : "Server quit");
		CL_Shutdown(p[0] ? p : "Client quit", qtrue, qtrue);
		VM_Forced_Unload_Done();
		Com_Shutdown ();
		FS_Shutdown(qtrue);
	}
	Sys_Quit ();
}
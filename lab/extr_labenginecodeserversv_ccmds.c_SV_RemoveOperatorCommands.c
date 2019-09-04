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

void SV_RemoveOperatorCommands( void ) {
#if 0
	// removing these won't let the server start again
	Cmd_RemoveCommand ("heartbeat");
	Cmd_RemoveCommand ("kick");
	Cmd_RemoveCommand ("kicknum");
	Cmd_RemoveCommand ("clientkick");
	Cmd_RemoveCommand ("kickall");
	Cmd_RemoveCommand ("kickbots");
	Cmd_RemoveCommand ("banUser");
	Cmd_RemoveCommand ("banClient");
	Cmd_RemoveCommand ("status");
	Cmd_RemoveCommand ("serverinfo");
	Cmd_RemoveCommand ("systeminfo");
	Cmd_RemoveCommand ("dumpuser");
	Cmd_RemoveCommand ("map_restart");
	Cmd_RemoveCommand ("sectorlist");
	Cmd_RemoveCommand ("say");
#endif
}
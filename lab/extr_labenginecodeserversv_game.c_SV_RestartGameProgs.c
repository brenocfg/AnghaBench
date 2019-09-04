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
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  GAME_SHUTDOWN ; 
 int /*<<< orphan*/  SV_InitGameVM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_Restart (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gvm ; 
 int /*<<< orphan*/  qtrue ; 

void SV_RestartGameProgs( void ) {
	if ( !gvm ) {
		return;
	}
	VM_Call( gvm, GAME_SHUTDOWN, qtrue );

	// do a restart instead of a free
	gvm = VM_Restart(gvm, qtrue);
	if ( !gvm ) {
		Com_Error( ERR_FATAL, "VM_Restart on game failed" );
	}

	SV_InitGameVM( qtrue );
}
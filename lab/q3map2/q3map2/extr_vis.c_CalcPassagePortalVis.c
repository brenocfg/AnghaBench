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
 int /*<<< orphan*/  CreatePassages ; 
 int /*<<< orphan*/  PassageMemory () ; 
 int /*<<< orphan*/  PassagePortalFlow ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 int numportals ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void CalcPassagePortalVis( void ){
	PassageMemory();

#ifdef MREDEBUG
	Sys_Printf( "%6d portals out of %d", 0, numportals * 2 );
	RunThreadsOnIndividual( numportals * 2, qfalse, CreatePassages );
	Sys_Printf( "\n" );
	Sys_Printf( "%6d portals out of %d", 0, numportals * 2 );
	RunThreadsOnIndividual( numportals * 2, qfalse, PassagePortalFlow );
	Sys_Printf( "\n" );
#else
	Sys_Printf( "\n--- CreatePassages (%d) ---\n", numportals * 2 );
	RunThreadsOnIndividual( numportals * 2, qtrue, CreatePassages );

	Sys_Printf( "\n--- PassagePortalFlow (%d) ---\n", numportals * 2 );
	RunThreadsOnIndividual( numportals * 2, qtrue, PassagePortalFlow );
#endif
}
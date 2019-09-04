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
 int /*<<< orphan*/  EmitPlanes () ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 int /*<<< orphan*/  UnparseEntities () ; 
 int /*<<< orphan*/  WriteBSPFile (char*) ; 
 int /*<<< orphan*/  WriteSurfaceExtraFile (char*) ; 
 int /*<<< orphan*/  numBSPEntities ; 
 int /*<<< orphan*/  numEntities ; 
 char* source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void EndBSPFile( void ){
	char path[ 1024 ];


	Sys_FPrintf( SYS_VRB, "--- EndBSPFile ---\n" );

	EmitPlanes();

	numBSPEntities = numEntities;
	UnparseEntities();

	/* write the surface extra file */
	WriteSurfaceExtraFile( source );

	/* write the bsp */
	sprintf( path, "%s.bsp", source );
	Sys_Printf( "Writing %s\n", path );
	WriteBSPFile( path );
}
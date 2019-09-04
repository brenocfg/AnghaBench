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
 int /*<<< orphan*/  DefaultExtension (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ExpandArg (char*) ; 
 int /*<<< orphan*/  ExportLightmaps () ; 
 int /*<<< orphan*/  LoadBSPFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripExtension (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ExportLightmapsMain( int argc, char **argv ){
	/* arg checking */
	if ( argc < 1 ) {
		Sys_Printf( "Usage: q3map -export [-v] <mapname>\n" );
		return 0;
	}

	/* do some path mangling */
	strcpy( source, ExpandArg( argv[ argc - 1 ] ) );
	StripExtension( source );
	DefaultExtension( source, ".bsp" );

	/* load the bsp */
	Sys_Printf( "Loading %s\n", source );
	LoadBSPFile( source );

	/* export the lightmaps */
	ExportLightmaps();

	/* return to sender */
	return 0;
}
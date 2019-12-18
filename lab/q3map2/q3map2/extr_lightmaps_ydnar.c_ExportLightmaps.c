#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int lightmapSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_mkdir (char*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 int /*<<< orphan*/  WriteTGA24 (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bspLightBytes ; 
 TYPE_1__* game ; 
 int numBSPLightBytes ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

void ExportLightmaps( void ){
	int i;
	char dirname[ 1024 ], filename[ 1024 ];
	byte        *lightmap;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- ExportLightmaps ---\n" );

	/* do some path mangling */
	strcpy( dirname, source );
	StripExtension( dirname );

	/* sanity check */
	if ( bspLightBytes == NULL ) {
		Sys_FPrintf( SYS_WRN, "WARNING: No BSP lightmap data\n" );
		return;
	}

	/* make a directory for the lightmaps */
	Q_mkdir( dirname );

	/* iterate through the lightmaps */
	for ( i = 0, lightmap = bspLightBytes; lightmap < ( bspLightBytes + numBSPLightBytes ); i++, lightmap += ( game->lightmapSize * game->lightmapSize * 3 ) )
	{
		/* write a tga image out */
		sprintf( filename, "%s/lightmap_%04d.tga", dirname, i );
		Sys_Printf( "Writing %s\n", filename );
		WriteTGA24( filename, lightmap, game->lightmapSize, game->lightmapSize, qfalse );
	}
}
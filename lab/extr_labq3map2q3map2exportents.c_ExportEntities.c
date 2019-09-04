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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 char* bspEntData ; 
 scalar_t__ bspEntDataSize ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

void ExportEntities( void ){
        char filename[ 1024 ];
        FILE *file;
		
        /* note it */
        Sys_FPrintf( SYS_VRB, "--- ExportEntities ---\n" );
		
        /* do some path mangling */
        strcpy( filename, source );
        StripExtension( filename );
        strcat( filename, ".ent" );
		
        /* sanity check */
        if ( bspEntDataSize == 0 ) {
			Sys_FPrintf( SYS_WRN, "WARNING: No BSP entity data. aborting...\n" );
			return;
        }
		
        /* write it */
        Sys_Printf( "Writing %s\n", filename );
        Sys_FPrintf( SYS_VRB, "(%d bytes)\n", bspEntDataSize );
        file = fopen( filename, "w" );
		
        if ( file == NULL ) {
                Error( "Unable to open %s for writing", filename );
        }
		
        fprintf( file, "%s\n", bspEntData );
        fclose( file );
}
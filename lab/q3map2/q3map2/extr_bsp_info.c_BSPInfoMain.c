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
 int /*<<< orphan*/  DefaultExtension (char*,char*) ; 
 int /*<<< orphan*/  ExtractFileExtension (char*,char*) ; 
 int /*<<< orphan*/  LoadBSPFile (char*) ; 
 int /*<<< orphan*/  PrintBSPFileSizes () ; 
 int Q_filelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  infoMode ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int BSPInfoMain( int count, char **fileNames ){
	int i;
	char source[ 1024 ], ext[ 64 ];
	int size;
	FILE        *f;


	/* dummy check */
	if ( count < 1 ) {
		Sys_Printf( "No files to dump info for.\n" );
		return -1;
	}

	/* enable info mode */
	infoMode = qtrue;

	/* walk file list */
	for ( i = 0; i < count; i++ )
	{
		Sys_Printf( "---------------------------------\n" );

		/* mangle filename and get size */
		strcpy( source, fileNames[ i ] );
		ExtractFileExtension( source, ext );
		if ( !Q_stricmp( ext, "map" ) ) {
			StripExtension( source );
		}
		DefaultExtension( source, ".bsp" );
		f = fopen( source, "rb" );
		if ( f ) {
			size = Q_filelength( f );
			fclose( f );
		}
		else{
			size = 0;
		}

		/* load the bsp file and print lump sizes */
		Sys_Printf( "%s\n", source );
		LoadBSPFile( source );
		PrintBSPFileSizes();

		/* print sizes */
		Sys_Printf( "\n" );
		Sys_Printf( "          total         %9d\n", size );
		Sys_Printf( "                        %9d KB\n", size / 1024 );
		Sys_Printf( "                        %9d MB\n", size / ( 1024 * 1024 ) );

		Sys_Printf( "---------------------------------\n" );
	}

	/* return count */
	return i;
}
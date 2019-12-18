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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 unsigned int CON_LogRead (char*,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char const*) ; 
 char* Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  DT_ERROR ; 
 char* FS_BuildOSPath (char const*,char const*,char const*) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  Sys_Dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Sys_Mkdir (char const*) ; 
 int /*<<< orphan*/  Sys_Print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  va (char*,char const*,...) ; 
 unsigned int write (int,char*,unsigned int) ; 

void Sys_ErrorDialog( const char *error )
{
	char buffer[ 1024 ];
	unsigned int size;
	int f = -1;
	const char *homepath = Cvar_VariableString( "fs_homepath" );
	const char *gamedir = Cvar_VariableString( "fs_game" );
	const char *fileName = "crashlog.txt";
	char *dirpath = FS_BuildOSPath( homepath, gamedir, "");
	char *ospath = FS_BuildOSPath( homepath, gamedir, fileName );

	Sys_Print( va( "%s\n", error ) );

#ifndef DEDICATED
	Sys_Dialog( DT_ERROR, va( "%s. See \"%s\" for details.", error, ospath ), "Error" );
#endif

	// Make sure the write path for the crashlog exists...

	if(!Sys_Mkdir(homepath))
	{
		Com_Printf("ERROR: couldn't create path '%s' for crash log.\n", homepath);
		return;
	}

	if(!Sys_Mkdir(dirpath))
	{
		Com_Printf("ERROR: couldn't create path '%s' for crash log.\n", dirpath);
		return;
	}

	// We might be crashing because we maxed out the Quake MAX_FILE_HANDLES,
	// which will come through here, so we don't want to recurse forever by
	// calling FS_FOpenFileWrite()...use the Unix system APIs instead.
	f = open( ospath, O_CREAT | O_TRUNC | O_WRONLY, 0640 );
	if( f == -1 )
	{
		Com_Printf( "ERROR: couldn't open %s\n", fileName );
		return;
	}

	// We're crashing, so we don't care much if write() or close() fails.
	while( ( size = CON_LogRead( buffer, sizeof( buffer ) ) ) > 0 ) {
		if( write( f, buffer, size ) != size ) {
			Com_Printf( "ERROR: couldn't fully write to %s\n", fileName );
			break;
		}
	}

	close( f );
}
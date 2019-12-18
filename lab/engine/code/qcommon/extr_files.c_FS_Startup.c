#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  integer; } ;
struct TYPE_17__ {char* string; } ;
struct TYPE_16__ {char const* string; } ;
struct TYPE_15__ {char* string; } ;
struct TYPE_14__ {char const* string; int /*<<< orphan*/  modified; } ;
struct TYPE_13__ {char* string; } ;
struct TYPE_12__ {char* string; } ;
struct TYPE_11__ {char* string; } ;
struct TYPE_10__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASEGAME ; 
 int CVAR_INIT ; 
 int CVAR_PROTECTED ; 
 int CVAR_SYSTEMINFO ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  Com_AppendCDKey (char const*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Com_ReadCDKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_ForceReset (char*) ; 
 void* Cvar_Get (char*,char const*,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_AddGameDirectory (char*,char const*) ; 
 int /*<<< orphan*/  FS_CreatePath (char const*) ; 
 int /*<<< orphan*/  FS_Dir_f () ; 
 int /*<<< orphan*/  FS_FilenameCompare (char const*,char const*) ; 
 scalar_t__ FS_InvalidGameDir (char const*) ; 
 int /*<<< orphan*/  FS_NewDir_f () ; 
 int /*<<< orphan*/  FS_Path_f () ; 
 int /*<<< orphan*/  FS_ReorderPurePaks () ; 
 int /*<<< orphan*/  FS_TouchFile_f () ; 
 int /*<<< orphan*/  FS_Which_f () ; 
 scalar_t__ Q_stricmp (char const*,char const*) ; 
 char* Sys_DefaultAppPath () ; 
 char* Sys_DefaultHomePath () ; 
 char* Sys_DefaultInstallPath () ; 
 int /*<<< orphan*/ * Sys_FOpen (char*,char*) ; 
 char* Sys_GogPath () ; 
 char* Sys_SteamPath () ; 
 TYPE_9__* com_standalone ; 
 TYPE_8__* fs_apppath ; 
 TYPE_7__* fs_basegame ; 
 TYPE_6__* fs_basepath ; 
 void* fs_debug ; 
 TYPE_5__* fs_gamedirvar ; 
 TYPE_4__* fs_gogpath ; 
 TYPE_3__* fs_homepath ; 
 scalar_t__ fs_packFiles ; 
 TYPE_2__* fs_steampath ; 
 TYPE_1__* fs_temporarypath ; 
 int /*<<< orphan*/ * missingFiles ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void FS_Startup( const char *gameName )
{
	const char *homePath;

	Com_Printf( "----- FS_Startup -----\n" );

	fs_packFiles = 0;

	fs_debug = Cvar_Get( "fs_debug", "0", 0 );
	fs_basepath = Cvar_Get ("fs_basepath", Sys_DefaultInstallPath(), CVAR_INIT|CVAR_PROTECTED );
	fs_basegame = Cvar_Get ("fs_basegame", "", CVAR_INIT );
	homePath = Sys_DefaultHomePath();
	if (!homePath || !homePath[0]) {
		homePath = fs_basepath->string;
	}
	fs_homepath = Cvar_Get ("fs_homepath", homePath, CVAR_INIT|CVAR_PROTECTED );
	fs_gamedirvar = Cvar_Get ("fs_game", "", CVAR_INIT|CVAR_SYSTEMINFO );

	if (!gameName[0]) {
		Cvar_ForceReset( "com_basegame" );
	}

	if (!FS_FilenameCompare(fs_gamedirvar->string, gameName)) {
		// This is the standard base game. Servers and clients should
		// use "" and not the standard basegame name because this messes
		// up pak file negotiation and lots of other stuff
		Cvar_ForceReset( "fs_game" );
	}

	if (FS_InvalidGameDir(gameName)) {
		Com_Error( ERR_DROP, "Invalid com_basegame '%s'", gameName );
	}
	if (FS_InvalidGameDir(fs_basegame->string)) {
		Com_Error( ERR_DROP, "Invalid fs_basegame '%s'", fs_basegame->string );
	}
	if (FS_InvalidGameDir(fs_gamedirvar->string)) {
		Com_Error( ERR_DROP, "Invalid fs_game '%s'", fs_gamedirvar->string );
	}

	// add search path elements in reverse priority order
	fs_gogpath = Cvar_Get ("fs_gogpath", Sys_GogPath(), CVAR_INIT|CVAR_PROTECTED );
	if (fs_gogpath->string[0]) {
		FS_AddGameDirectory( fs_gogpath->string, gameName );
	}
	fs_temporarypath = Cvar_Get ("fs_temporarypath", fs_homepath->string, CVAR_INIT|CVAR_PROTECTED );
	if (fs_temporarypath->string[0]) {
		FS_AddGameDirectory( fs_temporarypath->string, gameName );
	}

	// add search path elements in reverse priority order
	fs_steampath = Cvar_Get ("fs_steampath", Sys_SteamPath(), CVAR_INIT|CVAR_PROTECTED );
	if (fs_steampath->string[0]) {
		FS_AddGameDirectory( fs_steampath->string, gameName );
	}
	if (fs_basepath->string[0]) {
		FS_AddGameDirectory( fs_basepath->string, gameName );
	}
	// fs_homepath is somewhat particular to *nix systems, only add if relevant

#ifdef __APPLE__
	fs_apppath = Cvar_Get ("fs_apppath", Sys_DefaultAppPath(), CVAR_INIT|CVAR_PROTECTED );
	// Make MacOSX also include the base path included with the .app bundle
	if (fs_apppath->string[0])
		FS_AddGameDirectory(fs_apppath->string, gameName);
#endif

	// NOTE: same filtering below for mods and basegame
	if (fs_homepath->string[0] && Q_stricmp(fs_homepath->string,fs_basepath->string)) {
		FS_CreatePath ( fs_homepath->string );
		FS_AddGameDirectory ( fs_homepath->string, gameName );
	}

	// check for additional base game so mods can be based upon other mods
	if ( fs_basegame->string[0] && Q_stricmp( fs_basegame->string, gameName ) ) {
		if (fs_gogpath->string[0]) {
			FS_AddGameDirectory(fs_gogpath->string, fs_basegame->string);
		}
		if (fs_steampath->string[0]) {
			FS_AddGameDirectory(fs_steampath->string, fs_basegame->string);
		}
		if (fs_basepath->string[0]) {
			FS_AddGameDirectory(fs_basepath->string, fs_basegame->string);
		}
		if (fs_homepath->string[0] && Q_stricmp(fs_homepath->string,fs_basepath->string)) {
			FS_AddGameDirectory(fs_homepath->string, fs_basegame->string);
		}
	}

	// check for additional game folder for mods
	if ( fs_gamedirvar->string[0] && Q_stricmp( fs_gamedirvar->string, gameName ) ) {
		if (fs_gogpath->string[0]) {
			FS_AddGameDirectory(fs_gogpath->string, fs_gamedirvar->string);
		}
		if (fs_steampath->string[0]) {
			FS_AddGameDirectory(fs_steampath->string, fs_gamedirvar->string);
		}
		if (fs_basepath->string[0]) {
			FS_AddGameDirectory(fs_basepath->string, fs_gamedirvar->string);
		}
		if (fs_homepath->string[0] && Q_stricmp(fs_homepath->string,fs_basepath->string)) {
			FS_AddGameDirectory(fs_homepath->string, fs_gamedirvar->string);
		}
	}

#ifndef STANDALONE
	if (!com_standalone->integer) {
		Com_ReadCDKey(BASEGAME);
		if (fs_gamedirvar->string[0]) {
			Com_AppendCDKey(fs_gamedirvar->string);
		}
	}
#endif

	// add our commands
	Cmd_AddCommand ("path", FS_Path_f);
	Cmd_AddCommand ("dir", FS_Dir_f );
	Cmd_AddCommand ("fdir", FS_NewDir_f );
	Cmd_AddCommand ("touchFile", FS_TouchFile_f );
	Cmd_AddCommand ("which", FS_Which_f );

	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=506
	// reorder the pure pk3 files according to server order
	FS_ReorderPurePaks();

	// print the current search paths
	FS_Path_f();

	fs_gamedirvar->modified = qfalse; // We just loaded, it's not modified

	Com_Printf( "----------------------\n" );

#ifdef FS_MISSING
	if (missingFiles == NULL) {
		missingFiles = Sys_FOpen( "\\missing.txt", "ab" );
	}
#endif
	Com_Printf( "%d files in pk3 files\n", fs_packFiles );
}
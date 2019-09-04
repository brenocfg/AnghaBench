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
typedef  size_t fileHandle_t ;
struct TYPE_18__ {scalar_t__* string; } ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {scalar_t__* string; } ;
struct TYPE_15__ {scalar_t__* string; } ;
struct TYPE_14__ {scalar_t__* string; } ;
struct TYPE_13__ {scalar_t__* string; } ;
struct TYPE_10__ {void* o; } ;
struct TYPE_11__ {TYPE_1__ file; } ;
struct TYPE_12__ {TYPE_2__ handleFiles; void* handleSync; int /*<<< orphan*/  name; void* zipFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 char* FS_BuildOSPath (scalar_t__*,char const*,char*) ; 
 size_t FS_HandleForFile () ; 
 long FS_filelength (size_t) ; 
 scalar_t__ Q_stricmp (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  S_ClearSoundBuffer () ; 
 void* Sys_FOpen (char*,char*) ; 
 TYPE_9__* fs_basepath ; 
 TYPE_8__* fs_debug ; 
 TYPE_7__* fs_gogpath ; 
 TYPE_6__* fs_homepath ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 TYPE_5__* fs_steampath ; 
 TYPE_4__* fs_temporarypath ; 
 TYPE_3__* fsh ; 
 void* qfalse ; 
 int strlen (char*) ; 

long FS_SV_FOpenFileRead(const char *filename, fileHandle_t *fp)
{
	char *ospath;
	fileHandle_t	f = 0;

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization" );
	}

	f = FS_HandleForFile();
	fsh[f].zipFile = qfalse;

	Q_strncpyz( fsh[f].name, filename, sizeof( fsh[f].name ) );

	// don't let sound stutter
	S_ClearSoundBuffer();

	// search homepath
	ospath = FS_BuildOSPath( fs_homepath->string, filename, "" );
	// remove trailing slash
	ospath[strlen(ospath)-1] = '\0';

	if ( fs_debug->integer ) {
		Com_Printf( "FS_SV_FOpenFileRead (fs_homepath): %s\n", ospath );
	}

	fsh[f].handleFiles.file.o = Sys_FOpen( ospath, "rb" );
	fsh[f].handleSync = qfalse;
	if (!fsh[f].handleFiles.file.o)
	{
		// If fs_homepath == fs_basepath, don't bother
		if (Q_stricmp(fs_homepath->string,fs_basepath->string))
		{
			// search basepath
			ospath = FS_BuildOSPath( fs_basepath->string, filename, "" );
			ospath[strlen(ospath)-1] = '\0';

			if ( fs_debug->integer )
			{
				Com_Printf( "FS_SV_FOpenFileRead (fs_basepath): %s\n", ospath );
			}

			fsh[f].handleFiles.file.o = Sys_FOpen( ospath, "rb" );
			fsh[f].handleSync = qfalse;
		}

		// Check fs_temporarypath too
		if (!fsh[f].handleFiles.file.o && fs_temporarypath->string[0])
		{
			ospath = FS_BuildOSPath( fs_temporarypath->string, filename, "" );
			ospath[strlen(ospath)-1] = '\0';

			if ( fs_debug->integer )
			{
				Com_Printf( "FS_SV_FOpenFileRead (fs_temporarypath): %s\n", ospath );
			}

			fsh[f].handleFiles.file.o = Sys_FOpen( ospath, "rb" );
			fsh[f].handleSync = qfalse;
		}

		// Check fs_steampath too
		if (!fsh[f].handleFiles.file.o && fs_steampath->string[0])
		{
			ospath = FS_BuildOSPath( fs_steampath->string, filename, "" );
			ospath[strlen(ospath)-1] = '\0';

			if ( fs_debug->integer )
			{
				Com_Printf( "FS_SV_FOpenFileRead (fs_steampath): %s\n", ospath );
			}

			fsh[f].handleFiles.file.o = Sys_FOpen( ospath, "rb" );
			fsh[f].handleSync = qfalse;
		}

		// Check fs_gogpath
		if (!fsh[f].handleFiles.file.o && fs_gogpath->string[0])
		{
			ospath = FS_BuildOSPath( fs_gogpath->string, filename, "" );
			ospath[strlen(ospath)-1] = '\0';

			if ( fs_debug->integer )
			{
				Com_Printf( "FS_SV_FOpenFileRead (fs_gogpath): %s\n", ospath );
			}

			fsh[f].handleFiles.file.o = Sys_FOpen( ospath, "rb" );
			fsh[f].handleSync = qfalse;
		}

		if ( !fsh[f].handleFiles.file.o )
		{
			f = 0;
		}
	}

	*fp = f;
	if (f) {
		return FS_filelength(f);
	}

	return -1;
}
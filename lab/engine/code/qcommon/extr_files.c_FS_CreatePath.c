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
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  FS_ReplaceSeparators (char*) ; 
 int MAX_INSTALL_PATH ; 
 char PATH_SEP ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  Sys_Mkdir (char*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 char* strchr (char*,char) ; 
 scalar_t__ strstr (char*,char*) ; 

qboolean FS_CreatePath (char *OSPath) {
	char	*ofs;
	char	path[MAX_INSTALL_PATH];
	
	// make absolutely sure that it can't back up the path
	// FIXME: is c: allowed???
	if ( strstr( OSPath, ".." ) || strstr( OSPath, "::" ) ) {
		Com_Printf( "WARNING: refusing to create relative path \"%s\"\n", OSPath );
		return qtrue;
	}

	Q_strncpyz( path, OSPath, sizeof( path ) );
	FS_ReplaceSeparators( path );

	// Skip creation of the root directory as it will always be there
	ofs = strchr( path, PATH_SEP );
	if ( ofs != NULL ) {
		ofs++;
	}

	for (; ofs != NULL && *ofs ; ofs++) {
		if (*ofs == PATH_SEP) {
			// create the directory
			*ofs = 0;
			if (!Sys_Mkdir (path)) {
				Com_Error( ERR_FATAL, "FS_CreatePath: failed to create path \"%s\"",
					path );
			}
			*ofs = PATH_SEP;
		}
	}

	return qfalse;
}
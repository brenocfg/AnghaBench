#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  description ;
struct TYPE_12__ {char* string; } ;
struct TYPE_11__ {char const* const string; } ;
struct TYPE_10__ {char const* const string; } ;
struct TYPE_9__ {char const* const string; } ;
struct TYPE_8__ {char const* const string; } ;
struct TYPE_7__ {char const* const string; } ;

/* Variables and functions */
 int ARRAY_LEN (char const* const*) ; 
 char* FS_BuildOSPath (char const* const,char*,char*) ; 
 int /*<<< orphan*/  FS_GetModDescription (char*,char*,int) ; 
 scalar_t__ FS_IsExt (char*,char*,int) ; 
 int MAX_INSTALL_PATH ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 scalar_t__ Q_stricmpn (char*,char*,int) ; 
 char** Sys_ConcatenateFileLists (char**,char**) ; 
 int Sys_CountFileList (char**) ; 
 int /*<<< orphan*/  Sys_FreeFileList (char**) ; 
 char** Sys_ListFiles (char const* const,char*,int /*<<< orphan*/ *,int*,scalar_t__) ; 
 TYPE_6__* com_basegame ; 
 TYPE_5__* fs_basepath ; 
 TYPE_4__* fs_gogpath ; 
 TYPE_3__* fs_homepath ; 
 TYPE_2__* fs_steampath ; 
 TYPE_1__* fs_temporarypath ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int	FS_GetModList( char *listbuf, int bufsize ) {
	int nMods, i, j, k, nTotal, nLen, nPaks, nDirs, nPakDirs, nPotential, nDescLen;
	char **pFiles = NULL;
	char **pPaks = NULL;
	char **pDirs = NULL;
	char *name, *path;
	char description[MAX_INSTALL_PATH];

	int dummy;
	char **pFiles0 = NULL;
	qboolean bDrop = qfalse;

	// paths to search for mods
	const char * const paths[] = { fs_basepath->string, fs_homepath->string, fs_steampath->string, fs_gogpath->string, fs_temporarypath->string };

	*listbuf = 0;
	nMods = nTotal = 0;

	// iterate through paths and get list of potential mods
	for (i = 0; i < ARRAY_LEN(paths); i++) {
		pFiles0 = Sys_ListFiles(paths[i], NULL, NULL, &dummy, qtrue);
		// Sys_ConcatenateFileLists frees the lists so Sys_FreeFileList isn't required
		pFiles = Sys_ConcatenateFileLists(pFiles, pFiles0);
	}

	nPotential = Sys_CountFileList(pFiles);

	for (i = 0; i < nPotential; i++) {
		name = pFiles[i];
		// NOTE: cleaner would involve more changes
		// ignore duplicate mod directories
		if (i != 0) {
			bDrop = qfalse;
			for (j = 0; j < i; j++) {
				if (Q_stricmp(pFiles[j], name) == 0) {
					// this one can be dropped
					bDrop = qtrue;
					break;
				}
			}
		}
		// we also drop "baseq3" "." and ".."
		if (bDrop || Q_stricmp(name, com_basegame->string) == 0 || Q_stricmpn(name, ".", 1) == 0) {
			continue;
		}

		// in order to be a valid mod the directory must contain at least one .pk3 or .pk3dir
		// we didn't keep the information when we merged the directory names, as to what OS Path it was found under
		// so we will try each of them here
		for (j = 0; j < ARRAY_LEN(paths); j++) {
			path = FS_BuildOSPath(paths[j], name, "");
			nPaks = nDirs = nPakDirs = 0;
			pPaks = Sys_ListFiles(path, ".pk3", NULL, &nPaks, qfalse);
			pDirs = Sys_ListFiles(path, "/", NULL, &nDirs, qfalse);
			for (k = 0; k < nDirs; k++) {
				// we only want to count directories ending with ".pk3dir"
				if (FS_IsExt(pDirs[k], ".pk3dir", strlen(pDirs[k]))) {
					nPakDirs++;
				}
			}
			// we only use Sys_ListFiles to check whether files are present
			Sys_FreeFileList(pPaks);
			Sys_FreeFileList(pDirs);

			if (nPaks > 0 || nPakDirs > 0) {
				break;
			}
		}

		if (nPaks > 0 || nPakDirs > 0) {
			nLen = strlen(name) + 1;
			// nLen is the length of the mod path
			// we need to see if there is a description available
			FS_GetModDescription(name, description, sizeof(description));
			nDescLen = strlen(description) + 1;

			if (nTotal + nLen + 1 + nDescLen + 1 < bufsize) {
				strcpy(listbuf, name);
				listbuf += nLen;
				strcpy(listbuf, description);
				listbuf += nDescLen;
				nTotal += nLen + nDescLen;
				nMods++;
			} else {
				break;
			}
		}
	}
	Sys_FreeFileList( pFiles );

	return nMods;
}
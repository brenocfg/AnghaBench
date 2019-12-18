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
typedef  scalar_t__ fileHandle_t ;
typedef  int /*<<< orphan*/  descPath ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int /*<<< orphan*/ * FS_FileForHandle (scalar_t__) ; 
 int FS_SV_FOpenFileRead (char*,scalar_t__*) ; 
 int MAX_INSTALL_PATH ; 
 int /*<<< orphan*/  PATH_SEP ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 

void FS_GetModDescription( const char *modDir, char *description, int descriptionLen ) {
	fileHandle_t	descHandle;
	char			descPath[MAX_INSTALL_PATH];
	int				nDescLen;
	FILE			*file;

	Com_sprintf( descPath, sizeof ( descPath ), "%s%cdescription.txt", modDir, PATH_SEP );
	nDescLen = FS_SV_FOpenFileRead( descPath, &descHandle );

	if ( nDescLen > 0 ) {
		file = FS_FileForHandle(descHandle);
		Com_Memset( description, 0, descriptionLen );
		nDescLen = fread(description, 1, descriptionLen, file);
		if (nDescLen >= 0) {
			description[nDescLen] = '\0';
		}
	} else {
		Q_strncpyz( description, modDir, descriptionLen );
	}

	if ( descHandle ) {
		FS_FCloseFile( descHandle );
	}
}
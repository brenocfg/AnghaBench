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
typedef  int /*<<< orphan*/  fileHandle_t ;
typedef  int /*<<< orphan*/  fbuffer ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ CL_CDKeyValidate (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_Memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  FS_FCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_Read (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_SV_FOpenFileRead (char*,int /*<<< orphan*/ *) ; 
 int MAX_OSPATH ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_cdkey ; 

void Com_ReadCDKey( const char *filename ) {
	fileHandle_t	f;
	char			buffer[33];
	char			fbuffer[MAX_OSPATH];

	Com_sprintf(fbuffer, sizeof(fbuffer), "%s/q3key", filename);

	FS_SV_FOpenFileRead( fbuffer, &f );
	if ( !f ) {
		Q_strncpyz( cl_cdkey, "                ", 17 );
		return;
	}

	Com_Memset( buffer, 0, sizeof(buffer) );

	FS_Read( buffer, 16, f );
	FS_FCloseFile( f );

	if (CL_CDKeyValidate(buffer, NULL)) {
		Q_strncpyz( cl_cdkey, buffer, 17 );
	} else {
		Q_strncpyz( cl_cdkey, "                ", 17 );
	}
}
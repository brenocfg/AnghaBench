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

/* Variables and functions */
 char* Com_MD5File (int /*<<< orphan*/ ,int,char const*,int) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  FS_FCloseFile (int /*<<< orphan*/ ) ; 
 int FS_SV_FOpenFileRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QKEY_FILE ; 
 int QKEY_SIZE ; 

__attribute__((used)) static void CL_UpdateGUID( const char *prefix, int prefix_len )
{
	fileHandle_t f;
	int len;

	len = FS_SV_FOpenFileRead( QKEY_FILE, &f );
	FS_FCloseFile( f );

	if( len != QKEY_SIZE ) 
		Cvar_Set( "cl_guid", "" );
	else
		Cvar_Set( "cl_guid", Com_MD5File( QKEY_FILE, QKEY_SIZE,
			prefix, prefix_len ) );
}
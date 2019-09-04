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

/* Variables and functions */
 scalar_t__ COM_CompareExtension (char const*,char*) ; 
 int /*<<< orphan*/  COM_GetExtension (char const*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ Sys_DllExtension (char const*) ; 

__attribute__((used)) static void FS_CheckFilenameIsMutable( const char *filename,
		const char *function )
{
	// Check if the filename ends with the library, QVM, or pk3 extension
	if( Sys_DllExtension( filename )
		|| COM_CompareExtension( filename, ".qvm" )
		|| COM_CompareExtension( filename, ".pk3" ) )
	{
		Com_Error( ERR_FATAL, "%s: Not allowed to manipulate '%s' due "
			"to %s extension", function, filename, COM_GetExtension( filename ) );
	}
}
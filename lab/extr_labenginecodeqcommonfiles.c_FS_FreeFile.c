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
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  Hunk_ClearTempMemory () ; 
 int /*<<< orphan*/  Hunk_FreeTempMemory (void*) ; 
 scalar_t__ fs_loadStack ; 
 int /*<<< orphan*/  fs_searchpaths ; 

void FS_FreeFile( void *buffer ) {
	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization" );
	}
	if ( !buffer ) {
		Com_Error( ERR_FATAL, "FS_FreeFile( NULL )" );
	}
	fs_loadStack--;

	Hunk_FreeTempMemory( buffer );

	// if all of our temp files are free, clear all of our space
	if ( fs_loadStack == 0 ) {
		Hunk_ClearTempMemory();
	}
}
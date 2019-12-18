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

/* Variables and functions */
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int /*<<< orphan*/  FS_FOpenFileRead (char const*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void SV_TouchFile( const char *filename ) {
	fileHandle_t	f;

	FS_FOpenFileRead( filename, &f, qfalse );
	if ( f ) {
		FS_FCloseFile( f );
	}
}
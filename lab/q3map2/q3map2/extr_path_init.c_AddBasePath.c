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
 int /*<<< orphan*/  CleanPath (int /*<<< orphan*/ ) ; 
 size_t MAX_BASE_PATHS ; 
 int /*<<< orphan*/ * basePaths ; 
 size_t numBasePaths ; 
 int /*<<< orphan*/  safe_malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

void AddBasePath( char *path ){
	/* dummy check */
	if ( path == NULL || path[ 0 ] == '\0' || numBasePaths >= MAX_BASE_PATHS ) {
		return;
	}

	/* add it to the list */
	basePaths[ numBasePaths ] = safe_malloc( strlen( path ) + 1 );
	strcpy( basePaths[ numBasePaths ], path );
	CleanPath( basePaths[ numBasePaths ] );
	numBasePaths++;
}
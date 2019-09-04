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
 int /*<<< orphan*/  CleanPath (int /*<<< orphan*/ *) ; 
 size_t MAX_GAME_PATHS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** gamePaths ; 
 size_t numGamePaths ; 
 int /*<<< orphan*/ * safe_malloc (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (char*) ; 

void AddGamePath( char *path ){
	int i;

	/* dummy check */
	if ( path == NULL || path[ 0 ] == '\0' || numGamePaths >= MAX_GAME_PATHS ) {
		return;
	}

	/* add it to the list */
	gamePaths[ numGamePaths ] = safe_malloc( strlen( path ) + 1 );
	strcpy( gamePaths[ numGamePaths ], path );
	CleanPath( gamePaths[ numGamePaths ] );
	numGamePaths++;

	/* don't add it if it's already there */
	for ( i = 0; i < numGamePaths - 1; i++ )
	{
		if ( strcmp( gamePaths[i], gamePaths[numGamePaths - 1] ) == 0 ) {
			free( gamePaths[numGamePaths - 1] );
			gamePaths[numGamePaths - 1] = NULL;
			numGamePaths--;
			break;
		}
	}

}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* gamePath; char* magic; char* arg; int /*<<< orphan*/  homeBasePath; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddBasePath (char*) ; 
 int /*<<< orphan*/  AddGamePath (char*) ; 
 int /*<<< orphan*/  AddHomeBasePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CleanPath (char*) ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 TYPE_1__* GetGame (char*) ; 
 int /*<<< orphan*/  LokiInitPaths (char*) ; 
 int MAX_BASE_PATHS ; 
 int MAX_GAME_PATHS ; 
 int MAX_OS_PATH ; 
 scalar_t__ Q_strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Sys_Printf (char*) ; 
 char** basePaths ; 
 TYPE_1__* game ; 
 char** gamePaths ; 
 TYPE_1__* games ; 
 char* installPath ; 
 int numBasePaths ; 
 int numGamePaths ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int unz_GAME_QL ; 
 int /*<<< orphan*/  vfsInitDirectory (char*) ; 

void InitPaths( int *argc, char **argv ){
	int i, j, k, len, len2;
	char temp[ MAX_OS_PATH ];

	/* note it */
	Sys_FPrintf( SYS_VRB, "--- InitPaths ---\n" );

	/* get the install path for backup */
	LokiInitPaths( argv[ 0 ] );

	/* set game to default (q3a) */
	game = &games[ 0 ];
	numBasePaths = 0;
	numGamePaths = 0;

	/* parse through the arguments and extract those relevant to paths */
	for ( i = 0; i < *argc; i++ )
	{
		/* check for null */
		if ( argv[ i ] == NULL ) {
			continue;
		}

		/* -game */
		if ( strcmp( argv[ i ], "-game" ) == 0 ) {
			if ( ++i >= *argc ) {
				Error( "Out of arguments: No game specified after %s", argv[ i - 1 ] );
			}
			argv[ i - 1 ] = NULL;
			game = GetGame( argv[ i ] );
			if ( game == NULL ) {
				game = &games[ 0 ];
			}
			argv[ i ] = NULL;
		}

		/* -fs_basepath */
		else if ( strcmp( argv[ i ], "-fs_basepath" ) == 0 ) {
			if ( ++i >= *argc ) {
				Error( "Out of arguments: No path specified after %s.", argv[ i - 1 ] );
			}
			argv[ i - 1 ] = NULL;
			AddBasePath( argv[ i ] );
			argv[ i ] = NULL;
		}

		/* -fs_game */
		else if ( strcmp( argv[ i ], "-fs_game" ) == 0 ) {
			if ( ++i >= *argc ) {
				Error( "Out of arguments: No path specified after %s.", argv[ i - 1 ] );
			}
			argv[ i - 1 ] = NULL;
			AddGamePath( argv[ i ] );
			argv[ i ] = NULL;
		}
	}

	/* remove processed arguments */
	for ( i = 0, j = 0, k = 0; i < *argc && j < *argc; i++, j++ )
	{
		for ( ; j < *argc && argv[ j ] == NULL; j++ ) ;
		argv[ i ] = argv[ j ];
		if ( argv[ i ] != NULL ) {
			k++;
		}
	}
	*argc = k;

	/* add standard game path */
	AddGamePath( game->gamePath );

	/* if there is no base path set, figure it out */
	if ( numBasePaths == 0 ) {
		/* this is another crappy replacement for SetQdirFromPath() */
		len2 = strlen( game->magic );
		for ( i = 0; i < *argc && numBasePaths == 0; i++ )
		{
			/* extract the arg */
			strcpy( temp, argv[ i ] );
			CleanPath( temp );
			len = strlen( temp );
			Sys_FPrintf( SYS_VRB, "Searching for \"%s\" in \"%s\" (%d)...\n", game->magic, temp, i );

			/* this is slow, but only done once */
			for ( j = 0; j < ( len - len2 ); j++ )
			{
				/* check for the game's magic word */
				if ( Q_strncasecmp( &temp[ j ], game->magic, len2 ) == 0 ) {
					/* now find the next slash and nuke everything after it */
					while ( temp[ ++j ] != '/' && temp[ j ] != '\0' ) ;
					temp[ j ] = '\0';

					/* add this as a base path */
					AddBasePath( temp );
					break;
				}
			}
		}

		/* add install path */
		if ( numBasePaths == 0 ) {
			AddBasePath( installPath );
		}

		/* check again */
		if ( numBasePaths == 0 ) {
			Error( "Failed to find a valid base path." );
		}
	}

	/* this only affects unix */
	AddHomeBasePath( game->homeBasePath );

	/* initialize vfs paths */
	if ( numBasePaths > MAX_BASE_PATHS ) {
		numBasePaths = MAX_BASE_PATHS;
	}
	if ( numGamePaths > MAX_GAME_PATHS ) {
		numGamePaths = MAX_GAME_PATHS;
	}

	/* walk the list of game paths */
	for ( j = 0; j < numGamePaths; j++ )
	{
		/* walk the list of base paths */
		for ( i = 0; i < numBasePaths; i++ )
		{
			/* create a full path and initialize it */
			sprintf( temp, "%s/%s/", basePaths[ i ], gamePaths[ j ] );
			//quick n dirty patch to enable vfs for quakelive
			if (strcmp(game->arg, "quakelive") == 0 ) {
				unz_GAME_QL = 1;
			} else {
				unz_GAME_QL = 0;
			}
			vfsInitDirectory( temp );
		}
	}

	/* done */
	Sys_Printf( "\n" );
}
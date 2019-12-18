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
 char* BASEDIRNAME ; 
 int /*<<< orphan*/  Error (char*,char const*,...) ; 
 int /*<<< orphan*/  Q_getwd (char*) ; 
 int /*<<< orphan*/  Q_strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 char* gamedir ; 
 char* qdir ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* writedir ; 

void SetQdirFromPath( const char *path ){
	char temp[1024];
	const char  *c;
	const char *sep;
	int len, count;

	if ( !( path[0] == '/' || path[0] == '\\' || path[1] == ':' ) ) { // path is partial
		Q_getwd( temp );
		strcat( temp, path );
		path = temp;
	}

	// search for "quake2" in path

	len = strlen( BASEDIRNAME );
	for ( c = path + strlen( path ) - 1 ; c != path ; c-- )
	{
		int i;

		if ( !Q_strncasecmp( c, BASEDIRNAME, len ) ) {
			//
			//strncpy (qdir, path, c+len+2-path);
			// the +2 assumes a 2 or 3 following quake which is not the
			// case with a retail install
			// so we need to add up how much to the next separator
			sep = c + len;
			count = 1;
			while ( *sep && *sep != '/' && *sep != '\\' )
			{
				sep++;
				count++;
			}
			strncpy( qdir, path, c + len + count - path );
			Sys_Printf( "qdir: %s\n", qdir );
			for ( i = 0; i < strlen( qdir ); i++ )
			{
				if ( qdir[i] == '\\' ) {
					qdir[i] = '/';
				}
			}

			c += len + count;
			while ( *c )
			{
				if ( *c == '/' || *c == '\\' ) {
					strncpy( gamedir, path, c + 1 - path );

					for ( i = 0; i < strlen( gamedir ); i++ )
					{
						if ( gamedir[i] == '\\' ) {
							gamedir[i] = '/';
						}
					}

					Sys_Printf( "gamedir: %s\n", gamedir );

					if ( !writedir[0] ) {
						strcpy( writedir, gamedir );
					}
					else if ( writedir[strlen( writedir ) - 1] != '/' ) {
						writedir[strlen( writedir )] = '/';
						writedir[strlen( writedir ) + 1] = 0;
					}

					return;
				}
				c++;
			}
			Error( "No gamedir in %s", path );
			return;
		}
	}
	Error( "SetQdirFromPath: no '%s' in %s", BASEDIRNAME, path );
}
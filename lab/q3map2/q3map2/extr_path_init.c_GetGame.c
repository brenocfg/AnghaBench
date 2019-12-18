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
struct TYPE_4__ {char* arg; } ;
typedef  TYPE_1__ game_t ;

/* Variables and functions */
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_1__* games ; 

game_t *GetGame( char *arg ){
	int i;


	/* dummy check */
	if ( arg == NULL || arg[ 0 ] == '\0' ) {
		return NULL;
	}

	/* joke */
	if ( !Q_stricmp( arg, "quake1" ) ||
		 !Q_stricmp( arg, "quake2" ) ||
		 !Q_stricmp( arg, "unreal" ) ||
		 !Q_stricmp( arg, "ut2k3" ) ||
		 !Q_stricmp( arg, "dn3d" ) ||
		 !Q_stricmp( arg, "dnf" ) ||
		 !Q_stricmp( arg, "hl" ) ) {
		Sys_Printf( "April fools, silly rabbit!\n" );
		exit( 0 );
	}

	/* test it */
	i = 0;
	while ( games[ i ].arg != NULL )
	{
		if ( Q_stricmp( arg, games[ i ].arg ) == 0 ) {
			return &games[ i ];
		}
		i++;
	}

	/* no matching game */
	return NULL;
}
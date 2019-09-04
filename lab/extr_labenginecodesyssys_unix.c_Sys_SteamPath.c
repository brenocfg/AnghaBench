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
 char* steamPath ; 

char *Sys_SteamPath( void )
{
	// Disabled since Steam doesn't let you install Quake 3 on Mac/Linux
#if 0 //#ifdef STEAMPATH_NAME
	char *p;

	if( ( p = getenv( "HOME" ) ) != NULL )
	{
#ifdef __APPLE__
		char *steamPathEnd = "/Library/Application Support/Steam/SteamApps/common/" STEAMPATH_NAME;
#else
		char *steamPathEnd = "/.steam/steam/SteamApps/common/" STEAMPATH_NAME;
#endif
		Com_sprintf(steamPath, sizeof(steamPath), "%s%s", p, steamPathEnd);
	}
#endif

	return steamPath;
}
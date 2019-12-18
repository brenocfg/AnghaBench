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
 int /*<<< orphan*/  CON_Shutdown () ; 
 int /*<<< orphan*/  FS_GetCurrentGameDir () ; 
 int /*<<< orphan*/  NET_Shutdown () ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  Sys_PlatformExit () ; 
 int /*<<< orphan*/  Sys_RemovePIDFile (int /*<<< orphan*/ ) ; 
 scalar_t__ com_fullyInitialized ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static __attribute__ ((noreturn)) void Sys_Exit( int exitCode )
{
	CON_Shutdown( );

#ifndef DEDICATED
	SDL_Quit( );
#endif

	if( exitCode < 2 && com_fullyInitialized )
	{
		// Normal exit
		Sys_RemovePIDFile( FS_GetCurrentGameDir() );
	}

	NET_Shutdown( );

	Sys_PlatformExit( );

	exit( exitCode );
}
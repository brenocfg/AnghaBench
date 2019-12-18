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
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  IN_Restart () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_WasInit (int /*<<< orphan*/ ) ; 

void Sys_In_Restart_f( void )
{
#ifndef DEDICATED
	if( !SDL_WasInit( SDL_INIT_VIDEO ) )
	{
		Com_Printf( "in_restart: Cannot restart input while video is shutdown\n" );
		return;
	}
#endif

	IN_Restart( );
}
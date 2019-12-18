#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_4__ {int isFullscreen; } ;
struct TYPE_5__ {TYPE_1__ glconfig; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  Cbuf_AddText (char*) ; 
 scalar_t__ Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  IN_ActivateMouse (int) ; 
 int /*<<< orphan*/  IN_DeactivateMouse (int) ; 
 int /*<<< orphan*/  IN_JoyMove () ; 
 int /*<<< orphan*/  IN_ProcessEvents () ; 
 int KEYCATCH_CONSOLE ; 
 int Key_GetCatcher () ; 
 int SDL_GetWindowFlags (int /*<<< orphan*/ ) ; 
 int SDL_WINDOW_INPUT_FOCUS ; 
 int /*<<< orphan*/  SDL_window ; 
 scalar_t__ Sys_Milliseconds () ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 scalar_t__ in_eventTime ; 
 scalar_t__ vidRestartTime ; 

void IN_Frame( void )
{
	qboolean loading;

	IN_JoyMove( );

	// If not DISCONNECTED (main menu) or ACTIVE (in game), we're loading
	loading = ( clc.state != CA_DISCONNECTED && clc.state != CA_ACTIVE );

	// update isFullscreen since it might of changed since the last vid_restart
	cls.glconfig.isFullscreen = Cvar_VariableIntegerValue( "r_fullscreen" ) != 0;

	if( !cls.glconfig.isFullscreen && ( Key_GetCatcher( ) & KEYCATCH_CONSOLE ) )
	{
		// Console is down in windowed mode
		IN_DeactivateMouse( cls.glconfig.isFullscreen );
	}
	else if( !cls.glconfig.isFullscreen && loading )
	{
		// Loading in windowed mode
		IN_DeactivateMouse( cls.glconfig.isFullscreen );
	}
	else if( !( SDL_GetWindowFlags( SDL_window ) & SDL_WINDOW_INPUT_FOCUS ) )
	{
		// Window not got focus
		IN_DeactivateMouse( cls.glconfig.isFullscreen );
	}
	else
		IN_ActivateMouse( cls.glconfig.isFullscreen );

	IN_ProcessEvents( );

	// Set event time for next frame to earliest possible time an event could happen
	in_eventTime = Sys_Milliseconds( );

	// In case we had to delay actual restart of video system
	if( ( vidRestartTime != 0 ) && ( vidRestartTime < Sys_Milliseconds( ) ) )
	{
		vidRestartTime = 0;
		Cbuf_AddText( "vid_restart\n" );
	}
}
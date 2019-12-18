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
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct TYPE_5__ {void* modified; scalar_t__ integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* IN_Restart ) () ;int /*<<< orphan*/  (* Cmd_ExecuteText ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  (* Cvar_Set ) (char*,char*) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;scalar_t__ (* Cvar_VariableIntegerValue ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SDL_GL_SwapWindow (int /*<<< orphan*/ ) ; 
 int SDL_GetWindowFlags (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_SetWindowFullscreen (int /*<<< orphan*/ ,scalar_t__) ; 
 int SDL_WINDOW_FULLSCREEN ; 
 int /*<<< orphan*/  SDL_window ; 
 void* qfalse ; 
 TYPE_3__* r_drawBuffer ; 
 TYPE_2__* r_fullscreen ; 
 TYPE_1__ ri ; 
 scalar_t__ stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (char*,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 () ; 

void GLimp_EndFrame( void )
{
	// don't flip if drawing to front buffer
	if ( Q_stricmp( r_drawBuffer->string, "GL_FRONT" ) != 0 )
	{
		SDL_GL_SwapWindow( SDL_window );
	}

	if( r_fullscreen->modified )
	{
		int         fullscreen;
		qboolean    needToToggle;
		qboolean    sdlToggled = qfalse;

		// Find out the current state
		fullscreen = !!( SDL_GetWindowFlags( SDL_window ) & SDL_WINDOW_FULLSCREEN );

		if( r_fullscreen->integer && ri.Cvar_VariableIntegerValue( "in_nograb" ) )
		{
			ri.Printf( PRINT_ALL, "Fullscreen not allowed with in_nograb 1\n");
			ri.Cvar_Set( "r_fullscreen", "0" );
			r_fullscreen->modified = qfalse;
		}

		// Is the state we want different from the current state?
		needToToggle = !!r_fullscreen->integer != fullscreen;

		if( needToToggle )
		{
			sdlToggled = SDL_SetWindowFullscreen( SDL_window, r_fullscreen->integer ) >= 0;

			// SDL_WM_ToggleFullScreen didn't work, so do it the slow way
			if( !sdlToggled )
				ri.Cmd_ExecuteText(EXEC_APPEND, "vid_restart\n");

			ri.IN_Restart( );
		}

		r_fullscreen->modified = qfalse;
	}
}
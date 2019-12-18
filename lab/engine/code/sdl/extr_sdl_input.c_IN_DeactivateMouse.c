#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int vidWidth; int vidHeight; } ;
struct TYPE_4__ {TYPE_1__ glconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_GobbleMotionEvents () ; 
 int /*<<< orphan*/  SDL_FALSE ; 
 int SDL_GetWindowFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_SetRelativeMouseMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetWindowGrab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_ShowCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_TRUE ; 
 int SDL_WINDOW_MOUSE_FOCUS ; 
 int /*<<< orphan*/  SDL_WarpMouseInWindow (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SDL_WasInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_window ; 
 TYPE_2__ cls ; 
 scalar_t__ mouseActive ; 
 int /*<<< orphan*/  mouseAvailable ; 
 scalar_t__ qfalse ; 

__attribute__((used)) static void IN_DeactivateMouse( qboolean isFullscreen )
{
	if( !SDL_WasInit( SDL_INIT_VIDEO ) )
		return;

	// Always show the cursor when the mouse is disabled,
	// but not when fullscreen
	if( !isFullscreen )
		SDL_ShowCursor( SDL_TRUE );

	if( !mouseAvailable )
		return;

	if( mouseActive )
	{
		IN_GobbleMotionEvents( );

		SDL_SetWindowGrab( SDL_window, SDL_FALSE );
		SDL_SetRelativeMouseMode( SDL_FALSE );

		// Don't warp the mouse unless the cursor is within the window
		if( SDL_GetWindowFlags( SDL_window ) & SDL_WINDOW_MOUSE_FOCUS )
			SDL_WarpMouseInWindow( SDL_window, cls.glconfig.vidWidth / 2, cls.glconfig.vidHeight / 2 );

		mouseActive = qfalse;
	}
}
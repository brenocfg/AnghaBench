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
 scalar_t__ Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  IN_DeactivateMouse (int) ; 
 int /*<<< orphan*/  IN_ShutdownJoystick () ; 
 int /*<<< orphan*/  SDL_StopTextInput () ; 
 int /*<<< orphan*/ * SDL_window ; 
 int /*<<< orphan*/  mouseAvailable ; 
 int /*<<< orphan*/  qfalse ; 

void IN_Shutdown( void )
{
	SDL_StopTextInput( );

	IN_DeactivateMouse( Cvar_VariableIntegerValue( "r_fullscreen" ) != 0 );
	mouseAvailable = qfalse;

	IN_ShutdownJoystick( );

	SDL_window = NULL;
}
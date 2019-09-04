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
 int /*<<< orphan*/  SDL_GameControllerClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_INIT_GAMECONTROLLER ; 
 int /*<<< orphan*/  SDL_INIT_JOYSTICK ; 
 int /*<<< orphan*/  SDL_JoystickClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WasInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gamepad ; 
 int /*<<< orphan*/ * stick ; 

__attribute__((used)) static void IN_ShutdownJoystick( void )
{
	if ( !SDL_WasInit( SDL_INIT_GAMECONTROLLER ) )
		return;

	if ( !SDL_WasInit( SDL_INIT_JOYSTICK ) )
		return;

	if (gamepad)
	{
		SDL_GameControllerClose(gamepad);
		gamepad = NULL;
	}

	if (stick)
	{
		SDL_JoystickClose(stick);
		stick = NULL;
	}

	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}
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
 scalar_t__ SDL_GL_MakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_glContext ; 
 int /*<<< orphan*/  SDL_window ; 
 int /*<<< orphan*/  Sys_Error (char*,int /*<<< orphan*/ ) ; 

void GLimp_MakeCurrent( void ) {
	if ( SDL_GL_MakeCurrent( SDL_window, SDL_glContext ) != 0 ) {
		Sys_Error( "GLimp_MakeCurrent - %s", SDL_GetError() );
	}
}
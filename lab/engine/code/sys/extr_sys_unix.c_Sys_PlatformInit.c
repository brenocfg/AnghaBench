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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  Sys_SetFloatEnv () ; 
 char* getenv (char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int stdinIsATTY ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

void Sys_PlatformInit( void )
{
	const char* term = getenv( "TERM" );

	Sys_SetFloatEnv();

	stdinIsATTY = isatty( STDIN_FILENO ) &&
		!( term && ( !strcmp( term, "raw" ) || !strcmp( term, "dumb" ) ) );
}
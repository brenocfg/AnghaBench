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
 char* Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  PID_FILENAME ; 
 char* va (char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *Sys_PIDFileName( const char *gamedir )
{
	const char *homePath = Cvar_VariableString( "fs_homepath" );

	if( *homePath != '\0' )
		return va( "%s/%s/%s", homePath, gamedir, PID_FILENAME );

	return NULL;
}
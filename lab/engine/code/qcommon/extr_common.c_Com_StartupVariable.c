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
 scalar_t__ CVAR_NONEXISTENT ; 
 int /*<<< orphan*/  CVAR_USER_CREATED ; 
 int /*<<< orphan*/  Cmd_ArgsFrom (int) ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Cmd_TokenizeString (int /*<<< orphan*/ ) ; 
 scalar_t__ Cvar_Flags (char*) ; 
 int /*<<< orphan*/  Cvar_Get (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Set2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * com_consoleLines ; 
 int com_numConsoleLines ; 
 int /*<<< orphan*/  qfalse ; 
 scalar_t__ strcmp (char*,char const*) ; 

void Com_StartupVariable( const char *match ) {
	int		i;
	char	*s;

	for (i=0 ; i < com_numConsoleLines ; i++) {
		Cmd_TokenizeString( com_consoleLines[i] );
		if ( strcmp( Cmd_Argv(0), "set" ) ) {
			continue;
		}

		s = Cmd_Argv(1);
		
		if(!match || !strcmp(s, match))
		{
			if(Cvar_Flags(s) == CVAR_NONEXISTENT)
				Cvar_Get(s, Cmd_ArgsFrom(2), CVAR_USER_CREATED);
			else
				Cvar_Set2(s, Cmd_ArgsFrom(2), qfalse);
		}
	}
}
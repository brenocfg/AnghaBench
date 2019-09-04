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
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Set2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Cvar_VariableString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_VariableValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int) ; 

void Cvar_Toggle_f( void ) {
	int		i, c = Cmd_Argc();
	char		*curval;

	if(c < 2) {
		Com_Printf("usage: toggle <variable> [value1, value2, ...]\n");
		return;
	}

	if(c == 2) {
		Cvar_Set2(Cmd_Argv(1), va("%d", 
			!Cvar_VariableValue(Cmd_Argv(1))), 
			qfalse);
		return;
	}

	if(c == 3) {
		Com_Printf("toggle: nothing to toggle to\n");
		return;
	}

	curval = Cvar_VariableString(Cmd_Argv(1));

	// don't bother checking the last arg for a match since the desired
	// behaviour is the same as no match (set to the first argument)
	for(i = 2; i + 1 < c; i++) {
		if(strcmp(curval, Cmd_Argv(i)) == 0) {
			Cvar_Set2(Cmd_Argv(1), Cmd_Argv(i + 1), qfalse);
			return;
		}
	}

	// fallback
	Cvar_Set2(Cmd_Argv(1), Cmd_Argv(2), qfalse);
}
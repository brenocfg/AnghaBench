#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cvar_t ;

/* Variables and functions */
 int CVAR_USER_CREATED ; 
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* Cvar_FindVar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Unset (TYPE_1__*) ; 

void Cvar_Unset_f(void)
{
	cvar_t *cv;
	
	if(Cmd_Argc() != 2)
	{
		Com_Printf("Usage: %s <varname>\n", Cmd_Argv(0));
		return;
	}
	
	cv = Cvar_FindVar(Cmd_Argv(1));

	if(!cv)
		return;
	
	if(cv->flags & CVAR_USER_CREATED)
		Cvar_Unset(cv);
	else
		Com_Printf("Error: %s: Variable %s is not user created.\n", Cmd_Argv(0), cv->name);
}
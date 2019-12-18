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
 char* Cmd_ArgsFrom (int) ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*,...) ; 
 int /*<<< orphan*/  Sys_SetEnv (char*,char*) ; 
 char* getenv (char*) ; 

void Com_Setenv_f(void)
{
	int argc = Cmd_Argc();
	char *arg1 = Cmd_Argv(1);

	if(argc > 2)
	{
		char *arg2 = Cmd_ArgsFrom(2);
		
		Sys_SetEnv(arg1, arg2);
	}
	else if(argc == 2)
	{
		char *env = getenv(arg1);
		
		if(env)
			Com_Printf("%s=%s\n", arg1, env);
		else
			Com_Printf("%s undefined\n", arg1);
        }
}
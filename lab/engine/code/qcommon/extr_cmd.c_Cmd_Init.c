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
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_CompleteCfgName ; 
 int /*<<< orphan*/  Cmd_Echo_f ; 
 int /*<<< orphan*/  Cmd_Exec_f ; 
 int /*<<< orphan*/  Cmd_List_f ; 
 int /*<<< orphan*/  Cmd_SetCommandCompletionFunc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_Vstr_f ; 
 int /*<<< orphan*/  Cmd_Wait_f ; 
 int /*<<< orphan*/  Cvar_CompleteCvarName ; 

void Cmd_Init (void) {
	Cmd_AddCommand ("cmdlist",Cmd_List_f);
	Cmd_AddCommand ("exec",Cmd_Exec_f);
	Cmd_AddCommand ("execq",Cmd_Exec_f);
	Cmd_SetCommandCompletionFunc( "exec", Cmd_CompleteCfgName );
	Cmd_SetCommandCompletionFunc( "execq", Cmd_CompleteCfgName );
	Cmd_AddCommand ("vstr",Cmd_Vstr_f);
	Cmd_SetCommandCompletionFunc( "vstr", Cvar_CompleteCvarName );
	Cmd_AddCommand ("echo",Cmd_Echo_f);
	Cmd_AddCommand ("wait", Cmd_Wait_f);
}
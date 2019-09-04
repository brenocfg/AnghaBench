#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ function; } ;
typedef  TYPE_1__ cmd_function_t ;

/* Variables and functions */
 TYPE_1__* Cmd_FindCommand (char const*) ; 
 int /*<<< orphan*/  Cmd_RemoveCommand (char const*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ERR_DROP ; 

void Cmd_RemoveCommandSafe( const char *cmd_name )
{
	cmd_function_t *cmd = Cmd_FindCommand( cmd_name );

	if( !cmd )
		return;
	if( cmd->function )
	{
		Com_Error( ERR_DROP, "Restricted source tried to remove "
			"system command \"%s\"", cmd_name );
		return;
	}

	Cmd_RemoveCommand( cmd_name );
}
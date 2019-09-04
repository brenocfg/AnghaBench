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
typedef  int /*<<< orphan*/  completionFunc_t ;
struct TYPE_3__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ cmd_function_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* cmd_functions ; 

void Cmd_SetCommandCompletionFunc( const char *command, completionFunc_t complete ) {
	cmd_function_t	*cmd;

	for( cmd = cmd_functions; cmd; cmd = cmd->next ) {
		if( !Q_stricmp( command, cmd->name ) ) {
			cmd->complete = complete;
			return;
		}
	}
}
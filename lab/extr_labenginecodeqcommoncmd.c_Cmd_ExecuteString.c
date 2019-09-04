#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* function ) () ;struct TYPE_5__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cmd_function_t ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_6__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ForwardCommandToServer (char const*) ; 
 scalar_t__ CL_GameCommand () ; 
 int /*<<< orphan*/  Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_TokenizeString (char const*) ; 
 scalar_t__ Cvar_Command () ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SV_GameCommand () ; 
 scalar_t__ UI_GameCommand () ; 
 int /*<<< orphan*/ * cmd_argv ; 
 TYPE_1__* cmd_functions ; 
 TYPE_3__* com_cl_running ; 
 TYPE_2__* com_sv_running ; 
 int /*<<< orphan*/  stub1 () ; 

void	Cmd_ExecuteString( const char *text ) {	
	cmd_function_t	*cmd, **prev;

	// execute the command line
	Cmd_TokenizeString( text );		
	if ( !Cmd_Argc() ) {
		return;		// no tokens
	}

	// check registered command functions	
	for ( prev = &cmd_functions ; *prev ; prev = &cmd->next ) {
		cmd = *prev;
		if ( !Q_stricmp( cmd_argv[0],cmd->name ) ) {
			// rearrange the links so that the command will be
			// near the head of the list next time it is used
			*prev = cmd->next;
			cmd->next = cmd_functions;
			cmd_functions = cmd;

			// perform the action
			if ( !cmd->function ) {
				// let the cgame or game handle it
				break;
			} else {
				cmd->function ();
			}
			return;
		}
	}
	
	// check cvars
	if ( Cvar_Command() ) {
		return;
	}

	// check client game commands
	if ( com_cl_running && com_cl_running->integer && CL_GameCommand() ) {
		return;
	}

	// check server game commands
	if ( com_sv_running && com_sv_running->integer && SV_GameCommand() ) {
		return;
	}

	// check ui commands
	if ( com_cl_running && com_cl_running->integer && UI_GameCommand() ) {
		return;
	}

	// send it as a server command if we are connected
	// this will usually result in a chat message
	CL_ForwardCommandToServer ( text );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ voteExecuteTime; scalar_t__ time; scalar_t__ voteTime; int voteYes; int numVotingClients; int voteNo; int /*<<< orphan*/  voteString; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_VOTE_TIME ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ VOTE_TIME ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,char*) ; 
 int /*<<< orphan*/  trap_SetConfigstring (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void CheckVote( void ) {
	if ( level.voteExecuteTime && level.voteExecuteTime < level.time ) {
		level.voteExecuteTime = 0;
		trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", level.voteString ) );
	}
	if ( !level.voteTime ) {
		return;
	}
	if ( level.time - level.voteTime >= VOTE_TIME ) {
		trap_SendServerCommand( -1, "print \"Vote failed.\n\"" );
	} else {
		// ATVI Q3 1.32 Patch #9, WNF
		if ( level.voteYes > level.numVotingClients/2 ) {
			// execute the command, then remove the vote
			trap_SendServerCommand( -1, "print \"Vote passed.\n\"" );
			level.voteExecuteTime = level.time + 3000;
		} else if ( level.voteNo >= level.numVotingClients/2 ) {
			// same behavior as a timeout
			trap_SendServerCommand( -1, "print \"Vote failed.\n\"" );
		} else {
			// still waiting for a majority
			return;
		}
	}
	level.voteTime = 0;
	trap_SetConfigstring( CS_VOTE_TIME, "" );

}
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
struct TYPE_2__ {scalar_t__* teamVoteTime; scalar_t__ time; int* teamVoteYes; int* numteamVotingClients; int* teamVoteNo; scalar_t__* teamVoteString; } ;

/* Variables and functions */
 scalar_t__ CS_TEAMVOTE_TIME ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 int /*<<< orphan*/  Q_strncmp (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  SetLeader (int,int /*<<< orphan*/ ) ; 
 int TEAM_BLUE ; 
 int TEAM_RED ; 
 scalar_t__ VOTE_TIME ; 
 int /*<<< orphan*/  atoi (scalar_t__) ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,char*) ; 
 int /*<<< orphan*/  trap_SetConfigstring (scalar_t__,char*) ; 
 int /*<<< orphan*/  va (char*,scalar_t__) ; 

void CheckTeamVote( int team ) {
	int cs_offset;

	if ( team == TEAM_RED )
		cs_offset = 0;
	else if ( team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !level.teamVoteTime[cs_offset] ) {
		return;
	}
	if ( level.time - level.teamVoteTime[cs_offset] >= VOTE_TIME ) {
		trap_SendServerCommand( -1, "print \"Team vote failed.\n\"" );
	} else {
		if ( level.teamVoteYes[cs_offset] > level.numteamVotingClients[cs_offset]/2 ) {
			// execute the command, then remove the vote
			trap_SendServerCommand( -1, "print \"Team vote passed.\n\"" );
			//
			if ( !Q_strncmp( "leader", level.teamVoteString[cs_offset], 6) ) {
				//set the team leader
				SetLeader(team, atoi(level.teamVoteString[cs_offset] + 7));
			}
			else {
				trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", level.teamVoteString[cs_offset] ) );
			}
		} else if ( level.teamVoteNo[cs_offset] >= level.numteamVotingClients[cs_offset]/2 ) {
			// same behavior as a timeout
			trap_SendServerCommand( -1, "print \"Team vote failed.\n\"" );
		} else {
			// still waiting for a majority
			return;
		}
	}
	level.teamVoteTime[cs_offset] = 0;
	trap_SetConfigstring( CS_TEAMVOTE_TIME + cs_offset, "" );

}
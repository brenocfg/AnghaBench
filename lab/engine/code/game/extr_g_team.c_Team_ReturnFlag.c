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
 int /*<<< orphan*/  PrintMsg (int /*<<< orphan*/ *,char*,...) ; 
 int TEAM_FREE ; 
 int /*<<< orphan*/  TeamName (int) ; 
 int /*<<< orphan*/  Team_ResetFlag (int) ; 
 int /*<<< orphan*/  Team_ReturnFlagSound (int /*<<< orphan*/ ,int) ; 

void Team_ReturnFlag( int team ) {
	Team_ReturnFlagSound(Team_ResetFlag(team), team);
	if( team == TEAM_FREE ) {
		PrintMsg(NULL, "The flag has returned!\n" );
	}
	else {
		PrintMsg(NULL, "The %s flag has returned!\n", TeamName(team));
	}
}
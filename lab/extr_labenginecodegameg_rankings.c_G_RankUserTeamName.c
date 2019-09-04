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
struct TYPE_2__ {scalar_t__ warmupTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  QGR_KEY_TEAM_NAME ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_RankReportStr (int,int,int /*<<< orphan*/ ,char*) ; 

void G_RankUserTeamName( int self, char* team_name )
{
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	trap_RankReportStr( self, -1, QGR_KEY_TEAM_NAME, team_name );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {scalar_t__ gametype; size_t newBotIndex; int /*<<< orphan*/ * playerNameBuffers; TYPE_2__* playerTeam; TYPE_1__* playerType; } ;
struct TYPE_5__ {scalar_t__ curvalue; } ;
struct TYPE_4__ {int curvalue; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 int PLAYER_SLOTS ; 
 scalar_t__ Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__ s_serveroptions ; 

__attribute__((used)) static qboolean BotAlreadySelected( const char *checkName ) {
	int		n;

	for( n = 1; n < PLAYER_SLOTS; n++ ) {
		if( s_serveroptions.playerType[n].curvalue != 1 ) {
			continue;
		}
		if( (s_serveroptions.gametype >= GT_TEAM) &&
			(s_serveroptions.playerTeam[n].curvalue != s_serveroptions.playerTeam[s_serveroptions.newBotIndex].curvalue ) ) {
			continue;
		}
		if( Q_stricmp( checkName, s_serveroptions.playerNameBuffers[n] ) == 0 ) {
			return qtrue;
		}
	}

	return qfalse;
}
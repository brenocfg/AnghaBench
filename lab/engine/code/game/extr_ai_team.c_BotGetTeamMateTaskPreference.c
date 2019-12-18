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
typedef  int /*<<< orphan*/  teammatename ;
typedef  int /*<<< orphan*/  bot_state_t ;
struct TYPE_2__ {int preference; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_NETNAME ; 
 scalar_t__ Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctftaskpreferences ; 

int BotGetTeamMateTaskPreference(bot_state_t *bs, int teammate) {
	char teammatename[MAX_NETNAME];

	if (!ctftaskpreferences[teammate].preference) return 0;
	ClientName(teammate, teammatename, sizeof(teammatename));
	if (Q_stricmp(teammatename, ctftaskpreferences[teammate].name)) return 0;
	return ctftaskpreferences[teammate].preference;
}
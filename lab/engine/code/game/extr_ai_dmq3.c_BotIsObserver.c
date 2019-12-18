#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ pm_type; } ;
struct TYPE_5__ {scalar_t__ client; TYPE_1__ cur_ps; } ;
typedef  TYPE_2__ bot_state_t ;

/* Variables and functions */
 scalar_t__ CS_PLAYERS ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 scalar_t__ PM_SPECTATOR ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

qboolean BotIsObserver(bot_state_t *bs) {
	char buf[MAX_INFO_STRING];
	if (bs->cur_ps.pm_type == PM_SPECTATOR) return qtrue;
	trap_GetConfigstring(CS_PLAYERS+bs->client, buf, sizeof(buf));
	if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR) return qtrue;
	return qfalse;
}
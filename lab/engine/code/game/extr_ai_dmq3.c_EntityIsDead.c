#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {scalar_t__ pm_type; } ;
typedef  TYPE_1__ playerState_t ;
struct TYPE_6__ {scalar_t__ number; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_GetClientState (scalar_t__,TYPE_1__*) ; 
 scalar_t__ MAX_CLIENTS ; 
 scalar_t__ PM_NORMAL ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean EntityIsDead(aas_entityinfo_t *entinfo) {
	playerState_t ps;

	if (entinfo->number >= 0 && entinfo->number < MAX_CLIENTS) {
		//retrieve the current client state
		if (!BotAI_GetClientState(entinfo->number, &ps)) {
			return qfalse;
		}

		if (ps.pm_type != PM_NORMAL) return qtrue;
	}
	return qfalse;
}
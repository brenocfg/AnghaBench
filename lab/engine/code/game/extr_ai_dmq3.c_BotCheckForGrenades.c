#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_7__ {scalar_t__ eType; scalar_t__ weapon; TYPE_1__ pos; } ;
typedef  TYPE_2__ entityState_t ;
struct TYPE_8__ {int /*<<< orphan*/  ms; } ;
typedef  TYPE_3__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVOID_ALWAYS ; 
 scalar_t__ ET_MISSILE ; 
 scalar_t__ WP_GRENADE_LAUNCHER ; 
 int /*<<< orphan*/  trap_BotAddAvoidSpot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void BotCheckForGrenades(bot_state_t *bs, entityState_t *state) {
	// if this is not a grenade
	if (state->eType != ET_MISSILE || state->weapon != WP_GRENADE_LAUNCHER)
		return;
	// try to avoid the grenade
	trap_BotAddAvoidSpot(bs->ms, state->pos.trBase, 160, AVOID_ALWAYS);
}
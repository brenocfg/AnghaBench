#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int respawn_wait; double respawn_time; double respawnchat_time; int enemy; int /*<<< orphan*/  client; int /*<<< orphan*/  chatto; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Seek_LTG (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  BotIsDead (TYPE_1__*) ; 
 double FloatTime () ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Respawn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Talk (int /*<<< orphan*/ ) ; 

int AINode_Respawn(bot_state_t *bs) {
	// if waiting for the actual respawn
	if (bs->respawn_wait) {
		if (!BotIsDead(bs)) {
			AIEnter_Seek_LTG(bs, "respawn: respawned");
		}
		else {
			trap_EA_Respawn(bs->client);
		}
	}
	else if (bs->respawn_time < FloatTime()) {
		// wait until respawned
		bs->respawn_wait = qtrue;
		// elementary action respawn
		trap_EA_Respawn(bs->client);
		//
		if (bs->respawnchat_time) {
			trap_BotEnterChat(bs->cs, 0, bs->chatto);
			bs->enemy = -1;
		}
	}
	if (bs->respawnchat_time && bs->respawnchat_time < FloatTime() - 0.5) {
		trap_EA_Talk(bs->client);
	}
	//
	return qtrue;
}
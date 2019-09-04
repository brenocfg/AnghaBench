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
struct TYPE_4__ {int* inventory; int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHARACTERISTIC_WEAPONJUMPING ; 
 size_t INVENTORY_ARMOR ; 
 size_t INVENTORY_HEALTH ; 
 size_t INVENTORY_QUAD ; 
 size_t INVENTORY_ROCKETLAUNCHER ; 
 size_t INVENTORY_ROCKETS ; 
 TYPE_2__ bot_rocketjump ; 
 int qfalse ; 
 int qtrue ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int BotCanAndWantsToRocketJump(bot_state_t *bs) {
	float rocketjumper;

	//if rocket jumping is disabled
	if (!bot_rocketjump.integer) return qfalse;
	//if no rocket launcher
	if (bs->inventory[INVENTORY_ROCKETLAUNCHER] <= 0) return qfalse;
	//if low on rockets
	if (bs->inventory[INVENTORY_ROCKETS] < 3) return qfalse;
	//never rocket jump with the Quad
	if (bs->inventory[INVENTORY_QUAD]) return qfalse;
	//if low on health
	if (bs->inventory[INVENTORY_HEALTH] < 60) return qfalse;
	//if not full health
	if (bs->inventory[INVENTORY_HEALTH] < 90) {
		//if the bot has insufficient armor
		if (bs->inventory[INVENTORY_ARMOR] < 40) return qfalse;
	}
	rocketjumper = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_WEAPONJUMPING, 0, 1);
	if (rocketjumper < 0.5) return qfalse;
	return qtrue;
}
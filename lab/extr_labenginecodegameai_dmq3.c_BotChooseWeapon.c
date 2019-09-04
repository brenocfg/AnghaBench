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
struct TYPE_4__ {scalar_t__ weaponstate; } ;
struct TYPE_5__ {int weaponnum; int /*<<< orphan*/  client; int /*<<< orphan*/  weaponchange_time; int /*<<< orphan*/  inventory; int /*<<< orphan*/  ws; TYPE_1__ cur_ps; } ;
typedef  TYPE_2__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FloatTime () ; 
 scalar_t__ WEAPON_DROPPING ; 
 scalar_t__ WEAPON_RAISING ; 
 int trap_BotChooseBestFightWeapon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_SelectWeapon (int /*<<< orphan*/ ,int) ; 

void BotChooseWeapon(bot_state_t *bs) {
	int newweaponnum;

	if (bs->cur_ps.weaponstate == WEAPON_RAISING ||
			bs->cur_ps.weaponstate == WEAPON_DROPPING) {
		trap_EA_SelectWeapon(bs->client, bs->weaponnum);
	}
	else {
		newweaponnum = trap_BotChooseBestFightWeapon(bs->ws, bs->inventory);
		if (bs->weaponnum != newweaponnum) bs->weaponchange_time = FloatTime();
		bs->weaponnum = newweaponnum;
		//BotAI_Print(PRT_MESSAGE, "bs->weaponnum = %d\n", bs->weaponnum);
		trap_EA_SelectWeapon(bs->client, bs->weaponnum);
	}
}
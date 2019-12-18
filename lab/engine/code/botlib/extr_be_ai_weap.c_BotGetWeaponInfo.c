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
typedef  int /*<<< orphan*/  weaponinfo_t ;
typedef  int /*<<< orphan*/  bot_weaponstate_t ;
struct TYPE_2__ {int /*<<< orphan*/ * weaponinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotValidWeaponNumber (int) ; 
 int /*<<< orphan*/ * BotWeaponStateFromHandle (int) ; 
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* weaponconfig ; 

void BotGetWeaponInfo(int weaponstate, int weapon, weaponinfo_t *weaponinfo)
{
	bot_weaponstate_t *ws;

	if (!BotValidWeaponNumber(weapon)) return;
	ws = BotWeaponStateFromHandle(weaponstate);
	if (!ws) return;
	if (!weaponconfig) return;
	Com_Memcpy(weaponinfo, &weaponconfig->weaponinfo[weapon], sizeof(weaponinfo_t));
}
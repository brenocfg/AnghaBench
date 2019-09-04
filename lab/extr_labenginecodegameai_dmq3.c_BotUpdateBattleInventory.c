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
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {int* inventory; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 size_t ENEMY_HEIGHT ; 
 size_t ENEMY_HORIZONTAL_DIST ; 
 scalar_t__ VectorLength (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

void BotUpdateBattleInventory(bot_state_t *bs, int enemy) {
	vec3_t dir;
	aas_entityinfo_t entinfo;

	BotEntityInfo(enemy, &entinfo);
	VectorSubtract(entinfo.origin, bs->origin, dir);
	bs->inventory[ENEMY_HEIGHT] = (int) dir[2];
	dir[2] = 0;
	bs->inventory[ENEMY_HORIZONTAL_DIST] = (int) VectorLength(dir);
	//FIXME: add num visible enemies and num visible team mates to the inventory
}
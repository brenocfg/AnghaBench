#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int client; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  eye; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;
struct TYPE_10__ {int maxclients; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 float BotEntityVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ BotSameTeam (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EntityCarriesFlag (TYPE_2__*) ; 
 TYPE_3__ level ; 

int BotEnemyFlagCarrierVisible(bot_state_t *bs) {
	int i;
	float vis;
	aas_entityinfo_t entinfo;

	for (i = 0; i < level.maxclients; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if the flag carrier is on the same team
		if (BotSameTeam(bs, i))
			continue;
		//if the flag carrier is not visible
		vis = BotEntityVisible(bs->entitynum, bs->eye, bs->viewangles, 360, i);
		if (vis <= 0)
			continue;
		//
		return i;
	}
	return -1;
}
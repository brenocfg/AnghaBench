#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {int /*<<< orphan*/  cluster; } ;
typedef  TYPE_1__ aas_areainfo_t ;
struct TYPE_7__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*,...) ; 
 int BotPointAreaNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_2__ bot_testclusters ; 
 TYPE_2__ bot_testsolid ; 
 int /*<<< orphan*/  trap_AAS_AreaInfo (int,TYPE_1__*) ; 
 int /*<<< orphan*/  trap_AAS_Initialized () ; 
 int /*<<< orphan*/  trap_Cvar_Update (TYPE_2__*) ; 

void BotTestAAS(vec3_t origin) {
	int areanum;
	aas_areainfo_t info;

	trap_Cvar_Update(&bot_testsolid);
	trap_Cvar_Update(&bot_testclusters);
	if (bot_testsolid.integer) {
		if (!trap_AAS_Initialized()) return;
		areanum = BotPointAreaNum(origin);
		if (areanum) BotAI_Print(PRT_MESSAGE, "\rempty area");
		else BotAI_Print(PRT_MESSAGE, "\r^1SOLID area");
	}
	else if (bot_testclusters.integer) {
		if (!trap_AAS_Initialized()) return;
		areanum = BotPointAreaNum(origin);
		if (!areanum)
			BotAI_Print(PRT_MESSAGE, "\r^1Solid!                              ");
		else {
			trap_AAS_AreaInfo(areanum, &info);
			BotAI_Print(PRT_MESSAGE, "\rarea %d, cluster %d       ", areanum, info.cluster);
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bot_entitystate_t ;

/* Variables and functions */
 int AAS_UpdateEntity (int,int /*<<< orphan*/ *) ; 
 int BLERR_INVALIDENTITYNUMBER ; 
 int BLERR_LIBRARYNOTSETUP ; 
 int /*<<< orphan*/  BotLibSetup (char*) ; 
 int /*<<< orphan*/  ValidEntityNumber (int,char*) ; 

int Export_BotLibUpdateEntity(int ent, bot_entitystate_t *state)
{
	if (!BotLibSetup("BotUpdateEntity")) return BLERR_LIBRARYNOTSETUP;
	if (!ValidEntityNumber(ent, "BotUpdateEntity")) return BLERR_INVALIDENTITYNUMBER;

	return AAS_UpdateEntity(ent, state);
}
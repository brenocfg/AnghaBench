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
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int BLERR_CANNOTLOADWEAPONCONFIG ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  DumpWeaponConfig (int /*<<< orphan*/ ) ; 
 char* LibVarString (char*,char*) ; 
 int /*<<< orphan*/  LoadWeaponConfig (char*) ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  weaponconfig ; 

int BotSetupWeaponAI(void)
{
	char *file;

	file = LibVarString("weaponconfig", "weapons.c");
	weaponconfig = LoadWeaponConfig(file);
	if (!weaponconfig)
	{
		botimport.Print(PRT_FATAL, "couldn't load the weapon config\n");
		return BLERR_CANNOTLOADWEAPONCONFIG;
	} //end if

#ifdef DEBUG_AI_WEAP
	DumpWeaponConfig(weaponconfig);
#endif //DEBUG_AI_WEAP
	//
	return BLERR_NOERROR;
}
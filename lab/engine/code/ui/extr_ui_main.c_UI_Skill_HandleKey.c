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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int UI_SelectForKey (int) ; 
 int numSkillLevels ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 int trap_Cvar_VariableValue (char*) ; 

__attribute__((used)) static qboolean UI_Skill_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		int i = trap_Cvar_VariableValue( "g_spSkill" );

		i += select;

		if (i < 1) {
			i = numSkillLevels;
		} else if (i > numSkillLevels) {
			i = 1;
		}

		trap_Cvar_SetValue("g_spSkill", i);
		return qtrue;
	}
	return qfalse;
}
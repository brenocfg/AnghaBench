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
 int Com_Clamp (int,int,int /*<<< orphan*/ ) ; 
 int UI_SelectForKey (int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  trap_Cvar_VariableValue (char*) ; 

__attribute__((used)) static qboolean UI_Handicap_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		int h;

		h = Com_Clamp( 5, 100, trap_Cvar_VariableValue("handicap") );
		h += 5 * select;

		if (h > 100) {
			h = 5;
		} else if (h < 5) {
			h = 100;
		}

		trap_Cvar_SetValue( "handicap", h );
		return qtrue;
	}
	return qfalse;
}
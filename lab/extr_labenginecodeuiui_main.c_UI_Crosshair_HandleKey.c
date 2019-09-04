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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {scalar_t__ currentCrosshair; } ;

/* Variables and functions */
 scalar_t__ NUM_CROSSHAIRS ; 
 int UI_SelectForKey (int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,scalar_t__) ; 
 TYPE_1__ uiInfo ; 

__attribute__((used)) static qboolean UI_Crosshair_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		uiInfo.currentCrosshair += select;

		if (uiInfo.currentCrosshair >= NUM_CROSSHAIRS) {
			uiInfo.currentCrosshair = 0;
		} else if (uiInfo.currentCrosshair < 0) {
			uiInfo.currentCrosshair = NUM_CROSSHAIRS - 1;
		}
		trap_Cvar_SetValue("cg_drawCrosshair", uiInfo.currentCrosshair);
		return qtrue;
	}
	return qfalse;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ rectDef_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_11__ {int mapCount; TYPE_1__* mapList; } ;
struct TYPE_10__ {int integer; } ;
struct TYPE_9__ {int integer; } ;
struct TYPE_7__ {int /*<<< orphan*/  mapName; } ;

/* Variables and functions */
 int /*<<< orphan*/  Text_Paint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ uiInfo ; 
 TYPE_4__ ui_currentMap ; 
 TYPE_3__ ui_currentNetMap ; 

__attribute__((used)) static void UI_DrawAllMapsSelection(rectDef_t *rect, float scale, vec4_t color, int textStyle, qboolean net) {
	int map = (net) ? ui_currentNetMap.integer : ui_currentMap.integer;
	if (map >= 0 && map < uiInfo.mapCount) {
	  Text_Paint(rect->x, rect->y, scale, color, uiInfo.mapList[map].mapName, 0, 0, textStyle);
	}
}
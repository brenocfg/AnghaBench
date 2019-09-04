#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rectDef_t ;
struct TYPE_5__ {scalar_t__ redBlue; } ;

/* Variables and functions */
 int /*<<< orphan*/  Text_Paint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static void UI_DrawRedBlue(rectDef_t *rect, float scale, vec4_t color, int textStyle) {
  Text_Paint(rect->x, rect->y, scale, color, (uiInfo.redBlue == 0) ? "Red" : "Blue", 0, 0, textStyle);
}
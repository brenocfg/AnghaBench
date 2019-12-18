#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ rectDef_t ;
struct TYPE_6__ {int /*<<< orphan*/ * fxPic; int /*<<< orphan*/  fxBasePic; } ;
struct TYPE_7__ {TYPE_1__ Assets; } ;
struct TYPE_9__ {int effectsColor; TYPE_2__ uiDC; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_DrawHandlePic (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ uiInfo ; 

__attribute__((used)) static void UI_DrawEffects(rectDef_t *rect, float scale, vec4_t color) {
	UI_DrawHandlePic( rect->x, rect->y - 14, 128, 8, uiInfo.uiDC.Assets.fxBasePic );
	UI_DrawHandlePic( rect->x + uiInfo.effectsColor * 16 + 8, rect->y - 16, 16, 12, uiInfo.uiDC.Assets.fxPic[uiInfo.effectsColor] );
}
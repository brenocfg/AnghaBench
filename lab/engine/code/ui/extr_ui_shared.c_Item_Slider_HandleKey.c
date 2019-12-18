#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float x; float w; } ;
typedef  TYPE_3__ rectDef_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_10__ {int flags; TYPE_3__ rect; } ;
struct TYPE_9__ {int x; int w; } ;
struct TYPE_12__ {scalar_t__ cvar; TYPE_5__* typeData; TYPE_2__ window; TYPE_1__ textRect; scalar_t__ text; } ;
typedef  TYPE_4__ itemDef_t ;
struct TYPE_13__ {float maxVal; float minVal; } ;
typedef  TYPE_5__ editFieldDef_t ;
struct TYPE_14__ {float cursorx; int (* getCVarValue ) (scalar_t__) ;int /*<<< orphan*/  (* Print ) (char*) ;int /*<<< orphan*/  (* setCVar ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cursory; } ;

/* Variables and functions */
 TYPE_8__* DC ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int K_MOUSE3 ; 
 scalar_t__ Rect_ContainsPoint (TYPE_3__*,float,int /*<<< orphan*/ ) ; 
 scalar_t__ SLIDER_THUMB_WIDTH ; 
 float SLIDER_WIDTH ; 
 int UI_SelectForKey (int) ; 
 int WINDOW_HASFOCUS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*) ; 
 int /*<<< orphan*/  va (char*,float) ; 

qboolean Item_Slider_HandleKey(itemDef_t *item, int key, qboolean down) {
	float x, value, width, work;

	//DC->Print("slider handle key\n");
	if (item->cvar) {
		if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3) {
			editFieldDef_t *editDef = item->typeData;
			if (editDef && Rect_ContainsPoint(&item->window.rect, DC->cursorx, DC->cursory) && item->window.flags & WINDOW_HASFOCUS) {
				rectDef_t testRect;
				width = SLIDER_WIDTH;
				if (item->text) {
					x = item->textRect.x + item->textRect.w + 8;
				} else {
					x = item->window.rect.x;
				}

				testRect = item->window.rect;
				testRect.x = x;
				value = (float)SLIDER_THUMB_WIDTH / 2;
				testRect.x -= value;
				//DC->Print("slider x: %f\n", testRect.x);
				testRect.w = (SLIDER_WIDTH + (float)SLIDER_THUMB_WIDTH / 2);
				//DC->Print("slider w: %f\n", testRect.w);
				if (Rect_ContainsPoint(&testRect, DC->cursorx, DC->cursory)) {
					work = DC->cursorx - x;
					value = work / width;
					value *= (editDef->maxVal - editDef->minVal);
					// vm fuckage
					// value = (((float)(DC->cursorx - x)/ SLIDER_WIDTH) * (editDef->maxVal - editDef->minVal));
					value += editDef->minVal;
					DC->setCVar(item->cvar, va("%f", value));
					return qtrue;
				}
			}
		} else {
			int select = UI_SelectForKey(key);
			if (select != 0) {
				editFieldDef_t *editDef = item->typeData;
				if (editDef) {
					// 20 is number of steps
					value = DC->getCVarValue(item->cvar) + (((editDef->maxVal - editDef->minVal)/20) * select);

					if (value < editDef->minVal)
						value = editDef->minVal;
					else if (value > editDef->maxVal)
						value = editDef->maxVal;

					DC->setCVar(item->cvar, va("%f", value));
					return qtrue;
				}
			}
		}
	}
	DC->Print("slider handle key exit\n");
	return qfalse;
}
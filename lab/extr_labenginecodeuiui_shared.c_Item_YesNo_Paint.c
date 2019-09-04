#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec4_t ;
struct TYPE_10__ {double* focusColor; } ;
typedef  TYPE_3__ menuDef_t ;
struct TYPE_9__ {int /*<<< orphan*/  y; scalar_t__ x; scalar_t__ w; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  foreColor; } ;
struct TYPE_11__ {int /*<<< orphan*/  textStyle; int /*<<< orphan*/  textscale; TYPE_2__ textRect; scalar_t__ text; TYPE_1__ window; scalar_t__ cvar; scalar_t__ parent; } ;
typedef  TYPE_4__ itemDef_t ;
struct TYPE_12__ {float (* getCVarValue ) (scalar_t__) ;int realTime; int /*<<< orphan*/  (* drawText ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_7__* DC ; 
 int /*<<< orphan*/  Item_Text_Paint (TYPE_4__*) ; 
 int /*<<< orphan*/  LerpColor (double*,double*,double*,double) ; 
 int PULSE_DIVISOR ; 
 int WINDOW_HASFOCUS ; 
 int /*<<< orphan*/  memcpy (double**,int /*<<< orphan*/ *,int) ; 
 double sin (int) ; 
 float stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Item_YesNo_Paint(itemDef_t *item) {
	vec4_t newColor, lowLight;
	float value;
	menuDef_t *parent = (menuDef_t*)item->parent;

	value = (item->cvar) ? DC->getCVarValue(item->cvar) : 0;

	if (item->window.flags & WINDOW_HASFOCUS) {
		lowLight[0] = 0.8 * parent->focusColor[0]; 
		lowLight[1] = 0.8 * parent->focusColor[1]; 
		lowLight[2] = 0.8 * parent->focusColor[2]; 
		lowLight[3] = 0.8 * parent->focusColor[3]; 
		LerpColor(parent->focusColor,lowLight,newColor,0.5+0.5*sin(DC->realTime / PULSE_DIVISOR));
	} else {
		memcpy(&newColor, &item->window.foreColor, sizeof(vec4_t));
	}

	if (item->text) {
		Item_Text_Paint(item);
		DC->drawText(item->textRect.x + item->textRect.w + 8, item->textRect.y, item->textscale, newColor, (value != 0) ? "Yes" : "No", 0, 0, item->textStyle);
	} else {
		DC->drawText(item->textRect.x, item->textRect.y, item->textscale, newColor, (value != 0) ? "Yes" : "No", 0, 0, item->textStyle);
	}
}
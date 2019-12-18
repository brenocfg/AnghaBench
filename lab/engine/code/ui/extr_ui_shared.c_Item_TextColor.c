#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec4_t ;
struct TYPE_8__ {double* focusColor; double* disableColor; int /*<<< orphan*/  fadeAmount; int /*<<< orphan*/  fadeCycle; int /*<<< orphan*/  fadeClamp; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_7__ {int flags; double* foreColor; int /*<<< orphan*/  nextTime; } ;
struct TYPE_9__ {scalar_t__ textStyle; int cvarFlags; scalar_t__* cvarTest; scalar_t__* enableCvar; TYPE_1__ window; scalar_t__ parent; } ;
typedef  TYPE_3__ itemDef_t ;
struct TYPE_10__ {int realTime; } ;

/* Variables and functions */
 int BLINK_DIVISOR ; 
 int CVAR_DISABLE ; 
 int CVAR_ENABLE ; 
 TYPE_6__* DC ; 
 int /*<<< orphan*/  Fade (int*,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ITEM_TEXTSTYLE_BLINK ; 
 int /*<<< orphan*/  Item_EnableShowViaCvar (TYPE_3__*,int) ; 
 int /*<<< orphan*/  LerpColor (double*,double*,double*,double) ; 
 int PULSE_DIVISOR ; 
 int WINDOW_HASFOCUS ; 
 int /*<<< orphan*/  memcpy (double**,double**,int) ; 
 int /*<<< orphan*/  qtrue ; 
 double sin (int) ; 

void Item_TextColor(itemDef_t *item, vec4_t *newColor) {
	vec4_t lowLight;
	menuDef_t *parent = (menuDef_t*)item->parent;

	Fade(&item->window.flags, &item->window.foreColor[3], parent->fadeClamp, &item->window.nextTime, parent->fadeCycle, qtrue, parent->fadeAmount);

	if (item->window.flags & WINDOW_HASFOCUS) {
		lowLight[0] = 0.8 * parent->focusColor[0]; 
		lowLight[1] = 0.8 * parent->focusColor[1]; 
		lowLight[2] = 0.8 * parent->focusColor[2]; 
		lowLight[3] = 0.8 * parent->focusColor[3]; 
		LerpColor(parent->focusColor,lowLight,*newColor,0.5+0.5*sin(DC->realTime / PULSE_DIVISOR));
	} else if (item->textStyle == ITEM_TEXTSTYLE_BLINK && !((DC->realTime/BLINK_DIVISOR) & 1)) {
		lowLight[0] = 0.8 * item->window.foreColor[0]; 
		lowLight[1] = 0.8 * item->window.foreColor[1]; 
		lowLight[2] = 0.8 * item->window.foreColor[2]; 
		lowLight[3] = 0.8 * item->window.foreColor[3]; 
		LerpColor(item->window.foreColor,lowLight,*newColor,0.5+0.5*sin(DC->realTime / PULSE_DIVISOR));
	} else {
		memcpy(newColor, &item->window.foreColor, sizeof(vec4_t));
		// items can be enabled and disabled based on cvars
	}

	if (item->enableCvar && *item->enableCvar && item->cvarTest && *item->cvarTest) {
		if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
			memcpy(newColor, &parent->disableColor, sizeof(vec4_t));
		}
	}
}
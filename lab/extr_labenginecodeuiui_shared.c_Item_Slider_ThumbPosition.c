#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float x; } ;
struct TYPE_10__ {TYPE_2__ rect; } ;
struct TYPE_8__ {int x; int w; } ;
struct TYPE_11__ {int /*<<< orphan*/  cvar; TYPE_3__ window; TYPE_1__ textRect; scalar_t__ text; TYPE_5__* typeData; } ;
typedef  TYPE_4__ itemDef_t ;
struct TYPE_12__ {float minVal; float maxVal; } ;
typedef  TYPE_5__ editFieldDef_t ;
struct TYPE_13__ {float (* getCVarValue ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_7__* DC ; 
 float SLIDER_WIDTH ; 
 float stub1 (int /*<<< orphan*/ ) ; 

float Item_Slider_ThumbPosition(itemDef_t *item) {
	float value, range, x;
	editFieldDef_t *editDef = item->typeData;

	if (item->text) {
		x = item->textRect.x + item->textRect.w + 8;
	} else {
		x = item->window.rect.x;
	}

	if (!editDef || !item->cvar) {
		return x;
	}

	value = DC->getCVarValue(item->cvar);

	if (value < editDef->minVal) {
		value = editDef->minVal;
	} else if (value > editDef->maxVal) {
		value = editDef->maxVal;
	}

	range = editDef->maxVal - editDef->minVal;
	value -= editDef->minVal;
	value /= range;
	//value /= (editDef->maxVal - editDef->minVal);
	value *= SLIDER_WIDTH;
	x += value;
	// vm fuckage
	//x = x + (((float)value / editDef->maxVal) * SLIDER_WIDTH);
	return x;
}
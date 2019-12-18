#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int w; int /*<<< orphan*/  h; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ rectDef_t ;
struct TYPE_8__ {scalar_t__ y; } ;
struct TYPE_9__ {TYPE_1__ rect; } ;
struct TYPE_11__ {TYPE_2__ window; } ;
typedef  TYPE_4__ itemDef_t ;

/* Variables and functions */
 scalar_t__ Item_Slider_ThumbPosition (TYPE_4__*) ; 
 scalar_t__ Rect_ContainsPoint (TYPE_3__*,float,float) ; 
 int /*<<< orphan*/  SLIDER_THUMB_HEIGHT ; 
 int SLIDER_THUMB_WIDTH ; 
 int WINDOW_LB_THUMB ; 

int Item_Slider_OverSlider(itemDef_t *item, float x, float y) {
	rectDef_t r;

	r.x = Item_Slider_ThumbPosition(item) - (SLIDER_THUMB_WIDTH / 2);
	r.y = item->window.rect.y - 2;
	r.w = SLIDER_THUMB_WIDTH;
	r.h = SLIDER_THUMB_HEIGHT;

	if (Rect_ContainsPoint(&r, x, y)) {
		return WINDOW_LB_THUMB;
	}
	return 0;
}
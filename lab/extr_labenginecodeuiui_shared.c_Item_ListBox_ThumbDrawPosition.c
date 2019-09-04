#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int w; int y; int h; } ;
struct TYPE_9__ {int flags; TYPE_1__ rect; } ;
struct TYPE_10__ {TYPE_2__ window; } ;
typedef  TYPE_3__ itemDef_t ;
struct TYPE_11__ {int cursorx; int cursory; } ;

/* Variables and functions */
 TYPE_7__* DC ; 
 int Item_ListBox_ThumbPosition (TYPE_3__*) ; 
 int SCROLLBAR_SIZE ; 
 int WINDOW_HORIZONTAL ; 
 TYPE_3__* itemCapture ; 

int Item_ListBox_ThumbDrawPosition(itemDef_t *item) {
	int min, max;

	if (itemCapture == item) {
		if (item->window.flags & WINDOW_HORIZONTAL) {
			min = item->window.rect.x + SCROLLBAR_SIZE + 1;
			max = item->window.rect.x + item->window.rect.w - 2*SCROLLBAR_SIZE - 1;
			if (DC->cursorx >= min + SCROLLBAR_SIZE/2 && DC->cursorx <= max + SCROLLBAR_SIZE/2) {
				return DC->cursorx - SCROLLBAR_SIZE/2;
			}
			else {
				return Item_ListBox_ThumbPosition(item);
			}
		}
		else {
			min = item->window.rect.y + SCROLLBAR_SIZE + 1;
			max = item->window.rect.y + item->window.rect.h - 2*SCROLLBAR_SIZE - 1;
			if (DC->cursory >= min + SCROLLBAR_SIZE/2 && DC->cursory <= max + SCROLLBAR_SIZE/2) {
				return DC->cursory - SCROLLBAR_SIZE/2;
			}
			else {
				return Item_ListBox_ThumbPosition(item);
			}
		}
	}
	else {
		return Item_ListBox_ThumbPosition(item);
	}
}
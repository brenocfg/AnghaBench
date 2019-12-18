#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float x; float y; void* h; void* w; } ;
typedef  TYPE_3__ rectDef_t ;
struct TYPE_12__ {scalar_t__ elementStyle; void* drawPadding; scalar_t__ cursorPos; float elementWidth; scalar_t__ startPos; scalar_t__ endPos; float elementHeight; } ;
typedef  TYPE_4__ listBoxDef_t ;
struct TYPE_9__ {float x; float y; void* h; void* w; } ;
struct TYPE_10__ {int flags; TYPE_1__ rect; } ;
struct TYPE_13__ {TYPE_2__ window; scalar_t__ typeData; } ;
typedef  TYPE_5__ itemDef_t ;

/* Variables and functions */
 int Item_ListBox_OverLB (TYPE_5__*,float,float) ; 
 scalar_t__ LISTBOX_IMAGE ; 
 scalar_t__ Rect_ContainsPoint (TYPE_3__*,float,float) ; 
 void* SCROLLBAR_SIZE ; 
 int WINDOW_HORIZONTAL ; 
 int WINDOW_LB_LEFTARROW ; 
 int WINDOW_LB_PGDN ; 
 int WINDOW_LB_PGUP ; 
 int WINDOW_LB_RIGHTARROW ; 
 int WINDOW_LB_THUMB ; 

void Item_ListBox_MouseEnter(itemDef_t *item, float x, float y) 
{
	rectDef_t r;
	listBoxDef_t *listPtr = (listBoxDef_t*)item->typeData;
        
	item->window.flags &= ~(WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW | WINDOW_LB_THUMB | WINDOW_LB_PGUP | WINDOW_LB_PGDN);
	item->window.flags |= Item_ListBox_OverLB(item, x, y);

	if (item->window.flags & WINDOW_HORIZONTAL) {
		if (!(item->window.flags & (WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW | WINDOW_LB_THUMB | WINDOW_LB_PGUP | WINDOW_LB_PGDN))) {
			// check for selection hit as we have exausted buttons and thumb
			if (listPtr->elementStyle == LISTBOX_IMAGE) {
				r.x = item->window.rect.x;
				r.y = item->window.rect.y;
				r.h = item->window.rect.h - SCROLLBAR_SIZE;
				r.w = item->window.rect.w - listPtr->drawPadding;
				if (Rect_ContainsPoint(&r, x, y)) {
					listPtr->cursorPos =  (int)((x - r.x) / listPtr->elementWidth)  + listPtr->startPos;
					if (listPtr->cursorPos >= listPtr->endPos) {
						listPtr->cursorPos = listPtr->endPos;
					}
				}
			} else {
				// text hit.. 
			}
		}
	} else if (!(item->window.flags & (WINDOW_LB_LEFTARROW | WINDOW_LB_RIGHTARROW | WINDOW_LB_THUMB | WINDOW_LB_PGUP | WINDOW_LB_PGDN))) {
		r.x = item->window.rect.x;
		r.y = item->window.rect.y;
		r.w = item->window.rect.w - SCROLLBAR_SIZE;
		r.h = item->window.rect.h - listPtr->drawPadding;
		if (Rect_ContainsPoint(&r, x, y)) {
			listPtr->cursorPos =  (int)((y - 2 - r.y) / listPtr->elementHeight)  + listPtr->startPos;
			if (listPtr->cursorPos > listPtr->endPos) {
				listPtr->cursorPos = listPtr->endPos;
			}
		}
	}
}
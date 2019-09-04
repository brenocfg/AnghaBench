#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ xStart; scalar_t__ yStart; scalar_t__ nextScrollTime; scalar_t__ adjustValue; scalar_t__ nextAdjustTime; int /*<<< orphan*/  scrollKey; TYPE_6__* item; } ;
typedef  TYPE_3__ scrollInfo_t ;
struct TYPE_12__ {int x; int y; int h; int w; } ;
typedef  TYPE_4__ rectDef_t ;
struct TYPE_13__ {int startPos; } ;
typedef  TYPE_5__ listBoxDef_t ;
struct TYPE_15__ {scalar_t__ cursorx; scalar_t__ cursory; scalar_t__ realTime; } ;
struct TYPE_9__ {int x; int y; int h; int w; } ;
struct TYPE_10__ {int flags; TYPE_1__ rect; } ;
struct TYPE_14__ {TYPE_2__ window; scalar_t__ typeData; } ;

/* Variables and functions */
 TYPE_8__* DC ; 
 int /*<<< orphan*/  Item_ListBox_HandleKey (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Item_ListBox_MaxScroll (TYPE_6__*) ; 
 int SCROLLBAR_SIZE ; 
 scalar_t__ SCROLL_TIME_ADJUST ; 
 scalar_t__ SCROLL_TIME_ADJUSTOFFSET ; 
 scalar_t__ SCROLL_TIME_FLOOR ; 
 int WINDOW_HORIZONTAL ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void Scroll_ListBox_ThumbFunc(void *p) {
	scrollInfo_t *si = (scrollInfo_t*)p;
	rectDef_t r;
	int pos, max;

	listBoxDef_t *listPtr = (listBoxDef_t*)si->item->typeData;
	if (si->item->window.flags & WINDOW_HORIZONTAL) {
		if (DC->cursorx == si->xStart) {
			return;
		}
		r.x = si->item->window.rect.x + SCROLLBAR_SIZE + 1;
		r.y = si->item->window.rect.y + si->item->window.rect.h - SCROLLBAR_SIZE - 1;
		r.h = SCROLLBAR_SIZE;
		r.w = si->item->window.rect.w - (SCROLLBAR_SIZE*2) - 2;
		max = Item_ListBox_MaxScroll(si->item);
		//
		pos = (DC->cursorx - r.x - SCROLLBAR_SIZE/2) * max / (r.w - SCROLLBAR_SIZE);
		if (pos < 0) {
			pos = 0;
		}
		else if (pos > max) {
			pos = max;
		}
		listPtr->startPos = pos;
		si->xStart = DC->cursorx;
	}
	else if (DC->cursory != si->yStart) {

		r.x = si->item->window.rect.x + si->item->window.rect.w - SCROLLBAR_SIZE - 1;
		r.y = si->item->window.rect.y + SCROLLBAR_SIZE + 1;
		r.h = si->item->window.rect.h - (SCROLLBAR_SIZE*2) - 2;
		r.w = SCROLLBAR_SIZE;
		max = Item_ListBox_MaxScroll(si->item);
		//
		pos = (DC->cursory - r.y - SCROLLBAR_SIZE/2) * max / (r.h - SCROLLBAR_SIZE);
		if (pos < 0) {
			pos = 0;
		}
		else if (pos > max) {
			pos = max;
		}
		listPtr->startPos = pos;
		si->yStart = DC->cursory;
	}

	if (DC->realTime > si->nextScrollTime) { 
		// need to scroll which is done by simulating a click to the item
		// this is done a bit sideways as the autoscroll "knows" that the item is a listbox
		// so it calls it directly
		Item_ListBox_HandleKey(si->item, si->scrollKey, qtrue, qfalse);
		si->nextScrollTime = DC->realTime + si->adjustValue; 
	}

	if (DC->realTime > si->nextAdjustTime) {
		si->nextAdjustTime = DC->realTime + SCROLL_TIME_ADJUST;
		if (si->adjustValue > SCROLL_TIME_FLOOR) {
			si->adjustValue -= SCROLL_TIME_ADJUSTOFFSET;
		}
	}
}
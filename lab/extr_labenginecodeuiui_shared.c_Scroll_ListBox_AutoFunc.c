#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nextScrollTime; scalar_t__ adjustValue; scalar_t__ nextAdjustTime; int /*<<< orphan*/  scrollKey; int /*<<< orphan*/  item; } ;
typedef  TYPE_1__ scrollInfo_t ;
struct TYPE_4__ {scalar_t__ realTime; } ;

/* Variables and functions */
 TYPE_2__* DC ; 
 int /*<<< orphan*/  Item_ListBox_HandleKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCROLL_TIME_ADJUST ; 
 scalar_t__ SCROLL_TIME_ADJUSTOFFSET ; 
 scalar_t__ SCROLL_TIME_FLOOR ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void Scroll_ListBox_AutoFunc(void *p) {
	scrollInfo_t *si = (scrollInfo_t*)p;
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
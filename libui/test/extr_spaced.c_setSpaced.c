#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; void* ptr; } ;

/* Variables and functions */
#define  box 133 
#define  form 132 
#define  grid 131 
#define  group 130 
 size_t len ; 
#define  tab 129 
 TYPE_1__* things ; 
 int /*<<< orphan*/  uiBox (void*) ; 
 int /*<<< orphan*/  uiBoxSetPadded (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiForm (void*) ; 
 int /*<<< orphan*/  uiFormSetPadded (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiGrid (void*) ; 
 int /*<<< orphan*/  uiGridSetPadded (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiGroup (void*) ; 
 int /*<<< orphan*/  uiGroupSetMargined (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiTab (void*) ; 
 size_t uiTabNumPages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTabSetMargined (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  uiWindow (void*) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ ,int) ; 
#define  window 128 

void setSpaced(int spaced)
{
	size_t i;
	void *p;
	size_t j, n;

	for (i = 0; i < len; i++) {
		p = things[i].ptr;
		switch (things[i].type) {
		case window:
			uiWindowSetMargined(uiWindow(p), spaced);
			break;
		case box:
			uiBoxSetPadded(uiBox(p), spaced);
			break;
		case tab:
			n = uiTabNumPages(uiTab(p));
			for (j = 0; j < n; j++)
				uiTabSetMargined(uiTab(p), j, spaced);
			break;
		case group:
			uiGroupSetMargined(uiGroup(p), spaced);
			break;
		case form:
			uiFormSetPadded(uiForm(p), spaced);
			break;
		case grid:
			uiGridSetPadded(uiGrid(p), spaced);
			break;
		}
	}
}
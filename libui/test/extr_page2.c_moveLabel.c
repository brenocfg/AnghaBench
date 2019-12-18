#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 int /*<<< orphan*/ * movingBoxes ; 
 int movingCurrent ; 
 int /*<<< orphan*/  movingLabel ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiBoxDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void moveLabel(uiButton *b, void *data)
{
	int from, to;

	from = movingCurrent;
	to = 0;
	if (from == 0)
		to = 1;
	uiBoxDelete(movingBoxes[from], 0);
	uiBoxAppend(movingBoxes[to], uiControl(movingLabel), 0);
	movingCurrent = to;
}
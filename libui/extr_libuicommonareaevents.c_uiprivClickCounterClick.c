#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int curButton; int count; int rectX0; int rectY0; int rectX1; int rectY1; uintptr_t prevTime; } ;
typedef  TYPE_1__ uiprivClickCounter ;
typedef  int int32_t ;

/* Variables and functions */

int uiprivClickCounterClick(uiprivClickCounter *c, int button, int x, int y, uintptr_t time, uintptr_t maxTime, int32_t xdist, int32_t ydist)
{
	// different button than before? if so, don't count
	if (button != c->curButton)
		c->count = 0;

	// (x, y) in the allowed region for a double-click? if not, don't count
	if (x < c->rectX0)
		c->count = 0;
	if (y < c->rectY0)
		c->count = 0;
	if (x >= c->rectX1)
		c->count = 0;
	if (y >= c->rectY1)
		c->count = 0;

	// too slow? if so, don't count
	// note the below expression; time > (c.prevTime + maxTime) can overflow!
	if ((time - c->prevTime) > maxTime)	// too slow; don't count
		c->count = 0;

	c->count++;		// if either of the above ifs happened, this will make the click count 1; otherwise it will make the click count 2, 3, 4, 5, ...

	// now we need to update the internal structures for the next test
	c->curButton = button;
	c->prevTime = time;
	c->rectX0 = x - xdist;
	c->rectY0 = y - ydist;
	c->rectX1 = x + xdist;
	c->rectY1 = y + ydist;

	return c->count;
}
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
struct TYPE_3__ {int xsize; int ysize; int xpos; int ypos; int cursor_pos; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */

void
sc_move_cursor(scr_stat *scp, int x, int y)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= scp->xsize)
		x = scp->xsize - 1;
	if (y >= scp->ysize)
		y = scp->ysize - 1;
	scp->xpos = x;
	scp->ypos = y;
	scp->cursor_pos = scp->ypos*scp->xsize + scp->xpos;
}
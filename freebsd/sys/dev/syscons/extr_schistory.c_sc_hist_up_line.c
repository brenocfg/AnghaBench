#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int xsize; int ysize; scalar_t__ history_pos; int /*<<< orphan*/  history; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  history_to_screen (TYPE_1__*) ; 
 scalar_t__ sc_vtb_pos (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ sc_vtb_tail (int /*<<< orphan*/ ) ; 

int
sc_hist_up_line(scr_stat *scp)
{
	if (sc_vtb_pos(scp->history, scp->history_pos, -(scp->xsize*scp->ysize))
	    == sc_vtb_tail(scp->history))
		return -1;
	scp->history_pos = sc_vtb_pos(scp->history, scp->history_pos,
				      -scp->xsize);
	history_to_screen(scp);
	return 0;
}
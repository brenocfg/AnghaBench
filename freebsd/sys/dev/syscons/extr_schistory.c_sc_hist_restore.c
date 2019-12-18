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
struct TYPE_4__ {scalar_t__ history_pos; int xsize; int ysize; int /*<<< orphan*/  history; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  history_to_screen (TYPE_1__*) ; 
 int /*<<< orphan*/  sc_vtb_pos (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sc_vtb_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_vtb_tail (int /*<<< orphan*/ ) ; 

int
sc_hist_restore(scr_stat *scp)
{
	int ret;

	if (scp->history_pos != sc_vtb_tail(scp->history)) {
		scp->history_pos = sc_vtb_tail(scp->history);
		history_to_screen(scp);
		ret =  0;
	} else {
		ret = 1;
	}
	sc_vtb_seek(scp->history, sc_vtb_pos(scp->history, 
					     sc_vtb_tail(scp->history),
					     -scp->xsize*scp->ysize));
	return ret;
}
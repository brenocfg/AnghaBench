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
struct TYPE_4__ {int mouse_cut_end; int mouse_cut_start; int xsize; int ysize; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_CUTTING ; 
 int /*<<< orphan*/  mark_for_update (TYPE_1__*,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

void
sc_remove_cutmarking(scr_stat *scp)
{
    int s;

    s = spltty();
    if (scp->mouse_cut_end >= 0) {
	mark_for_update(scp, scp->mouse_cut_start);
	mark_for_update(scp, scp->mouse_cut_end);
    }
    scp->mouse_cut_start = scp->xsize*scp->ysize;
    scp->mouse_cut_end = -1;
    splx(s);
    scp->status &= ~MOUSE_CUTTING;
}
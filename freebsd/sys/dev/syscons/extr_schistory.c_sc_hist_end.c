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
struct TYPE_4__ {int xsize; int ysize; int /*<<< orphan*/  history; int /*<<< orphan*/  history_pos; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  history_to_screen (TYPE_1__*) ; 
 int /*<<< orphan*/  sc_vtb_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc_vtb_tail (int /*<<< orphan*/ ) ; 

void
sc_hist_end(scr_stat *scp)
{
	scp->history_pos = sc_vtb_pos(scp->history, sc_vtb_tail(scp->history),
				      scp->xsize*scp->ysize);
	history_to_screen(scp);
}
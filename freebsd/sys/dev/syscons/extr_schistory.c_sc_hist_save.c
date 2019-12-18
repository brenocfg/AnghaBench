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
struct TYPE_3__ {int xsize; int ysize; int /*<<< orphan*/  history; int /*<<< orphan*/  history_pos; int /*<<< orphan*/  vtb; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  sc_vtb_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc_vtb_tail (int /*<<< orphan*/ ) ; 

void
sc_hist_save(scr_stat *scp)
{
	sc_vtb_append(&scp->vtb, 0, scp->history, scp->xsize*scp->ysize);
	scp->history_pos = sc_vtb_tail(scp->history);
}
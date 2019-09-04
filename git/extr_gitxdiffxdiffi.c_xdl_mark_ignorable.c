#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ xrecord_t ;
struct TYPE_9__ {TYPE_3__** recs; } ;
struct TYPE_8__ {TYPE_3__** recs; } ;
struct TYPE_11__ {TYPE_2__ xdf2; TYPE_1__ xdf1; } ;
typedef  TYPE_4__ xdfenv_t ;
struct TYPE_12__ {size_t i1; long chg1; size_t i2; long chg2; int ignore; struct TYPE_12__* next; } ;
typedef  TYPE_5__ xdchange_t ;

/* Variables and functions */
 int xdl_blankline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void xdl_mark_ignorable(xdchange_t *xscr, xdfenv_t *xe, long flags)
{
	xdchange_t *xch;

	for (xch = xscr; xch; xch = xch->next) {
		int ignore = 1;
		xrecord_t **rec;
		long i;

		rec = &xe->xdf1.recs[xch->i1];
		for (i = 0; i < xch->chg1 && ignore; i++)
			ignore = xdl_blankline(rec[i]->ptr, rec[i]->size, flags);

		rec = &xe->xdf2.recs[xch->i2];
		for (i = 0; i < xch->chg2 && ignore; i++)
			ignore = xdl_blankline(rec[i]->ptr, rec[i]->size, flags);

		xch->ignore = ignore;
	}
}
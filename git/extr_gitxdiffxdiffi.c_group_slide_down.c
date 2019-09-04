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
struct TYPE_3__ {size_t nrec; int* rchg; int /*<<< orphan*/ * recs; } ;
typedef  TYPE_1__ xdfile_t ;
struct xdlgroup {size_t end; size_t start; } ;

/* Variables and functions */
 scalar_t__ recs_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int group_slide_down(xdfile_t *xdf, struct xdlgroup *g, long flags)
{
	if (g->end < xdf->nrec &&
	    recs_match(xdf->recs[g->start], xdf->recs[g->end], flags)) {
		xdf->rchg[g->start++] = 0;
		xdf->rchg[g->end++] = 1;

		while (xdf->rchg[g->end])
			g->end++;

		return 0;
	} else {
		return -1;
	}
}
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
struct TYPE_3__ {int* rchg; int /*<<< orphan*/ * recs; } ;
typedef  TYPE_1__ xdfile_t ;
struct xdlgroup {int start; int end; } ;

/* Variables and functions */
 scalar_t__ recs_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int group_slide_up(xdfile_t *xdf, struct xdlgroup *g, long flags)
{
	if (g->start > 0 &&
	    recs_match(xdf->recs[g->start - 1], xdf->recs[g->end - 1], flags)) {
		xdf->rchg[--g->start] = 1;
		xdf->rchg[--g->end] = 0;

		while (xdf->rchg[g->start - 1])
			g->start--;

		return 0;
	} else {
		return -1;
	}
}
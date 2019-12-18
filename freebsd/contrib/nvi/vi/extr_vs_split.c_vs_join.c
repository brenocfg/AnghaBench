#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jdir_t ;
struct TYPE_9__ {int /*<<< orphan*/  dq; } ;
struct TYPE_8__ {size_t rows; scalar_t__ coff; size_t cols; scalar_t__ roff; TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;

/* Variables and functions */
 int /*<<< orphan*/  HORIZ_FOLLOW ; 
 int /*<<< orphan*/  HORIZ_PRECEDE ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERT_FOLLOW ; 
 int /*<<< orphan*/  VERT_PRECEDE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  q ; 

__attribute__((used)) static int
vs_join(SCR *sp, SCR **listp, jdir_t *jdirp)
{
	GS *gp;
	SCR **lp, *tsp;
	int first;
	size_t tlen;

	gp = sp->gp;

	/* Check preceding vertical. */
	for (lp = listp, tlen = sp->rows,
	    tsp = TAILQ_FIRST(gp->dq);
	    tsp != NULL; tsp = TAILQ_NEXT(tsp, q)) {
		if (sp == tsp)
			continue;
		/* Test if precedes the screen vertically. */
		if (tsp->coff + tsp->cols + 1 != sp->coff)
			continue;
		/*
		 * Test if a subset on the vertical axis.  If overlaps the
		 * beginning or end, we can't join on this axis at all.
		 */
		if (tsp->roff > sp->roff + sp->rows)
			continue;
		if (tsp->roff < sp->roff) {
			if (tsp->roff + tsp->rows >= sp->roff)
				break;
			continue;
		}
		if (tsp->roff + tsp->rows > sp->roff + sp->rows)
			break;
#ifdef DEBUG
		if (tlen < tsp->rows)
			abort();
#endif
		tlen -= tsp->rows;
		*lp++ = tsp;
	}
	if (tlen == 0) {
		*lp = NULL;
		*jdirp = VERT_PRECEDE;
		return (0);
	}

	/* Check following vertical. */
	for (lp = listp, tlen = sp->rows,
	    tsp = TAILQ_FIRST(gp->dq);
	    tsp != NULL; tsp = TAILQ_NEXT(tsp, q)) {
		if (sp == tsp)
			continue;
		/* Test if follows the screen vertically. */
		if (tsp->coff != sp->coff + sp->cols + 1)
			continue;
		/*
		 * Test if a subset on the vertical axis.  If overlaps the
		 * beginning or end, we can't join on this axis at all.
		 */
		if (tsp->roff > sp->roff + sp->rows)
			continue;
		if (tsp->roff < sp->roff) {
			if (tsp->roff + tsp->rows >= sp->roff)
				break;
			continue;
		}
		if (tsp->roff + tsp->rows > sp->roff + sp->rows)
			break;
#ifdef DEBUG
		if (tlen < tsp->rows)
			abort();
#endif
		tlen -= tsp->rows;
		*lp++ = tsp;
	}
	if (tlen == 0) {
		*lp = NULL;
		*jdirp = VERT_FOLLOW;
		return (0);
	}

	/* Check preceding horizontal. */
	for (first = 0, lp = listp, tlen = sp->cols,
	    tsp = TAILQ_FIRST(gp->dq);
	    tsp != NULL; tsp = TAILQ_NEXT(tsp, q)) {
		if (sp == tsp)
			continue;
		/* Test if precedes the screen horizontally. */
		if (tsp->roff + tsp->rows != sp->roff)
			continue;
		/*
		 * Test if a subset on the horizontal axis.  If overlaps the
		 * beginning or end, we can't join on this axis at all.
		 */
		if (tsp->coff > sp->coff + sp->cols)
			continue;
		if (tsp->coff < sp->coff) {
			if (tsp->coff + tsp->cols >= sp->coff)
				break;
			continue;
		}
		if (tsp->coff + tsp->cols > sp->coff + sp->cols)
			break;
#ifdef DEBUG
		if (tlen < tsp->cols)
			abort();
#endif
		tlen -= tsp->cols + first;
		first = 1;
		*lp++ = tsp;
	}
	if (tlen == 0) {
		*lp = NULL;
		*jdirp = HORIZ_PRECEDE;
		return (0);
	}

	/* Check following horizontal. */
	for (first = 0, lp = listp, tlen = sp->cols,
	    tsp = TAILQ_FIRST(gp->dq);
	    tsp != NULL; tsp = TAILQ_NEXT(tsp, q)) {
		if (sp == tsp)
			continue;
		/* Test if precedes the screen horizontally. */
		if (tsp->roff != sp->roff + sp->rows)
			continue;
		/*
		 * Test if a subset on the horizontal axis.  If overlaps the
		 * beginning or end, we can't join on this axis at all.
		 */
		if (tsp->coff > sp->coff + sp->cols)
			continue;
		if (tsp->coff < sp->coff) {
			if (tsp->coff + tsp->cols >= sp->coff)
				break;
			continue;
		}
		if (tsp->coff + tsp->cols > sp->coff + sp->cols)
			break;
#ifdef DEBUG
		if (tlen < tsp->cols)
			abort();
#endif
		tlen -= tsp->cols + first;
		first = 1;
		*lp++ = tsp;
	}
	if (tlen == 0) {
		*lp = NULL;
		*jdirp = HORIZ_FOLLOW;
		return (0);
	}
	return (1);
}
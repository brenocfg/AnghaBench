#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  void* recno_t ;
typedef  int pos_t ;
struct TYPE_20__ {size_t t_rows; } ;
struct TYPE_19__ {int lno; int soff; scalar_t__ coff; } ;
typedef  TYPE_1__ SMAP ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALFTEXT (TYPE_2__*) ; 
 TYPE_1__* HMAP ; 
 void* OOBLNO ; 
#define  P_BOTTOM 131 
#define  P_FILL 130 
#define  P_MIDDLE 129 
#define  P_TOP 128 
 int /*<<< orphan*/  SC_SCR_REDRAW ; 
 int /*<<< orphan*/  SMAP_FLUSH (TYPE_1__*) ; 
 TYPE_1__* TMAP ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  db_last (TYPE_2__*,int*) ; 
 void* vs_screens (TYPE_2__*,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ vs_sm_next (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vs_sm_nlines (TYPE_2__*,TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs_sm_prev (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 

int
vs_sm_fill(SCR *sp, recno_t lno, pos_t pos)
{
	SMAP *p, tmp;
	size_t cnt;

	/* Flush all cached information from the SMAP. */
	for (p = HMAP, cnt = sp->t_rows; cnt--; ++p)
		SMAP_FLUSH(p);

	/*
	 * If the map is filled, the screen must be redrawn.
	 *
	 * XXX
	 * This is a bug.  We should try and figure out if the desired line
	 * is already in the map or close by -- scrolling the screen would
	 * be a lot better than redrawing.
	 */
	F_SET(sp, SC_SCR_REDRAW);

	switch (pos) {
	case P_FILL:
		tmp.lno = 1;
		tmp.coff = 0;
		tmp.soff = 1;

		/* See if less than half a screen from the top. */
		if (vs_sm_nlines(sp,
		    &tmp, lno, HALFTEXT(sp)) <= HALFTEXT(sp)) {
			lno = 1;
			goto top;
		}

		/* See if less than half a screen from the bottom. */
		if (db_last(sp, &tmp.lno))
			return (1);
		tmp.coff = 0;
		tmp.soff = vs_screens(sp, tmp.lno, NULL);
		if (vs_sm_nlines(sp,
		    &tmp, lno, HALFTEXT(sp)) <= HALFTEXT(sp)) {
			TMAP->lno = tmp.lno;
			TMAP->coff = tmp.coff;
			TMAP->soff = tmp.soff;
			goto bottom;
		}
		goto middle;
	case P_TOP:
		if (lno != OOBLNO) {
top:			HMAP->lno = lno;
			HMAP->coff = 0;
			HMAP->soff = 1;
		} else {
			/*
			 * If number of lines HMAP->lno (top line) spans
			 * changed due to, say reformatting, and now is
			 * fewer than HMAP->soff, reset so the line is
			 * redrawn at the top of the screen.
			 */
			cnt = vs_screens(sp, HMAP->lno, NULL);
			if (cnt < HMAP->soff)
				HMAP->soff = 1;
		}
		/* If we fail, just punt. */
		for (p = HMAP, cnt = sp->t_rows; --cnt; ++p)
			if (vs_sm_next(sp, p, p + 1))
				goto err;
		break;
	case P_MIDDLE:
		/* If we fail, guess that the file is too small. */
middle:		p = HMAP + sp->t_rows / 2;
		p->lno = lno;
		p->coff = 0;
		p->soff = 1;
		for (; p > HMAP; --p)
			if (vs_sm_prev(sp, p, p - 1)) {
				lno = 1;
				goto top;
			}

		/* If we fail, just punt. */
		p = HMAP + sp->t_rows / 2;
		for (; p < TMAP; ++p)
			if (vs_sm_next(sp, p, p + 1))
				goto err;
		break;
	case P_BOTTOM:
		if (lno != OOBLNO) {
			TMAP->lno = lno;
			TMAP->coff = 0;
			TMAP->soff = vs_screens(sp, lno, NULL);
		}
		/* If we fail, guess that the file is too small. */
bottom:		for (p = TMAP; p > HMAP; --p)
			if (vs_sm_prev(sp, p, p - 1)) {
				lno = 1;
				goto top;
			}
		break;
	default:
		abort();
	}
	return (0);

	/*
	 * Try and put *something* on the screen.  If this fails, we have a
	 * serious hard error.
	 */
err:	HMAP->lno = 1;
	HMAP->coff = 0;
	HMAP->soff = 1;
	for (p = HMAP; p < TMAP; ++p)
		if (vs_sm_next(sp, p, p + 1))
			return (1);
	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct roffcol const* cols; } ;
struct termp {scalar_t__ enc; scalar_t__ viscol; int /*<<< orphan*/  (* endline ) (struct termp*) ;TYPE_5__ tbl; TYPE_4__* tcols; int /*<<< orphan*/  (* advance ) (struct termp*,scalar_t__) ;} ;
struct tbl_span {scalar_t__ pos; TYPE_2__* layout; TYPE_6__* opts; TYPE_3__* next; struct tbl_dat* first; } ;
struct tbl_dat {int /*<<< orphan*/ * string; struct tbl_dat* next; struct tbl_cell const* layout; } ;
struct tbl_cell {scalar_t__ pos; int col; int vert; struct tbl_cell* next; } ;
typedef  struct roffcol {int width; int spacing; } const roffcol ;
struct TYPE_12__ {int opts; int cols; } ;
struct TYPE_10__ {scalar_t__ offset; } ;
struct TYPE_9__ {struct tbl_dat* first; } ;
struct TYPE_8__ {TYPE_1__* last; struct tbl_cell* first; } ;
struct TYPE_7__ {scalar_t__ pos; } ;

/* Variables and functions */
 int BDOWN ; 
 int BHORIZ ; 
 int BLEFT ; 
 int BRIGHT ; 
 int BUP ; 
 scalar_t__ TBL_CELL_DOWN ; 
 scalar_t__ TBL_CELL_SPAN ; 
 int TBL_OPT_ALLBOX ; 
 int TBL_OPT_BOX ; 
 int TBL_OPT_DBOX ; 
 scalar_t__ TBL_SPAN_DATA ; 
 scalar_t__ TBL_SPAN_DHORIZ ; 
 scalar_t__ TERMENC_ASCII ; 
 scalar_t__ TERMENC_UTF8 ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct termp*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct termp*) ; 
 int /*<<< orphan*/  tbl_direct_border (struct termp*,int,int) ; 

__attribute__((used)) static void
tbl_hrule(struct termp *tp, const struct tbl_span *spp,
    const struct tbl_span *sp, const struct tbl_span *spn, int flags)
{
	const struct tbl_cell	*cpp;    /* Layout cell above this line. */
	const struct tbl_cell	*cp;     /* Layout cell in this line. */
	const struct tbl_cell	*cpn;    /* Layout cell below this line. */
	const struct tbl_dat	*dpn;	 /* Data cell below this line. */
	const struct roffcol	*col;    /* Contains width and spacing. */
	int			 opts;   /* For the table as a whole. */
	int			 bw;	 /* Box line width. */
	int			 hw;     /* Horizontal line width. */
	int			 lw, rw; /* Left and right line widths. */
	int			 uw, dw; /* Vertical line widths. */

	cpp = spp == NULL ? NULL : spp->layout->first;
	cp  = sp  == NULL ? NULL : sp->layout->first;
	cpn = spn == NULL ? NULL : spn->layout->first;
	dpn = NULL;
	if (spn != NULL) {
		if (spn->pos == TBL_SPAN_DATA)
			dpn = spn->first;
		else if (spn->next != NULL)
			dpn = spn->next->first;
	}
	opts = sp->opts->opts;
	bw = opts & TBL_OPT_DBOX ? (tp->enc == TERMENC_UTF8 ? 2 : 1) :
	    opts & (TBL_OPT_BOX | TBL_OPT_ALLBOX) ? 1 : 0;
	hw = flags == TBL_OPT_DBOX || flags == TBL_OPT_BOX ? bw :
	    sp->pos == TBL_SPAN_DHORIZ ? 2 : 1;

	/* Print the left end of the line. */

	if (tp->viscol == 0) {
		(*tp->advance)(tp, tp->tcols->offset);
		tp->viscol = tp->tcols->offset;
	}
	if (flags != 0)
		tbl_direct_border(tp,
		    (spp == NULL ? 0 : BUP * bw) +
		    (spn == NULL ? 0 : BDOWN * bw) +
		    (spp == NULL || cpn == NULL ||
		     cpn->pos != TBL_CELL_DOWN ? BRIGHT * hw : 0), 1);

	col = tp->tbl.cols;
	for (;;) {
		if (cp == NULL)
			col++;
		else
			col = tp->tbl.cols + cp->col;

		/* Print the horizontal line inside this column. */

		lw = cpp == NULL || cpn == NULL ||
		    (cpn->pos != TBL_CELL_DOWN &&
		     (dpn == NULL || dpn->string == NULL ||
		      strcmp(dpn->string, "\\^") != 0))
		    ? hw : 0;
		tbl_direct_border(tp, BHORIZ * lw,
		    col->width + col->spacing / 2);

		/*
		 * Figure out whether a vertical line is crossing
		 * at the end of this column,
		 * and advance to the next column.
		 */

		uw = dw = 0;
		if (cpp != NULL) {
			if (flags != TBL_OPT_DBOX) {
				uw = cpp->vert;
				if (uw == 0 && opts & TBL_OPT_ALLBOX)
					uw = 1;
			}
			cpp = cpp->next;
		} else if (spp != NULL && opts & TBL_OPT_ALLBOX)
			uw = 1;
		if (cp != NULL)
			cp = cp->next;
		if (cpn != NULL) {
			if (flags != TBL_OPT_DBOX) {
				dw = cpn->vert;
				if (dw == 0 && opts & TBL_OPT_ALLBOX)
					dw = 1;
			}
			cpn = cpn->next;
			while (dpn != NULL && dpn->layout != cpn)
				dpn = dpn->next;
		} else if (spn != NULL && opts & TBL_OPT_ALLBOX)
			dw = 1;
		if (col + 1 == tp->tbl.cols + sp->opts->cols)
			break;

		/* Vertical lines do not cross spanned cells. */

		if (cpp != NULL && cpp->pos == TBL_CELL_SPAN)
			uw = 0;
		if (cpn != NULL && cpn->pos == TBL_CELL_SPAN)
			dw = 0;

		/* The horizontal line inside the next column. */

		rw = cpp == NULL || cpn == NULL ||
		    (cpn->pos != TBL_CELL_DOWN &&
		     (dpn == NULL || dpn->string == NULL ||
		      strcmp(dpn->string, "\\^") != 0))
		    ? hw : 0;

		/* The line crossing at the end of this column. */

		if (col->spacing)
			tbl_direct_border(tp, BLEFT * lw +
			    BRIGHT * rw + BUP * uw + BDOWN * dw, 1);

		/*
		 * In ASCII output, a crossing may print two characters.
		 */

		if (tp->enc != TERMENC_ASCII || (uw < 2 && dw < 2))
			uw = dw = 0;
		if (col->spacing > 2)
			tbl_direct_border(tp,
                            BHORIZ * rw + BUP * uw + BDOWN * dw, 1);

		/* Padding before the start of the next column. */

		if (col->spacing > 4)
			tbl_direct_border(tp,
			    BHORIZ * rw, (col->spacing - 3) / 2);
	}

	/* Print the right end of the line. */

	if (flags != 0) {
		tbl_direct_border(tp,
		    (spp == NULL ? 0 : BUP * bw) +
		    (spn == NULL ? 0 : BDOWN * bw) +
		    (spp == NULL || spn == NULL ||
		     spn->layout->last->pos != TBL_CELL_DOWN ?
		     BLEFT * hw : 0), 1);
		(*tp->endline)(tp);
		tp->viscol = 0;
	}
}
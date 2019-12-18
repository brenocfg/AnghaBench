#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_7__* cols; struct termp* arg; int /*<<< orphan*/  sulen; int /*<<< orphan*/  slen; int /*<<< orphan*/  len; } ;
struct termp {int flags; scalar_t__ enc; size_t maxrmargin; int lasttcol; int viscol; int skipvsp; TYPE_4__* tcol; TYPE_5__ tbl; int /*<<< orphan*/  (* endline ) (struct termp*) ;TYPE_4__* tcols; int /*<<< orphan*/  (* advance ) (struct termp*,int) ;int /*<<< orphan*/  col; } ;
struct tbl_span {int pos; struct tbl_span const* next; TYPE_6__* opts; TYPE_3__* layout; TYPE_2__* last; struct tbl_span const* prev; struct tbl_dat* first; } ;
struct tbl_dat {int hspans; scalar_t__ pos; struct tbl_dat* next; } ;
typedef  struct tbl_cell {scalar_t__ pos; int vert; int col; struct tbl_cell const* next; } const tbl_cell ;
struct TYPE_16__ {size_t spacing; scalar_t__ width; } ;
struct TYPE_15__ {int opts; int cols; scalar_t__ rvert; scalar_t__ lvert; } ;
struct TYPE_13__ {size_t offset; size_t rmargin; scalar_t__ col; scalar_t__ lastcol; } ;
struct TYPE_12__ {int vert; struct tbl_cell const* last; struct tbl_cell const* first; } ;
struct TYPE_11__ {scalar_t__ pos; TYPE_1__* layout; } ;
struct TYPE_10__ {int col; } ;

/* Variables and functions */
 int BDOWN ; 
 int BHORIZ ; 
 int BLEFT ; 
 int BRIGHT ; 
 int BUP ; 
 scalar_t__ IS_HORIZ (struct tbl_cell const*) ; 
#define  TBL_CELL_DHORIZ 132 
#define  TBL_CELL_HORIZ 131 
 scalar_t__ TBL_CELL_SPAN ; 
 scalar_t__ TBL_DATA_DHORIZ ; 
 scalar_t__ TBL_DATA_HORIZ ; 
 int TBL_OPT_ALLBOX ; 
 int TBL_OPT_BOX ; 
 int TBL_OPT_CENTRE ; 
 int TBL_OPT_DBOX ; 
#define  TBL_SPAN_DATA 130 
#define  TBL_SPAN_DHORIZ 129 
#define  TBL_SPAN_HORIZ 128 
 scalar_t__ TERMENC_ASCII ; 
 scalar_t__ TERMENC_UTF8 ; 
 int TERMP_MULTICOL ; 
 int TERMP_NONOSPACE ; 
 int TERMP_NOSPACE ; 
 int /*<<< orphan*/  assert (TYPE_7__*) ; 
 int /*<<< orphan*/  borders_ascii ; 
 int /*<<< orphan*/  borders_locale ; 
 int /*<<< orphan*/  borders_utf8 ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (struct termp*,int) ; 
 int /*<<< orphan*/  stub2 (struct termp*,int) ; 
 int /*<<< orphan*/  stub3 (struct termp*) ; 
 int /*<<< orphan*/  tbl_data (struct termp*,TYPE_6__*,struct tbl_cell const*,struct tbl_dat const*,TYPE_7__*) ; 
 int /*<<< orphan*/  tbl_direct_border (struct termp*,int,int) ; 
 int /*<<< orphan*/  tbl_hrule (struct termp*,struct tbl_span const*,struct tbl_span const*,struct tbl_span const*,int) ; 
 int /*<<< orphan*/  tblcalc (TYPE_5__*,struct tbl_span const*,size_t,size_t) ; 
 int /*<<< orphan*/  term_flushln (struct termp*) ; 
 int /*<<< orphan*/  term_setcol (struct termp*,int) ; 
 int /*<<< orphan*/  term_tab_iset (size_t) ; 
 int /*<<< orphan*/  term_tab_set (struct termp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  term_tbl_len ; 
 int /*<<< orphan*/  term_tbl_strlen ; 
 int /*<<< orphan*/  term_tbl_sulen ; 

void
term_tbl(struct termp *tp, const struct tbl_span *sp)
{
	const struct tbl_cell	*cp, *cpn, *cpp, *cps;
	const struct tbl_dat	*dp;
	static size_t		 offset;
	size_t			 save_offset;
	size_t			 coloff, tsz;
	int			 hspans, ic, more;
	int			 dvert, fc, horiz, lhori, rhori, uvert;

	/* Inhibit printing of spaces: we do padding ourselves. */

	tp->flags |= TERMP_NOSPACE | TERMP_NONOSPACE;
	save_offset = tp->tcol->offset;

	/*
	 * The first time we're invoked for a given table block,
	 * calculate the table widths and decimal positions.
	 */

	if (tp->tbl.cols == NULL) {
		borders_locale = tp->enc == TERMENC_UTF8 ?
		    borders_utf8 : borders_ascii;

		tp->tbl.len = term_tbl_len;
		tp->tbl.slen = term_tbl_strlen;
		tp->tbl.sulen = term_tbl_sulen;
		tp->tbl.arg = tp;

		tblcalc(&tp->tbl, sp, tp->tcol->offset, tp->tcol->rmargin);

		/* Tables leak .ta settings to subsequent text. */

		term_tab_set(tp, NULL);
		coloff = sp->opts->opts & (TBL_OPT_BOX | TBL_OPT_DBOX) ||
		    sp->opts->lvert;
		for (ic = 0; ic < sp->opts->cols; ic++) {
			coloff += tp->tbl.cols[ic].width;
			term_tab_iset(coloff);
			coloff += tp->tbl.cols[ic].spacing;
		}

		/* Center the table as a whole. */

		offset = tp->tcol->offset;
		if (sp->opts->opts & TBL_OPT_CENTRE) {
			tsz = sp->opts->opts & (TBL_OPT_BOX | TBL_OPT_DBOX)
			    ? 2 : !!sp->opts->lvert + !!sp->opts->rvert;
			for (ic = 0; ic + 1 < sp->opts->cols; ic++)
				tsz += tp->tbl.cols[ic].width +
				    tp->tbl.cols[ic].spacing;
			if (sp->opts->cols)
				tsz += tp->tbl.cols[sp->opts->cols - 1].width;
			if (offset + tsz > tp->tcol->rmargin)
				tsz -= 1;
			offset = offset + tp->tcol->rmargin > tsz ?
			    (offset + tp->tcol->rmargin - tsz) / 2 : 0;
			tp->tcol->offset = offset;
		}

		/* Horizontal frame at the start of boxed tables. */

		if (tp->enc == TERMENC_ASCII &&
		    sp->opts->opts & TBL_OPT_DBOX)
			tbl_hrule(tp, NULL, sp, sp, TBL_OPT_DBOX);
		if (sp->opts->opts & (TBL_OPT_DBOX | TBL_OPT_BOX))
			tbl_hrule(tp, NULL, sp, sp, TBL_OPT_BOX);
	}

	/* Set up the columns. */

	tp->flags |= TERMP_MULTICOL;
	tp->tcol->offset = offset;
	horiz = 0;
	switch (sp->pos) {
	case TBL_SPAN_HORIZ:
	case TBL_SPAN_DHORIZ:
		horiz = 1;
		term_setcol(tp, 1);
		break;
	case TBL_SPAN_DATA:
		term_setcol(tp, sp->opts->cols + 2);
		coloff = tp->tcol->offset;

		/* Set up a column for a left vertical frame. */

		if (sp->opts->opts & (TBL_OPT_BOX | TBL_OPT_DBOX) ||
		    sp->opts->lvert)
			coloff++;
		tp->tcol->rmargin = coloff;

		/* Set up the data columns. */

		dp = sp->first;
		hspans = 0;
		for (ic = 0; ic < sp->opts->cols; ic++) {
			if (hspans == 0) {
				tp->tcol++;
				tp->tcol->offset = coloff;
			}
			coloff += tp->tbl.cols[ic].width;
			tp->tcol->rmargin = coloff;
			if (ic + 1 < sp->opts->cols)
				coloff += tp->tbl.cols[ic].spacing;
			if (hspans) {
				hspans--;
				continue;
			}
			if (dp == NULL)
				continue;
			hspans = dp->hspans;
			if (ic || sp->layout->first->pos != TBL_CELL_SPAN)
				dp = dp->next;
		}

		/* Set up a column for a right vertical frame. */

		tp->tcol++;
		tp->tcol->offset = coloff + 1;
		tp->tcol->rmargin = tp->maxrmargin;

		/* Spans may have reduced the number of columns. */

		tp->lasttcol = tp->tcol - tp->tcols;

		/* Fill the buffers for all data columns. */

		tp->tcol = tp->tcols;
		cp = cpn = sp->layout->first;
		dp = sp->first;
		hspans = 0;
		for (ic = 0; ic < sp->opts->cols; ic++) {
			if (cpn != NULL) {
				cp = cpn;
				cpn = cpn->next;
			}
			if (hspans) {
				hspans--;
				continue;
			}
			tp->tcol++;
			tp->col = 0;
			tbl_data(tp, sp->opts, cp, dp, tp->tbl.cols + ic);
			if (dp == NULL)
				continue;
			hspans = dp->hspans;
			if (cp->pos != TBL_CELL_SPAN)
				dp = dp->next;
		}
		break;
	}

	do {
		/* Print the vertical frame at the start of each row. */

		tp->tcol = tp->tcols;
		uvert = dvert = sp->opts->opts & TBL_OPT_DBOX ? 2 :
		    sp->opts->opts & TBL_OPT_BOX ? 1 : 0;
		if (sp->pos == TBL_SPAN_DATA && uvert < sp->layout->vert)
			uvert = dvert = sp->layout->vert;
		if (sp->next != NULL && sp->next->pos == TBL_SPAN_DATA &&
		    dvert < sp->next->layout->vert)
			dvert = sp->next->layout->vert;
		if (sp->prev != NULL && uvert < sp->prev->layout->vert &&
		    (horiz || (IS_HORIZ(sp->layout->first) &&
		      !IS_HORIZ(sp->prev->layout->first))))
			uvert = sp->prev->layout->vert;
		rhori = sp->pos == TBL_SPAN_DHORIZ ||
		    (sp->first != NULL && sp->first->pos == TBL_DATA_DHORIZ) ||
		    sp->layout->first->pos == TBL_CELL_DHORIZ ? 2 :
		    sp->pos == TBL_SPAN_HORIZ ||
		    (sp->first != NULL && sp->first->pos == TBL_DATA_HORIZ) ||
		    sp->layout->first->pos == TBL_CELL_HORIZ ? 1 : 0;
		fc = BUP * uvert + BDOWN * dvert + BRIGHT * rhori;
		if (uvert > 0 || dvert > 0 || (horiz && sp->opts->lvert)) {
			(*tp->advance)(tp, tp->tcols->offset);
			tp->viscol = tp->tcol->offset;
			tbl_direct_border(tp, fc, 1);
		}

		/* Print the data cells. */

		more = 0;
		if (horiz)
			tbl_hrule(tp, sp->prev, sp, sp->next, 0);
		else {
			cp = sp->layout->first;
			cpn = sp->next == NULL ? NULL :
			    sp->next->layout->first;
			cpp = sp->prev == NULL ? NULL :
			    sp->prev->layout->first;
			dp = sp->first;
			hspans = 0;
			for (ic = 0; ic < sp->opts->cols; ic++) {

				/*
				 * Figure out whether to print a
				 * vertical line after this cell
				 * and advance to next layout cell.
				 */

				uvert = dvert = fc = 0;
				if (cp != NULL) {
					cps = cp;
					while (cps->next != NULL &&
					    cps->next->pos == TBL_CELL_SPAN)
						cps = cps->next;
					if (sp->pos == TBL_SPAN_DATA)
						uvert = dvert = cps->vert;
					switch (cp->pos) {
					case TBL_CELL_HORIZ:
						fc = BHORIZ;
						break;
					case TBL_CELL_DHORIZ:
						fc = BHORIZ * 2;
						break;
					default:
						break;
					}
				}
				if (cpp != NULL) {
					if (uvert < cpp->vert &&
					    cp != NULL &&
					    ((IS_HORIZ(cp) &&
					      !IS_HORIZ(cpp)) ||
					     (cp->next != NULL &&
					      cpp->next != NULL &&
					      IS_HORIZ(cp->next) &&
					      !IS_HORIZ(cpp->next))))
						uvert = cpp->vert;
					cpp = cpp->next;
				}
				if (sp->opts->opts & TBL_OPT_ALLBOX) {
					if (uvert == 0)
						uvert = 1;
					if (dvert == 0)
						dvert = 1;
				}
				if (cpn != NULL) {
					if (dvert == 0 ||
					    (dvert < cpn->vert &&
					     tp->enc == TERMENC_UTF8))
						dvert = cpn->vert;
					cpn = cpn->next;
				}

				lhori = (cp != NULL &&
				     cp->pos == TBL_CELL_DHORIZ) ||
				    (dp != NULL &&
				     dp->pos == TBL_DATA_DHORIZ) ? 2 :
				    (cp != NULL &&
				     cp->pos == TBL_CELL_HORIZ) ||
				    (dp != NULL &&
				     dp->pos == TBL_DATA_HORIZ) ? 1 : 0;

				/*
				 * Skip later cells in a span,
				 * figure out whether to start a span,
				 * and advance to next data cell.
				 */

				if (hspans) {
					hspans--;
					cp = cp->next;
					continue;
				}
				if (dp != NULL) {
					hspans = dp->hspans;
					if (ic || sp->layout->first->pos
					    != TBL_CELL_SPAN)
						dp = dp->next;
				}

				/*
				 * Print one line of text in the cell
				 * and remember whether there is more.
				 */

				tp->tcol++;
				if (tp->tcol->col < tp->tcol->lastcol)
					term_flushln(tp);
				if (tp->tcol->col < tp->tcol->lastcol)
					more = 1;

				/*
				 * Vertical frames between data cells,
				 * but not after the last column.
				 */

				if (fc == 0 &&
				    ((uvert == 0 && dvert == 0 &&
				      cp != NULL && (cp->next == NULL ||
				      !IS_HORIZ(cp->next))) ||
				     tp->tcol + 1 ==
				      tp->tcols + tp->lasttcol)) {
					if (cp != NULL)
						cp = cp->next;
					continue;
				}

				if (tp->viscol < tp->tcol->rmargin) {
					(*tp->advance)(tp, tp->tcol->rmargin
					   - tp->viscol);
					tp->viscol = tp->tcol->rmargin;
				}
				while (tp->viscol < tp->tcol->rmargin +
				    tp->tbl.cols[ic].spacing / 2)
					tbl_direct_border(tp,
					    BHORIZ * lhori, 1);

				if (tp->tcol + 1 == tp->tcols + tp->lasttcol)
					continue;

				if (cp != NULL)
					cp = cp->next;

				rhori = (cp != NULL &&
				     cp->pos == TBL_CELL_DHORIZ) ||
				    (dp != NULL &&
				     dp->pos == TBL_DATA_DHORIZ) ? 2 :
				    (cp != NULL &&
				     cp->pos == TBL_CELL_HORIZ) ||
				    (dp != NULL &&
				     dp->pos == TBL_DATA_HORIZ) ? 1 : 0;

				if (tp->tbl.cols[ic].spacing)
					tbl_direct_border(tp,
					    BLEFT * lhori + BRIGHT * rhori +
					    BUP * uvert + BDOWN * dvert, 1);

				if (tp->enc == TERMENC_UTF8)
					uvert = dvert = 0;

				if (tp->tbl.cols[ic].spacing > 2 &&
				    (uvert > 1 || dvert > 1 || rhori))
					tbl_direct_border(tp,
					    BHORIZ * rhori +
					    BUP * (uvert > 1) +
					    BDOWN * (dvert > 1), 1);
			}
		}

		/* Print the vertical frame at the end of each row. */

		uvert = dvert = sp->opts->opts & TBL_OPT_DBOX ? 2 :
		    sp->opts->opts & TBL_OPT_BOX ? 1 : 0;
		if (sp->pos == TBL_SPAN_DATA &&
		    uvert < sp->layout->last->vert &&
		    sp->layout->last->col + 1 == sp->opts->cols)
			uvert = dvert = sp->layout->last->vert;
		if (sp->next != NULL &&
		    dvert < sp->next->layout->last->vert &&
		    sp->next->layout->last->col + 1 == sp->opts->cols)
			dvert = sp->next->layout->last->vert;
		if (sp->prev != NULL &&
		    uvert < sp->prev->layout->last->vert &&
		    sp->prev->layout->last->col + 1 == sp->opts->cols &&
		    (horiz || (IS_HORIZ(sp->layout->last) &&
		     !IS_HORIZ(sp->prev->layout->last))))
			uvert = sp->prev->layout->last->vert;
		lhori = sp->pos == TBL_SPAN_DHORIZ ||
		    (sp->last != NULL &&
		     sp->last->pos == TBL_DATA_DHORIZ &&
		     sp->last->layout->col + 1 == sp->opts->cols) ||
		    (sp->layout->last->pos == TBL_CELL_DHORIZ &&
		     sp->layout->last->col + 1 == sp->opts->cols) ? 2 :
		    sp->pos == TBL_SPAN_HORIZ ||
		    (sp->last != NULL &&
		     sp->last->pos == TBL_DATA_HORIZ &&
		     sp->last->layout->col + 1 == sp->opts->cols) ||
		    (sp->layout->last->pos == TBL_CELL_HORIZ &&
		     sp->layout->last->col + 1 == sp->opts->cols) ? 1 : 0;
		fc = BUP * uvert + BDOWN * dvert + BLEFT * lhori;
		if (uvert > 0 || dvert > 0 || (horiz && sp->opts->rvert)) {
			if (horiz == 0 && (IS_HORIZ(sp->layout->last) == 0 ||
			    sp->layout->last->col + 1 < sp->opts->cols)) {
				tp->tcol++;
				do {
					tbl_direct_border(tp,
					    BHORIZ * lhori, 1);
				} while (tp->viscol < tp->tcol->offset);
			}
			tbl_direct_border(tp, fc, 1);
		}
		(*tp->endline)(tp);
		tp->viscol = 0;
	} while (more);

	/*
	 * Clean up after this row.  If it is the last line
	 * of the table, print the box line and clean up
	 * column data; otherwise, print the allbox line.
	 */

	term_setcol(tp, 1);
	tp->flags &= ~TERMP_MULTICOL;
	tp->tcol->rmargin = tp->maxrmargin;
	if (sp->next == NULL) {
		if (sp->opts->opts & (TBL_OPT_DBOX | TBL_OPT_BOX)) {
			tbl_hrule(tp, sp, sp, NULL, TBL_OPT_BOX);
			tp->skipvsp = 1;
		}
		if (tp->enc == TERMENC_ASCII &&
		    sp->opts->opts & TBL_OPT_DBOX) {
			tbl_hrule(tp, sp, sp, NULL, TBL_OPT_DBOX);
			tp->skipvsp = 2;
		}
		assert(tp->tbl.cols);
		free(tp->tbl.cols);
		tp->tbl.cols = NULL;
	} else if (horiz == 0 && sp->opts->opts & TBL_OPT_ALLBOX &&
	    (sp->next == NULL || sp->next->pos == TBL_SPAN_DATA ||
	     sp->next->next != NULL))
		tbl_hrule(tp, sp, sp, sp->next, TBL_OPT_ALLBOX);

	tp->tcol->offset = save_offset;
	tp->flags &= ~TERMP_NONOSPACE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tbl_span {scalar_t__ pos; struct tbl_row* layout; } ;
struct tbl_row {struct tbl_row* next; struct tbl_cell* first; TYPE_1__* last; } ;
struct TYPE_4__ {scalar_t__ cols; } ;
struct tbl_node {TYPE_2__ opts; struct tbl_row* first_row; struct tbl_span* last_span; } ;
struct tbl_cell {scalar_t__ pos; struct tbl_cell* next; } ;
struct TYPE_3__ {scalar_t__ col; } ;

/* Variables and functions */
 scalar_t__ TBL_CELL_DHORIZ ; 
 scalar_t__ TBL_CELL_HORIZ ; 
 scalar_t__ TBL_SPAN_DATA ; 
 scalar_t__ TBL_SPAN_DHORIZ ; 
 scalar_t__ TBL_SPAN_HORIZ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getdata (struct tbl_node*,struct tbl_span*,int,char const*,int*) ; 
 struct tbl_span* newspan (struct tbl_node*,int,struct tbl_row*) ; 

void
tbl_data(struct tbl_node *tbl, int ln, const char *p, int pos)
{
	struct tbl_row	*rp;
	struct tbl_cell	*cp;
	struct tbl_span	*sp;

	rp = (sp = tbl->last_span) == NULL ? tbl->first_row :
	    sp->pos == TBL_SPAN_DATA && sp->layout->next != NULL ?
	    sp->layout->next : sp->layout;

	assert(rp != NULL);

	if (p[1] == '\0') {
		switch (p[0]) {
		case '.':
			/*
			 * Empty request lines must be handled here
			 * and cannot be discarded in roff_parseln()
			 * because in the layout section, they
			 * are significant and end the layout.
			 */
			return;
		case '_':
			sp = newspan(tbl, ln, rp);
			sp->pos = TBL_SPAN_HORIZ;
			return;
		case '=':
			sp = newspan(tbl, ln, rp);
			sp->pos = TBL_SPAN_DHORIZ;
			return;
		default:
			break;
		}
	}

	/*
	 * If the layout row contains nothing but horizontal lines,
	 * allocate an empty span for it and assign the current span
	 * to the next layout row accepting data.
	 */

	while (rp->next != NULL) {
		if (rp->last->col + 1 < tbl->opts.cols)
			break;
		for (cp = rp->first; cp != NULL; cp = cp->next)
			if (cp->pos != TBL_CELL_HORIZ &&
			    cp->pos != TBL_CELL_DHORIZ)
				break;
		if (cp != NULL)
			break;
		sp = newspan(tbl, ln, rp);
		sp->pos = TBL_SPAN_DATA;
		rp = rp->next;
	}

	/* Process a real data row. */

	sp = newspan(tbl, ln, rp);
	sp->pos = TBL_SPAN_DATA;
	while (p[pos] != '\0')
		getdata(tbl, sp, ln, p, &pos);
}
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
struct tbl_row {struct tbl_row* next; int /*<<< orphan*/ * first; TYPE_2__* last; int /*<<< orphan*/  vert; } ;
struct TYPE_3__ {int /*<<< orphan*/  rvert; int /*<<< orphan*/  cols; int /*<<< orphan*/  lvert; } ;
struct tbl_node {struct tbl_row* last_row; struct tbl_row* first_row; TYPE_1__ opts; int /*<<< orphan*/  part; } ;
struct TYPE_4__ {int /*<<< orphan*/  vert; int /*<<< orphan*/  col; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_TBLLAYOUT_NONE ; 
 int /*<<< orphan*/  TBL_CELL_LEFT ; 
 int /*<<< orphan*/  TBL_PART_DATA ; 
 int /*<<< orphan*/  cell (struct tbl_node*,struct tbl_row*,int,char const*,int*) ; 
 int /*<<< orphan*/  cell_alloc (struct tbl_node*,struct tbl_row*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tbl_row*) ; 
 void* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void
tbl_layout(struct tbl_node *tbl, int ln, const char *p, int pos)
{
	struct tbl_row	*rp;

	rp = NULL;
	for (;;) {
		/* Skip whitespace before and after each cell. */

		while (p[pos] == ' ' || p[pos] == '\t')
			pos++;

		switch (p[pos]) {
		case ',':  /* Next row on this input line. */
			pos++;
			rp = NULL;
			continue;
		case '\0':  /* Next row on next input line. */
			return;
		case '.':  /* End of layout. */
			pos++;
			tbl->part = TBL_PART_DATA;

			/*
			 * When the layout is completely empty,
			 * default to one left-justified column.
			 */

			if (tbl->first_row == NULL) {
				tbl->first_row = tbl->last_row =
				    mandoc_calloc(1, sizeof(*rp));
			}
			if (tbl->first_row->first == NULL) {
				mandoc_msg(MANDOCERR_TBLLAYOUT_NONE,
				    ln, pos, NULL);
				cell_alloc(tbl, tbl->first_row,
				    TBL_CELL_LEFT);
				if (tbl->opts.lvert < tbl->first_row->vert)
					tbl->opts.lvert = tbl->first_row->vert;
				return;
			}

			/*
			 * Search for the widest line
			 * along the left and right margins.
			 */

			for (rp = tbl->first_row; rp; rp = rp->next) {
				if (tbl->opts.lvert < rp->vert)
					tbl->opts.lvert = rp->vert;
				if (rp->last != NULL &&
				    rp->last->col + 1 == tbl->opts.cols &&
				    tbl->opts.rvert < rp->last->vert)
					tbl->opts.rvert = rp->last->vert;

				/* If the last line is empty, drop it. */

				if (rp->next != NULL &&
				    rp->next->first == NULL) {
					free(rp->next);
					rp->next = NULL;
					tbl->last_row = rp;
				}
			}
			return;
		default:  /* Cell. */
			break;
		}

		/*
		 * If the last line had at least one cell,
		 * start a new one; otherwise, continue it.
		 */

		if (rp == NULL) {
			if (tbl->last_row == NULL ||
			    tbl->last_row->first != NULL) {
				rp = mandoc_calloc(1, sizeof(*rp));
				if (tbl->last_row)
					tbl->last_row->next = rp;
				else
					tbl->first_row = rp;
				tbl->last_row = rp;
			} else
				rp = tbl->last_row;
		}
		cell(tbl, rp, ln, p, &pos);
	}
}
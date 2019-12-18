#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tbl_span {struct tbl_dat* last; struct tbl_dat* first; struct tbl_span* prev; TYPE_3__* layout; TYPE_2__* opts; } ;
struct TYPE_4__ {char const tab; } ;
struct tbl_node {int /*<<< orphan*/  part; TYPE_1__ opts; } ;
struct tbl_dat {char* string; scalar_t__ pos; struct tbl_cell* layout; struct tbl_dat* next; scalar_t__ hspans; scalar_t__ vspans; scalar_t__ block; } ;
struct tbl_cell {scalar_t__ pos; scalar_t__ col; struct tbl_cell* next; } ;
struct TYPE_6__ {struct tbl_cell* last; struct tbl_cell* first; } ;
struct TYPE_5__ {scalar_t__ cols; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_TBLDATA_EXTRA ; 
 int /*<<< orphan*/  MANDOCERR_TBLDATA_SPAN ; 
 scalar_t__ TBL_CELL_DHORIZ ; 
 scalar_t__ TBL_CELL_DOWN ; 
 scalar_t__ TBL_CELL_HORIZ ; 
 scalar_t__ TBL_CELL_LEFT ; 
 scalar_t__ TBL_CELL_SPAN ; 
 scalar_t__ TBL_DATA_DATA ; 
 scalar_t__ TBL_DATA_DHORIZ ; 
 scalar_t__ TBL_DATA_HORIZ ; 
 scalar_t__ TBL_DATA_NDHORIZ ; 
 scalar_t__ TBL_DATA_NHORIZ ; 
 scalar_t__ TBL_DATA_NONE ; 
 int /*<<< orphan*/  TBL_PART_CDATA ; 
 struct tbl_cell* mandoc_calloc (int,int) ; 
 struct tbl_dat* mandoc_malloc (int) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,char const*) ; 
 char* mandoc_strndup (char const*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
getdata(struct tbl_node *tbl, struct tbl_span *dp,
		int ln, const char *p, int *pos)
{
	struct tbl_dat	*dat, *pdat;
	struct tbl_cell	*cp;
	struct tbl_span	*pdp;
	int		 sv;

	/*
	 * Determine the length of the string in the cell
	 * and advance the parse point to the end of the cell.
	 */

	sv = *pos;
	while (p[*pos] != '\0' && p[*pos] != tbl->opts.tab)
		(*pos)++;

	/* Advance to the next layout cell, skipping spanners. */

	cp = dp->last == NULL ? dp->layout->first : dp->last->layout->next;
	while (cp != NULL && cp->pos == TBL_CELL_SPAN)
		cp = cp->next;

	/*
	 * If the current layout row is out of cells, allocate
	 * a new cell if another row of the table has at least
	 * this number of columns, or discard the input if we
	 * are beyond the last column of the table as a whole.
	 */

	if (cp == NULL) {
		if (dp->layout->last->col + 1 < dp->opts->cols) {
			cp = mandoc_calloc(1, sizeof(*cp));
			cp->pos = TBL_CELL_LEFT;
			dp->layout->last->next = cp;
			cp->col = dp->layout->last->col + 1;
			dp->layout->last = cp;
		} else {
			mandoc_msg(MANDOCERR_TBLDATA_EXTRA,
			    ln, sv, "%s", p + sv);
			while (p[*pos] != '\0')
				(*pos)++;
			return;
		}
	}

	dat = mandoc_malloc(sizeof(*dat));
	dat->layout = cp;
	dat->next = NULL;
	dat->string = NULL;
	dat->hspans = 0;
	dat->vspans = 0;
	dat->block = 0;
	dat->pos = TBL_DATA_NONE;

	/*
	 * Increment the number of vertical spans in a data cell above,
	 * if this cell vertically extends one or more cells above.
	 * The iteration must be done over data rows,
	 * not over layout rows, because one layout row
	 * can be reused for more than one data row.
	 */

	if (cp->pos == TBL_CELL_DOWN ||
	    (*pos - sv == 2 && p[sv] == '\\' && p[sv + 1] == '^')) {
		pdp = dp;
		while ((pdp = pdp->prev) != NULL) {
			pdat = pdp->first;
			while (pdat != NULL &&
			    pdat->layout->col < dat->layout->col)
				pdat = pdat->next;
			if (pdat == NULL)
				break;
			if (pdat->layout->pos != TBL_CELL_DOWN &&
			    strcmp(pdat->string, "\\^") != 0) {
				pdat->vspans++;
				break;
			}
		}
	}

	/*
	 * Count the number of horizontal spans to the right of this cell.
	 * This is purely a matter of the layout, independent of the data.
	 */

	for (cp = cp->next; cp != NULL; cp = cp->next)
		if (cp->pos == TBL_CELL_SPAN)
			dat->hspans++;
		else
			break;

	/* Append the new data cell to the data row. */

	if (dp->last == NULL)
		dp->first = dat;
	else
		dp->last->next = dat;
	dp->last = dat;

	/*
	 * Check for a continued-data scope opening.  This consists of a
	 * trailing `T{' at the end of the line.  Subsequent lines,
	 * until a standalone `T}', are included in our cell.
	 */

	if (*pos - sv == 2 && p[sv] == 'T' && p[sv + 1] == '{') {
		tbl->part = TBL_PART_CDATA;
		return;
	}

	dat->string = mandoc_strndup(p + sv, *pos - sv);

	if (p[*pos] != '\0')
		(*pos)++;

	if ( ! strcmp(dat->string, "_"))
		dat->pos = TBL_DATA_HORIZ;
	else if ( ! strcmp(dat->string, "="))
		dat->pos = TBL_DATA_DHORIZ;
	else if ( ! strcmp(dat->string, "\\_"))
		dat->pos = TBL_DATA_NHORIZ;
	else if ( ! strcmp(dat->string, "\\="))
		dat->pos = TBL_DATA_NDHORIZ;
	else
		dat->pos = TBL_DATA_DATA;

	if ((dat->layout->pos == TBL_CELL_HORIZ ||
	    dat->layout->pos == TBL_CELL_DHORIZ ||
	    dat->layout->pos == TBL_CELL_DOWN) &&
	    dat->pos == TBL_DATA_DATA && *dat->string != '\0')
		mandoc_msg(MANDOCERR_TBLDATA_SPAN,
		    ln, sv, "%s", dat->string);
}
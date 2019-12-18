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
typedef  int /*<<< orphan*/  vbuf ;
struct tbl_span {scalar_t__ pos; struct tbl_span* next; struct tbl_dat* first; TYPE_1__* layout; } ;
struct tbl_dat {int hspans; scalar_t__ vspans; int /*<<< orphan*/ * string; struct tbl_cell* layout; struct tbl_dat* next; } ;
struct tbl_cell {int pos; int flags; int vert; struct tbl_cell* next; } ;
struct tag {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cols; } ;
struct html {TYPE_2__ tbl; int /*<<< orphan*/  flags; int /*<<< orphan*/ * tblt; } ;
typedef  int /*<<< orphan*/  hbuf ;
struct TYPE_3__ {int vert; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTML_NONOSPACE ; 
 int /*<<< orphan*/  HTML_NOSPACE ; 
 int /*<<< orphan*/  TAG_TD ; 
 int /*<<< orphan*/  TAG_TR ; 
 int TBL_CELL_BALIGN ; 
#define  TBL_CELL_CENTRE 132 
 int TBL_CELL_DOWN ; 
#define  TBL_CELL_NUMBER 131 
#define  TBL_CELL_RIGHT 130 
 int TBL_CELL_SPAN ; 
 int TBL_CELL_TALIGN ; 
 scalar_t__ TBL_SPAN_DATA ; 
#define  TBL_SPAN_DHORIZ 129 
#define  TBL_SPAN_HORIZ 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  html_tblopen (struct html*,struct tbl_span const*) ; 
 struct tag* print_otag (struct html*,int /*<<< orphan*/ ,char*,char*,char const*,char*,char const*,...) ; 
 int /*<<< orphan*/  print_stagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_tblclose (struct html*) ; 
 int /*<<< orphan*/  print_text (struct html*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

void
print_tbl(struct html *h, const struct tbl_span *sp)
{
	const struct tbl_dat	*dp;
	const struct tbl_cell	*cp;
	const struct tbl_span	*psp;
	struct tag		*tt;
	const char		*hspans, *vspans, *halign, *valign;
	const char		*bborder, *lborder, *rborder;
	char			 hbuf[4], vbuf[4];
	int			 i;

	if (h->tblt == NULL)
		html_tblopen(h, sp);

	/*
	 * Horizontal lines spanning the whole table
	 * are handled by previous or following table rows.
	 */

	if (sp->pos != TBL_SPAN_DATA)
		return;

	/* Inhibit printing of spaces: we do padding ourselves. */

	h->flags |= HTML_NONOSPACE;
	h->flags |= HTML_NOSPACE;

	/* Draw a vertical line left of this row? */

	switch (sp->layout->vert) {
	case 2:
		lborder = "double";
		break;
	case 1:
		lborder = "solid";
		break;
	default:
		lborder = NULL;
		break;
	}

	/* Draw a horizontal line below this row? */

	bborder = NULL;
	if ((psp = sp->next) != NULL) {
		switch (psp->pos) {
		case TBL_SPAN_DHORIZ:
			bborder = "double";
			break;
		case TBL_SPAN_HORIZ:
			bborder = "solid";
			break;
		default:
			break;
		}
	}

	tt = print_otag(h, TAG_TR, "ss",
	    "border-left-style", lborder,
	    "border-bottom-style", bborder);

	for (dp = sp->first; dp != NULL; dp = dp->next) {
		print_stagq(h, tt);

		/*
		 * Do not generate <td> elements for continuations
		 * of spanned cells.  Larger <td> elements covering
		 * this space were already generated earlier.
		 */

		cp = dp->layout;
		if (cp->pos == TBL_CELL_SPAN || cp->pos == TBL_CELL_DOWN ||
		    (dp->string != NULL && strcmp(dp->string, "\\^") == 0))
			continue;

		/* Determine the attribute values. */

		if (dp->hspans > 0) {
			(void)snprintf(hbuf, sizeof(hbuf),
			    "%d", dp->hspans + 1);
			hspans = hbuf;
		} else
			hspans = NULL;
		if (dp->vspans > 0) {
			(void)snprintf(vbuf, sizeof(vbuf),
			    "%d", dp->vspans + 1);
			vspans = vbuf;
		} else
			vspans = NULL;

		switch (cp->pos) {
		case TBL_CELL_CENTRE:
			halign = "center";
			break;
		case TBL_CELL_RIGHT:
		case TBL_CELL_NUMBER:
			halign = "right";
			break;
		default:
			halign = NULL;
			break;
		}
		if (cp->flags & TBL_CELL_TALIGN)
			valign = "top";
		else if (cp->flags & TBL_CELL_BALIGN)
			valign = "bottom";
		else
			valign = NULL;

		for (i = dp->hspans; i > 0; i--)
			cp = cp->next;
		switch (cp->vert) {
		case 2:
			rborder = "double";
			break;
		case 1:
			rborder = "solid";
			break;
		default:
			rborder = NULL;
			break;
		}

		/* Print the element and the attributes. */

		print_otag(h, TAG_TD, "??sss",
		    "colspan", hspans, "rowspan", vspans,
		    "vertical-align", valign,
		    "text-align", halign,
		    "border-right-style", rborder);
		if (dp->string != NULL)
			print_text(h, dp->string);
	}

	print_tagq(h, tt);

	h->flags &= ~HTML_NONOSPACE;

	if (sp->next == NULL) {
		assert(h->tbl.cols);
		free(h->tbl.cols);
		h->tbl.cols = NULL;
		print_tblclose(h);
	}
}
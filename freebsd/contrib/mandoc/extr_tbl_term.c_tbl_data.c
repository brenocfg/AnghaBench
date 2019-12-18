#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct termp {int dummy; } ;
struct tbl_opts {int dummy; } ;
struct tbl_dat {int pos; } ;
struct tbl_cell {int pos; } ;
struct roffcol {int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int BHORIZ ; 
#define  TBL_CELL_CENTRE 141 
#define  TBL_CELL_DHORIZ 140 
#define  TBL_CELL_DOWN 139 
#define  TBL_CELL_HORIZ 138 
#define  TBL_CELL_LEFT 137 
#define  TBL_CELL_LONG 136 
#define  TBL_CELL_NUMBER 135 
#define  TBL_CELL_RIGHT 134 
#define  TBL_CELL_SPAN 133 
#define  TBL_DATA_DHORIZ 132 
#define  TBL_DATA_HORIZ 131 
#define  TBL_DATA_NDHORIZ 130 
#define  TBL_DATA_NHORIZ 129 
#define  TBL_DATA_NONE 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  tbl_fill_border (struct termp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbl_literal (struct termp*,struct tbl_dat const*,struct roffcol const*) ; 
 int /*<<< orphan*/  tbl_number (struct termp*,struct tbl_opts const*,struct tbl_dat const*,struct roffcol const*) ; 

__attribute__((used)) static void
tbl_data(struct termp *tp, const struct tbl_opts *opts,
    const struct tbl_cell *cp, const struct tbl_dat *dp,
    const struct roffcol *col)
{
	switch (cp->pos) {
	case TBL_CELL_HORIZ:
		tbl_fill_border(tp, BHORIZ, col->width);
		return;
	case TBL_CELL_DHORIZ:
		tbl_fill_border(tp, BHORIZ * 2, col->width);
		return;
	default:
		break;
	}

	if (dp == NULL)
		return;

	switch (dp->pos) {
	case TBL_DATA_NONE:
		return;
	case TBL_DATA_HORIZ:
	case TBL_DATA_NHORIZ:
		tbl_fill_border(tp, BHORIZ, col->width);
		return;
	case TBL_DATA_NDHORIZ:
	case TBL_DATA_DHORIZ:
		tbl_fill_border(tp, BHORIZ * 2, col->width);
		return;
	default:
		break;
	}

	switch (cp->pos) {
	case TBL_CELL_LONG:
	case TBL_CELL_CENTRE:
	case TBL_CELL_LEFT:
	case TBL_CELL_RIGHT:
		tbl_literal(tp, dp, col);
		break;
	case TBL_CELL_NUMBER:
		tbl_number(tp, opts, dp, col);
		break;
	case TBL_CELL_DOWN:
	case TBL_CELL_SPAN:
		break;
	default:
		abort();
	}
}
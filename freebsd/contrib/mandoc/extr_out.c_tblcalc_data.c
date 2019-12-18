#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tbl_opts {int dummy; } ;
struct tbl_dat {TYPE_1__* layout; } ;
struct rofftbl {size_t (* len ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg; } ;
struct roffcol {size_t width; } ;
struct TYPE_2__ {int pos; } ;

/* Variables and functions */
#define  TBL_CELL_CENTRE 135 
#define  TBL_CELL_DHORIZ 134 
#define  TBL_CELL_DOWN 133 
#define  TBL_CELL_HORIZ 132 
#define  TBL_CELL_LEFT 131 
#define  TBL_CELL_LONG 130 
#define  TBL_CELL_NUMBER 129 
#define  TBL_CELL_RIGHT 128 
 int /*<<< orphan*/  abort () ; 
 size_t stub1 (int,int /*<<< orphan*/ ) ; 
 size_t tblcalc_literal (struct rofftbl*,struct roffcol*,struct tbl_dat const*,size_t) ; 
 size_t tblcalc_number (struct rofftbl*,struct roffcol*,struct tbl_opts const*,struct tbl_dat const*) ; 

__attribute__((used)) static size_t
tblcalc_data(struct rofftbl *tbl, struct roffcol *col,
    const struct tbl_opts *opts, const struct tbl_dat *dp, size_t mw)
{
	size_t		 sz;

	/* Branch down into data sub-types. */

	switch (dp->layout->pos) {
	case TBL_CELL_HORIZ:
	case TBL_CELL_DHORIZ:
		sz = (*tbl->len)(1, tbl->arg);
		if (col != NULL && col->width < sz)
			col->width = sz;
		return sz;
	case TBL_CELL_LONG:
	case TBL_CELL_CENTRE:
	case TBL_CELL_LEFT:
	case TBL_CELL_RIGHT:
		return tblcalc_literal(tbl, col, dp, mw);
	case TBL_CELL_NUMBER:
		return tblcalc_number(tbl, col, opts, dp);
	case TBL_CELL_DOWN:
		return 0;
	default:
		abort();
	}
}
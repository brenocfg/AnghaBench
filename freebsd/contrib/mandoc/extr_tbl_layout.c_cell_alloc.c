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
struct tbl_row {struct tbl_cell* last; struct tbl_cell* first; } ;
struct TYPE_2__ {scalar_t__ cols; } ;
struct tbl_node {TYPE_1__ opts; } ;
struct tbl_cell {int pos; scalar_t__ col; struct tbl_cell* next; int /*<<< orphan*/  spacing; } ;
typedef  enum tbl_cellt { ____Placeholder_tbl_cellt } tbl_cellt ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 struct tbl_cell* mandoc_calloc (int,int) ; 

__attribute__((used)) static struct tbl_cell *
cell_alloc(struct tbl_node *tbl, struct tbl_row *rp, enum tbl_cellt pos)
{
	struct tbl_cell	*p, *pp;

	p = mandoc_calloc(1, sizeof(*p));
	p->spacing = SIZE_MAX;
	p->pos = pos;

	if ((pp = rp->last) != NULL) {
		pp->next = p;
		p->col = pp->col + 1;
	} else
		rp->first = p;
	rp->last = p;

	if (tbl->opts.cols <= p->col)
		tbl->opts.cols = p->col + 1;

	return p;
}
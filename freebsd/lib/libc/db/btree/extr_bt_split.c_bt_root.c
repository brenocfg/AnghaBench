#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* pgno_t ;
typedef  int /*<<< orphan*/  indx_t ;
struct TYPE_16__ {int /*<<< orphan*/  bt_psize; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; void* nextpg; void* prevpg; void* pgno; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  BTDATAOFF ; 
 void* P_INVALID ; 
 int P_TYPE ; 
 TYPE_1__* __bt_new (TYPE_2__*,void**) ; 
 TYPE_1__* bt_psplit (TYPE_2__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bt_rootsplit ; 
 int /*<<< orphan*/  bt_split ; 

__attribute__((used)) static PAGE *
bt_root(BTREE *t, PAGE *h, PAGE **lp, PAGE **rp, indx_t *skip, size_t ilen)
{
	PAGE *l, *r, *tp;
	pgno_t lnpg, rnpg;

#ifdef STATISTICS
	++bt_split;
	++bt_rootsplit;
#endif
	/* Put the new left and right pages for the split into place. */
	if ((l = __bt_new(t, &lnpg)) == NULL ||
	    (r = __bt_new(t, &rnpg)) == NULL)
		return (NULL);
	l->pgno = lnpg;
	r->pgno = rnpg;
	l->nextpg = r->pgno;
	r->prevpg = l->pgno;
	l->prevpg = r->nextpg = P_INVALID;
	l->lower = r->lower = BTDATAOFF;
	l->upper = r->upper = t->bt_psize;
	l->flags = r->flags = h->flags & P_TYPE;

	/* Split the root page. */
	tp = bt_psplit(t, h, l, r, skip, ilen);

	*lp = l;
	*rp = r;
	return (tp);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  pgno_t ;
typedef  scalar_t__ indx_t ;
typedef  enum SRCHOP { ____Placeholder_SRCHOP } SRCHOP ;
struct TYPE_20__ {scalar_t__ index; TYPE_2__* page; } ;
struct TYPE_21__ {int /*<<< orphan*/  bt_mp; TYPE_4__ bt_cur; } ;
struct TYPE_19__ {scalar_t__ index; int /*<<< orphan*/  pgno; } ;
struct TYPE_18__ {int flags; } ;
struct TYPE_17__ {scalar_t__ nrecs; int /*<<< orphan*/  pgno; } ;
typedef  TYPE_1__ RINTERNAL ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ EPGNO ;
typedef  TYPE_4__ EPG ;
typedef  TYPE_5__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLR (TYPE_5__*) ; 
 TYPE_3__* BT_POP (TYPE_5__*) ; 
 int /*<<< orphan*/  BT_PUSH (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* GETRINTERNAL (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 scalar_t__ NEXTINDEX (TYPE_2__*) ; 
 int P_RLEAF ; 
 int /*<<< orphan*/  P_ROOT ; 
#define  SDELETE 130 
#define  SEARCH 129 
#define  SINSERT 128 
 int errno ; 
 TYPE_2__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

EPG *
__rec_search(BTREE *t, recno_t recno, enum SRCHOP op)
{
	indx_t idx;
	PAGE *h;
	EPGNO *parent;
	RINTERNAL *r;
	pgno_t pg;
	indx_t top;
	recno_t total;
	int sverrno;

	BT_CLR(t);
	for (pg = P_ROOT, total = 0;;) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
			goto err;
		if (h->flags & P_RLEAF) {
			t->bt_cur.page = h;
			t->bt_cur.index = recno - total;
			return (&t->bt_cur);
		}
		for (idx = 0, top = NEXTINDEX(h);;) {
			r = GETRINTERNAL(h, idx);
			if (++idx == top || total + r->nrecs > recno)
				break;
			total += r->nrecs;
		}

		BT_PUSH(t, pg, idx - 1);

		pg = r->pgno;
		switch (op) {
		case SDELETE:
			--GETRINTERNAL(h, (idx - 1))->nrecs;
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		case SINSERT:
			++GETRINTERNAL(h, (idx - 1))->nrecs;
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		case SEARCH:
			mpool_put(t->bt_mp, h, 0);
			break;
		}

	}
	/* Try and recover the tree. */
err:	sverrno = errno;
	if (op != SEARCH)
		while  ((parent = BT_POP(t)) != NULL) {
			if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
				break;
			if (op == SINSERT)
				--GETRINTERNAL(h, parent->index)->nrecs;
			else
				++GETRINTERNAL(h, parent->index)->nrecs;
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
		}
	errno = sverrno;
	return (NULL);
}
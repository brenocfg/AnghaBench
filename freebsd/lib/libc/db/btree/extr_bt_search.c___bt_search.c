#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgno_t ;
typedef  int indx_t ;
struct TYPE_22__ {int index; TYPE_1__* page; } ;
struct TYPE_23__ {int /*<<< orphan*/  bt_mp; TYPE_2__ bt_cur; } ;
struct TYPE_21__ {int flags; scalar_t__ prevpg; scalar_t__ nextpg; int /*<<< orphan*/  pgno; } ;
struct TYPE_20__ {int /*<<< orphan*/  pgno; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ EPG ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLR (TYPE_3__*) ; 
 int /*<<< orphan*/  BT_PUSH (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  B_NODUPS ; 
 int /*<<< orphan*/  F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_15__* GETBINTERNAL (TYPE_1__*,int) ; 
 int NEXTINDEX (TYPE_1__*) ; 
 int P_BLEAF ; 
 scalar_t__ P_INVALID ; 
 int /*<<< orphan*/  P_ROOT ; 
 int __bt_cmp (TYPE_3__*,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 scalar_t__ __bt_snext (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/  const*,int*) ; 
 scalar_t__ __bt_sprev (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/  const*,int*) ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

EPG *
__bt_search(BTREE *t, const DBT *key, int *exactp)
{
	PAGE *h;
	indx_t base, idx, lim;
	pgno_t pg;
	int cmp;

	BT_CLR(t);
	for (pg = P_ROOT;;) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
			return (NULL);

		/* Do a binary search on the current page. */
		t->bt_cur.page = h;
		for (base = 0, lim = NEXTINDEX(h); lim; lim >>= 1) {
			t->bt_cur.index = idx = base + (lim >> 1);
			if ((cmp = __bt_cmp(t, key, &t->bt_cur)) == 0) {
				if (h->flags & P_BLEAF) {
					*exactp = 1;
					return (&t->bt_cur);
				}
				goto next;
			}
			if (cmp > 0) {
				base = idx + 1;
				--lim;
			}
		}

		/*
		 * If it's a leaf page, we're almost done.  If no duplicates
		 * are allowed, or we have an exact match, we're done.  Else,
		 * it's possible that there were matching keys on this page,
		 * which later deleted, and we're on a page with no matches
		 * while there are matches on other pages.  If at the start or
		 * end of a page, check the adjacent page.
		 */
		if (h->flags & P_BLEAF) {
			if (!F_ISSET(t, B_NODUPS)) {
				if (base == 0 &&
				    h->prevpg != P_INVALID &&
				    __bt_sprev(t, h, key, exactp))
					return (&t->bt_cur);
				if (base == NEXTINDEX(h) &&
				    h->nextpg != P_INVALID &&
				    __bt_snext(t, h, key, exactp))
					return (&t->bt_cur);
			}
			*exactp = 0;
			t->bt_cur.index = base;
			return (&t->bt_cur);
		}

		/*
		 * No match found.  Base is the smallest index greater than
		 * key and may be zero or a last + 1 index.  If it's non-zero,
		 * decrement by one, and record the internal page which should
		 * be a parent page for the key.  If a split later occurs, the
		 * inserted page will be to the right of the saved page.
		 */
		idx = base ? base - 1 : base;

next:		BT_PUSH(t, h->pgno, idx);
		pg = GETBINTERNAL(h, idx)->pgno;
		mpool_put(t->bt_mp, h, 0);
	}
}
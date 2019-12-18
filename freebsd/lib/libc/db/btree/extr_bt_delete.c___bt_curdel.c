#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_18__ {scalar_t__ index; int /*<<< orphan*/  pgno; } ;
struct TYPE_21__ {int /*<<< orphan*/  key; TYPE_1__ pg; } ;
struct TYPE_22__ {int /*<<< orphan*/  bt_mp; TYPE_4__ bt_cursor; } ;
struct TYPE_20__ {scalar_t__ index; TYPE_2__* page; } ;
struct TYPE_19__ {scalar_t__ prevpg; scalar_t__ nextpg; int /*<<< orphan*/  pgno; } ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ EPG ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_4__ CURSOR ;
typedef  TYPE_5__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_NODUPS ; 
 int CURS_ACQUIRE ; 
 int CURS_AFTER ; 
 int CURS_BEFORE ; 
 int /*<<< orphan*/  F_CLR (TYPE_4__*,int) ; 
 int /*<<< orphan*/  F_ISSET (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_4__*,int) ; 
 scalar_t__ NEXTINDEX (TYPE_2__*) ; 
 scalar_t__ P_INVALID ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ __bt_cmp (TYPE_5__*,int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int __bt_ret (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* mpool_get (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__bt_curdel(BTREE *t, const DBT *key, PAGE *h, u_int idx)
{
	CURSOR *c;
	EPG e;
	PAGE *pg;
	int curcopy, status;

	/*
	 * If there are duplicates, move forward or backward to one.
	 * Otherwise, copy the key into the cursor area.
	 */
	c = &t->bt_cursor;
	F_CLR(c, CURS_AFTER | CURS_BEFORE | CURS_ACQUIRE);

	curcopy = 0;
	if (!F_ISSET(t, B_NODUPS)) {
		/*
		 * We're going to have to do comparisons.  If we weren't
		 * provided a copy of the key, i.e. the user is deleting
		 * the current cursor position, get one.
		 */
		if (key == NULL) {
			e.page = h;
			e.index = idx;
			if ((status = __bt_ret(t, &e,
			    &c->key, &c->key, NULL, NULL, 1)) != RET_SUCCESS)
				return (status);
			curcopy = 1;
			key = &c->key;
		}
		/* Check previous key, if not at the beginning of the page. */
		if (idx > 0) {
			e.page = h;
			e.index = idx - 1;
			if (__bt_cmp(t, key, &e) == 0) {
				F_SET(c, CURS_BEFORE);
				goto dup2;
			}
		}
		/* Check next key, if not at the end of the page. */
		if (idx < NEXTINDEX(h) - 1) {
			e.page = h;
			e.index = idx + 1;
			if (__bt_cmp(t, key, &e) == 0) {
				F_SET(c, CURS_AFTER);
				goto dup2;
			}
		}
		/* Check previous key if at the beginning of the page. */
		if (idx == 0 && h->prevpg != P_INVALID) {
			if ((pg = mpool_get(t->bt_mp, h->prevpg, 0)) == NULL)
				return (RET_ERROR);
			e.page = pg;
			e.index = NEXTINDEX(pg) - 1;
			if (__bt_cmp(t, key, &e) == 0) {
				F_SET(c, CURS_BEFORE);
				goto dup1;
			}
			mpool_put(t->bt_mp, pg, 0);
		}
		/* Check next key if at the end of the page. */
		if (idx == NEXTINDEX(h) - 1 && h->nextpg != P_INVALID) {
			if ((pg = mpool_get(t->bt_mp, h->nextpg, 0)) == NULL)
				return (RET_ERROR);
			e.page = pg;
			e.index = 0;
			if (__bt_cmp(t, key, &e) == 0) {
				F_SET(c, CURS_AFTER);
dup1:				mpool_put(t->bt_mp, pg, 0);
dup2:				c->pg.pgno = e.page->pgno;
				c->pg.index = e.index;
				return (RET_SUCCESS);
			}
			mpool_put(t->bt_mp, pg, 0);
		}
	}
	e.page = h;
	e.index = idx;
	if (curcopy || (status =
	    __bt_ret(t, &e, &c->key, &c->key, NULL, NULL, 1)) == RET_SUCCESS) {
		F_SET(c, CURS_ACQUIRE);
		return (RET_SUCCESS);
	}
	return (status);
}
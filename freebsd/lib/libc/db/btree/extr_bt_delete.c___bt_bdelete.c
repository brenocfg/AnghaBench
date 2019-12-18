#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bt_mp; } ;
struct TYPE_11__ {scalar_t__ index; int /*<<< orphan*/ * page; } ;
typedef  int /*<<< orphan*/  PAGE ;
typedef  TYPE_1__ EPG ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_NODUPS ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 scalar_t__ NEXTINDEX (int /*<<< orphan*/ *) ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 int RET_SUCCESS ; 
 scalar_t__ __bt_cmp (TYPE_2__*,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int __bt_dleaf (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ __bt_pdelete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* __bt_search (TYPE_2__*,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__bt_bdelete(BTREE *t, const DBT *key)
{
	EPG *e;
	PAGE *h;
	int deleted, exact, redo;

	deleted = 0;

	/* Find any matching record; __bt_search pins the page. */
loop:	if ((e = __bt_search(t, key, &exact)) == NULL)
		return (deleted ? RET_SUCCESS : RET_ERROR);
	if (!exact) {
		mpool_put(t->bt_mp, e->page, 0);
		return (deleted ? RET_SUCCESS : RET_SPECIAL);
	}

	/*
	 * Delete forward, then delete backward, from the found key.  If
	 * there are duplicates and we reach either side of the page, do
	 * the key search again, so that we get them all.
	 */
	redo = 0;
	h = e->page;
	do {
		if (__bt_dleaf(t, key, h, e->index)) {
			mpool_put(t->bt_mp, h, 0);
			return (RET_ERROR);
		}
		if (F_ISSET(t, B_NODUPS)) {
			if (NEXTINDEX(h) == 0) {
				if (__bt_pdelete(t, h))
					return (RET_ERROR);
			} else
				mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			return (RET_SUCCESS);
		}
		deleted = 1;
	} while (e->index < NEXTINDEX(h) && __bt_cmp(t, key, e) == 0);

	/* Check for right-hand edge of the page. */
	if (e->index == NEXTINDEX(h))
		redo = 1;

	/* Delete from the key to the beginning of the page. */
	while (e->index-- > 0) {
		if (__bt_cmp(t, key, e) != 0)
			break;
		if (__bt_dleaf(t, key, h, e->index) == RET_ERROR) {
			mpool_put(t->bt_mp, h, 0);
			return (RET_ERROR);
		}
		if (e->index == 0)
			redo = 1;
	}

	/* Check for an empty page. */
	if (NEXTINDEX(h) == 0) {
		if (__bt_pdelete(t, h))
			return (RET_ERROR);
		goto loop;
	}

	/* Put the page. */
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);

	if (redo)
		goto loop;
	return (RET_SUCCESS);
}
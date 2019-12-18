#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
typedef  scalar_t__ pgno_t ;
typedef  int indx_t ;
struct TYPE_27__ {scalar_t__ pgno; } ;
struct TYPE_26__ {int /*<<< orphan*/  bt_mp; } ;
struct TYPE_21__ {scalar_t__ pgno; } ;
struct TYPE_25__ {TYPE_1__ pg; int /*<<< orphan*/  key; } ;
struct TYPE_24__ {TYPE_2__* page; } ;
struct TYPE_23__ {scalar_t__ pgno; int index; } ;
struct TYPE_22__ {scalar_t__ pgno; scalar_t__ nextpg; scalar_t__ prevpg; } ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ EPGNO ;
typedef  TYPE_4__ EPG ;
typedef  TYPE_5__ CURSOR ;
typedef  TYPE_6__ BTREE ;
typedef  TYPE_7__ BINTERNAL ;

/* Variables and functions */
 TYPE_3__* BT_POP (TYPE_6__*) ; 
 int /*<<< orphan*/  BT_PUSH (TYPE_6__*,scalar_t__,int) ; 
 TYPE_7__* GETBINTERNAL (TYPE_2__*,int) ; 
 int NEXTINDEX (TYPE_2__*) ; 
 scalar_t__ P_INVALID ; 
 TYPE_4__* __bt_search (TYPE_6__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* mpool_get (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__bt_stkacq(BTREE *t, PAGE **hp, CURSOR *c)
{
	BINTERNAL *bi;
	EPG *e;
	EPGNO *parent;
	PAGE *h;
	indx_t idx;
	pgno_t pgno;
	recno_t nextpg, prevpg;
	int exact, level;

	/*
	 * Find the first occurrence of the key in the tree.  Toss the
	 * currently locked page so we don't hit an already-locked page.
	 */
	h = *hp;
	mpool_put(t->bt_mp, h, 0);
	if ((e = __bt_search(t, &c->key, &exact)) == NULL)
		return (1);
	h = e->page;

	/* See if we got it in one shot. */
	if (h->pgno == c->pg.pgno)
		goto ret;

	/*
	 * Move right, looking for the page.  At each move we have to move
	 * up the stack until we don't have to move to the next page.  If
	 * we have to change pages at an internal level, we have to fix the
	 * stack back up.
	 */
	while (h->pgno != c->pg.pgno) {
		if ((nextpg = h->nextpg) == P_INVALID)
			break;
		mpool_put(t->bt_mp, h, 0);

		/* Move up the stack. */
		for (level = 0; (parent = BT_POP(t)) != NULL; ++level) {
			/* Get the parent page. */
			if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
				return (1);

			/* Move to the next index. */
			if (parent->index != NEXTINDEX(h) - 1) {
				idx = parent->index + 1;
				BT_PUSH(t, h->pgno, idx);
				break;
			}
			mpool_put(t->bt_mp, h, 0);
		}

		/* Restore the stack. */
		while (level--) {
			/* Push the next level down onto the stack. */
			bi = GETBINTERNAL(h, idx);
			pgno = bi->pgno;
			BT_PUSH(t, pgno, 0);

			/* Lose the currently pinned page. */
			mpool_put(t->bt_mp, h, 0);

			/* Get the next level down. */
			if ((h = mpool_get(t->bt_mp, pgno, 0)) == NULL)
				return (1);
			idx = 0;
		}
		mpool_put(t->bt_mp, h, 0);
		if ((h = mpool_get(t->bt_mp, nextpg, 0)) == NULL)
			return (1);
	}

	if (h->pgno == c->pg.pgno)
		goto ret;

	/* Reacquire the original stack. */
	mpool_put(t->bt_mp, h, 0);
	if ((e = __bt_search(t, &c->key, &exact)) == NULL)
		return (1);
	h = e->page;

	/*
	 * Move left, looking for the page.  At each move we have to move
	 * up the stack until we don't have to change pages to move to the
	 * next page.  If we have to change pages at an internal level, we
	 * have to fix the stack back up.
	 */
	while (h->pgno != c->pg.pgno) {
		if ((prevpg = h->prevpg) == P_INVALID)
			break;
		mpool_put(t->bt_mp, h, 0);

		/* Move up the stack. */
		for (level = 0; (parent = BT_POP(t)) != NULL; ++level) {
			/* Get the parent page. */
			if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
				return (1);

			/* Move to the next index. */
			if (parent->index != 0) {
				idx = parent->index - 1;
				BT_PUSH(t, h->pgno, idx);
				break;
			}
			mpool_put(t->bt_mp, h, 0);
		}

		/* Restore the stack. */
		while (level--) {
			/* Push the next level down onto the stack. */
			bi = GETBINTERNAL(h, idx);
			pgno = bi->pgno;

			/* Lose the currently pinned page. */
			mpool_put(t->bt_mp, h, 0);

			/* Get the next level down. */
			if ((h = mpool_get(t->bt_mp, pgno, 0)) == NULL)
				return (1);

			idx = NEXTINDEX(h) - 1;
			BT_PUSH(t, pgno, idx);
		}
		mpool_put(t->bt_mp, h, 0);
		if ((h = mpool_get(t->bt_mp, prevpg, 0)) == NULL)
			return (1);
	}


ret:	mpool_put(t->bt_mp, h, 0);
	return ((*hp = mpool_get(t->bt_mp, c->pg.pgno, 0)) == NULL);
}
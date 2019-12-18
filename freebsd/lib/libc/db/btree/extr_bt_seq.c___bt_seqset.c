#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgno_t ;
struct TYPE_20__ {int /*<<< orphan*/  bt_mp; } ;
struct TYPE_19__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {int /*<<< orphan*/  index; TYPE_1__* page; } ;
struct TYPE_17__ {int flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  pgno; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ EPG ;
typedef  TYPE_3__ DBT ;
typedef  TYPE_4__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 TYPE_14__* GETBINTERNAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXTINDEX (TYPE_1__*) ; 
 int P_BLEAF ; 
 int P_RLEAF ; 
 int /*<<< orphan*/  P_ROOT ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 int RET_SUCCESS ; 
#define  R_CURSOR 132 
#define  R_FIRST 131 
#define  R_LAST 130 
#define  R_NEXT 129 
#define  R_PREV 128 
 int __bt_first (TYPE_4__*,TYPE_3__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__bt_seqset(BTREE *t, EPG *ep, DBT *key, int flags)
{
	PAGE *h;
	pgno_t pg;
	int exact;

	/*
	 * Find the first, last or specific key in the tree and point the
	 * cursor at it.  The cursor may not be moved until a new key has
	 * been found.
	 */
	switch (flags) {
	case R_CURSOR:				/* Keyed scan. */
		/*
		 * Find the first instance of the key or the smallest key
		 * which is greater than or equal to the specified key.
		 */
		if (key->data == NULL || key->size == 0) {
			errno = EINVAL;
			return (RET_ERROR);
		}
		return (__bt_first(t, key, ep, &exact));
	case R_FIRST:				/* First record. */
	case R_NEXT:
		/* Walk down the left-hand side of the tree. */
		for (pg = P_ROOT;;) {
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
				return (RET_ERROR);

			/* Check for an empty tree. */
			if (NEXTINDEX(h) == 0) {
				mpool_put(t->bt_mp, h, 0);
				return (RET_SPECIAL);
			}

			if (h->flags & (P_BLEAF | P_RLEAF))
				break;
			pg = GETBINTERNAL(h, 0)->pgno;
			mpool_put(t->bt_mp, h, 0);
		}
		ep->page = h;
		ep->index = 0;
		break;
	case R_LAST:				/* Last record. */
	case R_PREV:
		/* Walk down the right-hand side of the tree. */
		for (pg = P_ROOT;;) {
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
				return (RET_ERROR);

			/* Check for an empty tree. */
			if (NEXTINDEX(h) == 0) {
				mpool_put(t->bt_mp, h, 0);
				return (RET_SPECIAL);
			}

			if (h->flags & (P_BLEAF | P_RLEAF))
				break;
			pg = GETBINTERNAL(h, NEXTINDEX(h) - 1)->pgno;
			mpool_put(t->bt_mp, h, 0);
		}

		ep->page = h;
		ep->index = NEXTINDEX(h) - 1;
		break;
	}
	return (RET_SUCCESS);
}
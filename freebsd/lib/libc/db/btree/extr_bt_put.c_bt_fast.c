#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  indx_t ;
struct TYPE_18__ {int index; TYPE_2__* page; } ;
struct TYPE_16__ {int index; int /*<<< orphan*/  pgno; } ;
struct TYPE_20__ {scalar_t__ bt_order; int /*<<< orphan*/  bt_mp; TYPE_3__ bt_cur; TYPE_1__ bt_last; } ;
struct TYPE_19__ {int /*<<< orphan*/  size; } ;
struct TYPE_17__ {scalar_t__ nextpg; scalar_t__ prevpg; scalar_t__ lower; scalar_t__ upper; } ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ EPG ;
typedef  TYPE_4__ DBT ;
typedef  TYPE_5__ BTREE ;

/* Variables and functions */
 scalar_t__ FORWARD ; 
 scalar_t__ NBLEAFDBT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NEXTINDEX (TYPE_2__*) ; 
 void* NOT ; 
 scalar_t__ P_INVALID ; 
 int __bt_cmp (TYPE_5__*,TYPE_4__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  bt_cache_hit ; 
 int /*<<< orphan*/  bt_cache_miss ; 
 TYPE_2__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static EPG *
bt_fast(BTREE *t, const DBT *key, const DBT *data, int *exactp)
{
	PAGE *h;
	u_int32_t nbytes;
	int cmp;

	if ((h = mpool_get(t->bt_mp, t->bt_last.pgno, 0)) == NULL) {
		t->bt_order = NOT;
		return (NULL);
	}
	t->bt_cur.page = h;
	t->bt_cur.index = t->bt_last.index;

	/*
	 * If won't fit in this page or have too many keys in this page,
	 * have to search to get split stack.
	 */
	nbytes = NBLEAFDBT(key->size, data->size);
	if ((u_int32_t)(h->upper - h->lower) < nbytes + sizeof(indx_t))
		goto miss;

	if (t->bt_order == FORWARD) {
		if (t->bt_cur.page->nextpg != P_INVALID)
			goto miss;
		if (t->bt_cur.index != NEXTINDEX(h) - 1)
			goto miss;
		if ((cmp = __bt_cmp(t, key, &t->bt_cur)) < 0)
			goto miss;
		t->bt_last.index = cmp ? ++t->bt_cur.index : t->bt_cur.index;
	} else {
		if (t->bt_cur.page->prevpg != P_INVALID)
			goto miss;
		if (t->bt_cur.index != 0)
			goto miss;
		if ((cmp = __bt_cmp(t, key, &t->bt_cur)) > 0)
			goto miss;
		t->bt_last.index = 0;
	}
	*exactp = cmp == 0;
#ifdef STATISTICS
	++bt_cache_hit;
#endif
	return (&t->bt_cur);

miss:
#ifdef STATISTICS
	++bt_cache_miss;
#endif
	t->bt_order = NOT;
	mpool_put(t->bt_mp, h, 0);
	return (NULL);
}
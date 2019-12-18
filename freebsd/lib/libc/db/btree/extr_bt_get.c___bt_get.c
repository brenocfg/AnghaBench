#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_12__ {int /*<<< orphan*/ * bt_pinned; int /*<<< orphan*/  bt_mp; int /*<<< orphan*/  bt_rdata; } ;
struct TYPE_11__ {TYPE_3__* internal; } ;
struct TYPE_10__ {int /*<<< orphan*/ * page; } ;
typedef  TYPE_1__ EPG ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_2__ DB ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_DB_LOCK ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 int __bt_ret (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* __bt_search (TYPE_3__*,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
__bt_get(const DB *dbp, const DBT *key, DBT *data, u_int flags)
{
	BTREE *t;
	EPG *e;
	int exact, status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* Get currently doesn't take any flags. */
	if (flags) {
		errno = EINVAL;
		return (RET_ERROR);
	}

	if ((e = __bt_search(t, key, &exact)) == NULL)
		return (RET_ERROR);
	if (!exact) {
		mpool_put(t->bt_mp, e->page, 0);
		return (RET_SPECIAL);
	}

	status = __bt_ret(t, e, NULL, NULL, data, &t->bt_rdata, 0);

	/*
	 * If the user is doing concurrent access, we copied the
	 * key/data, toss the page.
	 */
	if (F_ISSET(t, B_DB_LOCK))
		mpool_put(t->bt_mp, e->page, 0);
	else
		t->bt_pinned = e->page;
	return (status);
}
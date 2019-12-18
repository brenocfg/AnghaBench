#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  scalar_t__ recno_t ;
struct TYPE_18__ {scalar_t__ bt_nrecs; int (* bt_irec ) (TYPE_4__*,scalar_t__) ;int /*<<< orphan*/ * bt_pinned; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_17__ {TYPE_4__* internal; } ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {int /*<<< orphan*/ * page; } ;
typedef  TYPE_1__ EPG ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ DB ;
typedef  TYPE_4__ BTREE ;

/* Variables and functions */
 int B_DB_LOCK ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ F_ISSET (TYPE_4__*,int) ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 int RET_SUCCESS ; 
 int R_EOF ; 
 int R_INMEM ; 
 int /*<<< orphan*/  SEARCH ; 
 int __rec_ret (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* __rec_search (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,scalar_t__) ; 

int
__rec_get(const DB *dbp, const DBT *key, DBT *data, u_int flags)
{
	BTREE *t;
	EPG *e;
	recno_t nrec;
	int status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* Get currently doesn't take any flags, and keys of 0 are illegal. */
	if (flags || (nrec = *(recno_t *)key->data) == 0) {
		errno = EINVAL;
		return (RET_ERROR);
	}

	/*
	 * If we haven't seen this record yet, try to find it in the
	 * original file.
	 */
	if (nrec > t->bt_nrecs) {
		if (F_ISSET(t, R_EOF | R_INMEM))
			return (RET_SPECIAL);
		if ((status = t->bt_irec(t, nrec)) != RET_SUCCESS)
			return (status);
	}

	--nrec;
	if ((e = __rec_search(t, nrec, SEARCH)) == NULL)
		return (RET_ERROR);

	status = __rec_ret(t, e, 0, NULL, data);
	if (F_ISSET(t, B_DB_LOCK))
		mpool_put(t->bt_mp, e->page, 0);
	else
		t->bt_pinned = e->page;
	return (status);
}
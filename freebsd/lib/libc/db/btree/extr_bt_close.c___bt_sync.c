#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_8__ {int /*<<< orphan*/  bt_mp; int /*<<< orphan*/ * bt_pinned; } ;
struct TYPE_7__ {TYPE_2__* internal; } ;
typedef  TYPE_1__ DB ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int B_INMEM ; 
 int B_METADIRTY ; 
 int B_MODIFIED ; 
 int B_RDONLY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int) ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 int bt_meta (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mpool_sync (int /*<<< orphan*/ ) ; 

int
__bt_sync(const DB *dbp, u_int flags)
{
	BTREE *t;
	int status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* Sync doesn't currently take any flags. */
	if (flags != 0) {
		errno = EINVAL;
		return (RET_ERROR);
	}

	if (F_ISSET(t, B_INMEM | B_RDONLY) ||
	    !F_ISSET(t, B_MODIFIED | B_METADIRTY))
		return (RET_SUCCESS);

	if (F_ISSET(t, B_METADIRTY) && bt_meta(t) == RET_ERROR)
		return (RET_ERROR);

	if ((status = mpool_sync(t->bt_mp)) == RET_SUCCESS)
		F_CLR(t, B_MODIFIED);

	return (status);
}
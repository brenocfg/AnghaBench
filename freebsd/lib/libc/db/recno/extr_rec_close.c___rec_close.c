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
struct TYPE_8__ {int /*<<< orphan*/  bt_rfd; int /*<<< orphan*/  bt_rfp; int /*<<< orphan*/  bt_msize; int /*<<< orphan*/  bt_smap; int /*<<< orphan*/ * bt_pinned; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_7__ {TYPE_2__* internal; } ;
typedef  TYPE_1__ DB ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 int /*<<< orphan*/  R_CLOSEFP ; 
 int /*<<< orphan*/  R_INMEM ; 
 int /*<<< orphan*/  R_MEMMAPPED ; 
 int __bt_close (TYPE_1__*) ; 
 int __rec_sync (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _close (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
__rec_close(DB *dbp)
{
	BTREE *t;
	int status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	if (__rec_sync(dbp, 0) == RET_ERROR)
		return (RET_ERROR);

	/* Committed to closing. */
	status = RET_SUCCESS;
	if (F_ISSET(t, R_MEMMAPPED) && munmap(t->bt_smap, t->bt_msize))
		status = RET_ERROR;

	if (!F_ISSET(t, R_INMEM)) {
		if (F_ISSET(t, R_CLOSEFP)) {
			if (fclose(t->bt_rfp))
				status = RET_ERROR;
		} else {
			if (_close(t->bt_rfd))
				status = RET_ERROR;
		}
	}

	if (__bt_close(dbp) == RET_ERROR)
		status = RET_ERROR;

	return (status);
}
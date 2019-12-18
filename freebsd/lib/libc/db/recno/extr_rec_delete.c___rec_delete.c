#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_12__ {int /*<<< orphan*/  rcursor; } ;
struct TYPE_11__ {TYPE_8__ bt_cursor; int /*<<< orphan*/  bt_nrecs; int /*<<< orphan*/ * bt_pinned; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_10__ {TYPE_3__* internal; } ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_1__ DBT ;
typedef  TYPE_2__ DB ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int B_MODIFIED ; 
 int /*<<< orphan*/  CURS_INIT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  F_ISSET (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int) ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 int RET_SUCCESS ; 
#define  R_CURSOR 128 
 int R_MODIFIED ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rec_rdelete (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
__rec_delete(const DB *dbp, const DBT *key, u_int flags)
{
	BTREE *t;
	recno_t nrec;
	int status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	switch(flags) {
	case 0:
		if ((nrec = *(recno_t *)key->data) == 0)
			goto einval;
		if (nrec > t->bt_nrecs)
			return (RET_SPECIAL);
		--nrec;
		status = rec_rdelete(t, nrec);
		break;
	case R_CURSOR:
		if (!F_ISSET(&t->bt_cursor, CURS_INIT))
			goto einval;
		if (t->bt_nrecs == 0)
			return (RET_SPECIAL);
		status = rec_rdelete(t, t->bt_cursor.rcursor - 1);
		if (status == RET_SUCCESS)
			--t->bt_cursor.rcursor;
		break;
	default:
einval:		errno = EINVAL;
		return (RET_ERROR);
	}

	if (status == RET_SUCCESS)
		F_SET(t, B_MODIFIED | R_MODIFIED);
	return (status);
}
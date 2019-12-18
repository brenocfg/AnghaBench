#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_15__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {TYPE_2__ bt_rdata; TYPE_1__ bt_rkey; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int /*<<< orphan*/  index; int /*<<< orphan*/  page; } ;
struct TYPE_16__ {int flags; int dsize; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_3__ RLEAF ;
typedef  TYPE_4__ EPG ;
typedef  TYPE_5__ DBT ;
typedef  TYPE_6__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_DB_LOCK ; 
 scalar_t__ F_ISSET (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* GETRLEAF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int P_BIGDATA ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ __ovfl_get (TYPE_6__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 

int
__rec_ret(BTREE *t, EPG *e, recno_t nrec, DBT *key, DBT *data)
{
	RLEAF *rl;
	void *p;

	if (key == NULL)
		goto dataonly;

	/* We have to copy the key, it's not on the page. */
	if (sizeof(recno_t) > t->bt_rkey.size) {
		p = realloc(t->bt_rkey.data, sizeof(recno_t));
		if (p == NULL)
			return (RET_ERROR);
		t->bt_rkey.data = p;
		t->bt_rkey.size = sizeof(recno_t);
	}
	memmove(t->bt_rkey.data, &nrec, sizeof(recno_t));
	key->size = sizeof(recno_t);
	key->data = t->bt_rkey.data;

dataonly:
	if (data == NULL)
		return (RET_SUCCESS);

	/*
	 * We must copy big keys/data to make them contigous.  Otherwise,
	 * leave the page pinned and don't copy unless the user specified
	 * concurrent access.
	 */
	rl = GETRLEAF(e->page, e->index);
	if (rl->flags & P_BIGDATA) {
		if (__ovfl_get(t, rl->bytes,
		    &data->size, &t->bt_rdata.data, &t->bt_rdata.size))
			return (RET_ERROR);
		data->data = t->bt_rdata.data;
	} else if (F_ISSET(t, B_DB_LOCK)) {
		/* Use +1 in case the first record retrieved is 0 length. */
		if (rl->dsize + 1 > t->bt_rdata.size) {
			p = realloc(t->bt_rdata.data, rl->dsize + 1);
			if (p == NULL)
				return (RET_ERROR);
			t->bt_rdata.data = p;
			t->bt_rdata.size = rl->dsize + 1;
		}
		memmove(t->bt_rdata.data, rl->bytes, rl->dsize);
		data->size = rl->dsize;
		data->data = t->bt_rdata.data;
	} else {
		data->size = rl->dsize;
		data->data = rl->bytes;
	}
	return (RET_SUCCESS);
}
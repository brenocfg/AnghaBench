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
struct TYPE_12__ {int flags; scalar_t__ bytes; scalar_t__ ksize; scalar_t__ dsize; } ;
struct TYPE_11__ {scalar_t__ size; scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ EPG ;
typedef  TYPE_2__ DBT ;
typedef  int /*<<< orphan*/  BTREE ;
typedef  TYPE_3__ BLEAF ;

/* Variables and functions */
 int /*<<< orphan*/  B_DB_LOCK ; 
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* GETBLEAF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int P_BIGDATA ; 
 int P_BIGKEY ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ __ovfl_get (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 void* realloc (scalar_t__,scalar_t__) ; 

int
__bt_ret(BTREE *t, EPG *e, DBT *key, DBT *rkey, DBT *data, DBT *rdata, int copy)
{
	BLEAF *bl;
	void *p;

	bl = GETBLEAF(e->page, e->index);

	/*
	 * We must copy big keys/data to make them contigous.  Otherwise,
	 * leave the page pinned and don't copy unless the user specified
	 * concurrent access.
	 */
	if (key == NULL)
		goto dataonly;

	if (bl->flags & P_BIGKEY) {
		if (__ovfl_get(t, bl->bytes,
		    &key->size, &rkey->data, &rkey->size))
			return (RET_ERROR);
		key->data = rkey->data;
	} else if (copy || F_ISSET(t, B_DB_LOCK)) {
		if (bl->ksize > rkey->size) {
			p = realloc(rkey->data, bl->ksize);
			if (p == NULL)
				return (RET_ERROR);
			rkey->data = p;
			rkey->size = bl->ksize;
		}
		memmove(rkey->data, bl->bytes, bl->ksize);
		key->size = bl->ksize;
		key->data = rkey->data;
	} else {
		key->size = bl->ksize;
		key->data = bl->bytes;
	}

dataonly:
	if (data == NULL)
		return (RET_SUCCESS);

	if (bl->flags & P_BIGDATA) {
		if (__ovfl_get(t, bl->bytes + bl->ksize,
		    &data->size, &rdata->data, &rdata->size))
			return (RET_ERROR);
		data->data = rdata->data;
	} else if (copy || F_ISSET(t, B_DB_LOCK)) {
		/* Use +1 in case the first record retrieved is 0 length. */
		if (bl->dsize + 1 > rdata->size) {
			p = realloc(rdata->data, bl->dsize + 1);
			if (p == NULL)
				return (RET_ERROR);
			rdata->data = p;
			rdata->size = bl->dsize + 1;
		}
		memmove(rdata->data, bl->bytes + bl->ksize, bl->dsize);
		data->size = bl->dsize;
		data->data = rdata->data;
	} else {
		data->size = bl->dsize;
		data->data = bl->bytes + bl->ksize;
	}

	return (RET_SUCCESS);
}
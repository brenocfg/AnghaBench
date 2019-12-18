#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
typedef  int /*<<< orphan*/  pgno_t ;
struct TYPE_11__ {int bt_psize; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_10__ {size_t size; void* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  pgno; int /*<<< orphan*/  nextpg; scalar_t__ upper; scalar_t__ lower; int /*<<< orphan*/  flags; int /*<<< orphan*/  prevpg; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int BTDATAOFF ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int /*<<< orphan*/  P_INVALID ; 
 int /*<<< orphan*/  P_OVERFLOW ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 TYPE_1__* __bt_new (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,void*,size_t) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
__ovfl_put(BTREE *t, const DBT *dbt, pgno_t *pg)
{
	PAGE *h, *last;
	void *p;
	pgno_t npg;
	size_t nb, plen;
	u_int32_t sz;

	/*
	 * Allocate pages and copy the key/data record into them.  Store the
	 * number of the first page in the chain.
	 */
	plen = t->bt_psize - BTDATAOFF;
	for (last = NULL, p = dbt->data, sz = dbt->size;;
	    p = (char *)p + plen, last = h) {
		if ((h = __bt_new(t, &npg)) == NULL)
			return (RET_ERROR);

		h->pgno = npg;
		h->nextpg = h->prevpg = P_INVALID;
		h->flags = P_OVERFLOW;
		h->lower = h->upper = 0;

		nb = MIN(sz, plen);
		memmove((char *)h + BTDATAOFF, p, nb);

		if (last) {
			last->nextpg = h->pgno;
			mpool_put(t->bt_mp, last, MPOOL_DIRTY);
		} else
			*pg = h->pgno;

		if ((sz -= nb) == 0) {
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		}
	}
	return (RET_SUCCESS);
}
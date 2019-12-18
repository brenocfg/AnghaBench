#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
typedef  scalar_t__ pgno_t ;
struct TYPE_7__ {int bt_psize; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_6__ {scalar_t__ nextpg; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ BTREE ;

/* Variables and functions */
 int BTDATAOFF ; 
 size_t MIN (size_t,size_t) ; 
 scalar_t__ P_INVALID ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memmove (void*,char*,size_t) ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* reallocf (void*,size_t) ; 

int
__ovfl_get(BTREE *t, void *p, size_t *ssz, void **buf, size_t *bufsz)
{
	PAGE *h;
	pgno_t pg;
	size_t nb, plen;
	u_int32_t sz;

	memmove(&pg, p, sizeof(pgno_t));
	memmove(&sz, (char *)p + sizeof(pgno_t), sizeof(u_int32_t));
	*ssz = sz;

#ifdef DEBUG
	if (pg == P_INVALID || sz == 0)
		abort();
#endif
	/* Make the buffer bigger as necessary. */
	if (*bufsz < sz) {
		*buf = reallocf(*buf, sz);
		if (*buf == NULL)
			return (RET_ERROR);
		*bufsz = sz;
	}

	/*
	 * Step through the linked list of pages, copying the data on each one
	 * into the buffer.  Never copy more than the data's length.
	 */
	plen = t->bt_psize - BTDATAOFF;
	for (p = *buf;; p = (char *)p + nb, pg = h->nextpg) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
			return (RET_ERROR);

		nb = MIN(sz, plen);
		memmove(p, (char *)h + BTDATAOFF, nb);
		mpool_put(t->bt_mp, h, 0);

		if ((sz -= nb) == 0)
			break;
	}
	return (RET_SUCCESS);
}
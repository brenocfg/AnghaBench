#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  size_t u_int ;
typedef  scalar_t__ indx_t ;
struct TYPE_19__ {int flags; scalar_t__ ksize; scalar_t__ bytes; } ;
struct TYPE_16__ {scalar_t__ pgno; size_t index; } ;
struct TYPE_15__ {TYPE_1__ pg; } ;
struct TYPE_18__ {TYPE_14__ bt_cursor; } ;
struct TYPE_17__ {scalar_t__ pgno; int upper; scalar_t__* linp; int lower; } ;
typedef  TYPE_2__ PAGE ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_3__ BTREE ;
typedef  TYPE_4__ BLEAF ;

/* Variables and functions */
 int /*<<< orphan*/  CURS_ACQUIRE ; 
 int /*<<< orphan*/  CURS_INIT ; 
 scalar_t__ F_ISSET (TYPE_14__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* GETBLEAF (TYPE_2__*,size_t) ; 
 int NBLEAF (TYPE_4__*) ; 
 size_t NEXTINDEX (TYPE_2__*) ; 
 int P_BIGDATA ; 
 int P_BIGKEY ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ __bt_curdel (TYPE_3__*,int /*<<< orphan*/  const*,TYPE_2__*,size_t) ; 
 int __ovfl_delete (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

int
__bt_dleaf(BTREE *t, const DBT *key, PAGE *h, u_int idx)
{
	BLEAF *bl;
	indx_t cnt, *ip, offset;
	u_int32_t nbytes;
	void *to;
	char *from;

	/* If this record is referenced by the cursor, delete the cursor. */
	if (F_ISSET(&t->bt_cursor, CURS_INIT) &&
	    !F_ISSET(&t->bt_cursor, CURS_ACQUIRE) &&
	    t->bt_cursor.pg.pgno == h->pgno && t->bt_cursor.pg.index == idx &&
	    __bt_curdel(t, key, h, idx))
		return (RET_ERROR);

	/* If the entry uses overflow pages, make them available for reuse. */
	to = bl = GETBLEAF(h, idx);
	if (bl->flags & P_BIGKEY && __ovfl_delete(t, bl->bytes) == RET_ERROR)
		return (RET_ERROR);
	if (bl->flags & P_BIGDATA &&
	    __ovfl_delete(t, bl->bytes + bl->ksize) == RET_ERROR)
		return (RET_ERROR);

	/* Pack the remaining key/data items at the end of the page. */
	nbytes = NBLEAF(bl);
	from = (char *)h + h->upper;
	memmove(from + nbytes, from, (char *)to - from);
	h->upper += nbytes;

	/* Adjust the indices' offsets, shift the indices down. */
	offset = h->linp[idx];
	for (cnt = idx, ip = &h->linp[0]; cnt--; ++ip)
		if (ip[0] < offset)
			ip[0] += nbytes;
	for (cnt = NEXTINDEX(h) - idx; --cnt; ++ip)
		ip[0] = ip[1] < offset ? ip[1] + nbytes : ip[1];
	h->lower -= sizeof(indx_t);

	/* If the cursor is on this page, adjust it as necessary. */
	if (F_ISSET(&t->bt_cursor, CURS_INIT) &&
	    !F_ISSET(&t->bt_cursor, CURS_ACQUIRE) &&
	    t->bt_cursor.pg.pgno == h->pgno && t->bt_cursor.pg.index > idx)
		--t->bt_cursor.pg.index;

	return (RET_SUCCESS);
}
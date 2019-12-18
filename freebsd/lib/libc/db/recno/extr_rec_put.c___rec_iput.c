#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int u_int ;
typedef  scalar_t__ recno_t ;
typedef  int /*<<< orphan*/  pgno_t ;
typedef  int /*<<< orphan*/  pg ;
typedef  int indx_t ;
struct TYPE_23__ {scalar_t__ bt_ovflsize; scalar_t__ bt_nrecs; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_22__ {scalar_t__ size; char* data; } ;
struct TYPE_21__ {int index; TYPE_1__* page; } ;
struct TYPE_20__ {scalar_t__ upper; scalar_t__ lower; scalar_t__* linp; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ EPG ;
typedef  TYPE_3__ DBT ;
typedef  TYPE_4__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  B_MODIFIED ; 
 int /*<<< orphan*/  F_SET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int NEXTINDEX (TYPE_1__*) ; 
 int NOVFLSIZE ; 
 scalar_t__ NRLEAFDBT (scalar_t__) ; 
 int P_BIGDATA ; 
 scalar_t__ RET_ERROR ; 
 int RET_SUCCESS ; 
#define  R_IAFTER 129 
#define  R_IBEFORE 128 
 int /*<<< orphan*/  SEARCH ; 
 int /*<<< orphan*/  SINSERT ; 
 int /*<<< orphan*/  WR_RLEAF (char*,TYPE_3__ const*,int) ; 
 int __bt_split (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__ const*,int,scalar_t__,int) ; 
 scalar_t__ __ovfl_put (TYPE_4__*,TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ __rec_dleaf (TYPE_4__*,TYPE_1__*,int) ; 
 TYPE_2__* __rec_search (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
__rec_iput(BTREE *t, recno_t nrec, const DBT *data, u_int flags)
{
	DBT tdata;
	EPG *e;
	PAGE *h;
	indx_t idx, nxtindex;
	pgno_t pg;
	u_int32_t nbytes;
	int dflags, status;
	char *dest, db[NOVFLSIZE];

	/*
	 * If the data won't fit on a page, store it on indirect pages.
	 *
	 * XXX
	 * If the insert fails later on, these pages aren't recovered.
	 */
	if (data->size > t->bt_ovflsize) {
		if (__ovfl_put(t, data, &pg) == RET_ERROR)
			return (RET_ERROR);
		tdata.data = db;
		tdata.size = NOVFLSIZE;
		memcpy(db, &pg, sizeof(pg));
		*(u_int32_t *)(db + sizeof(pgno_t)) = data->size;
		dflags = P_BIGDATA;
		data = &tdata;
	} else
		dflags = 0;

	/* __rec_search pins the returned page. */
	if ((e = __rec_search(t, nrec,
	    nrec > t->bt_nrecs || flags == R_IAFTER || flags == R_IBEFORE ?
	    SINSERT : SEARCH)) == NULL)
		return (RET_ERROR);

	h = e->page;
	idx = e->index;

	/*
	 * Add the specified key/data pair to the tree.  The R_IAFTER and
	 * R_IBEFORE flags insert the key after/before the specified key.
	 *
	 * Pages are split as required.
	 */
	switch (flags) {
	case R_IAFTER:
		++idx;
		break;
	case R_IBEFORE:
		break;
	default:
		if (nrec < t->bt_nrecs &&
		    __rec_dleaf(t, h, idx) == RET_ERROR) {
			mpool_put(t->bt_mp, h, 0);
			return (RET_ERROR);
		}
		break;
	}

	/*
	 * If not enough room, split the page.  The split code will insert
	 * the key and data and unpin the current page.  If inserting into
	 * the offset array, shift the pointers up.
	 */
	nbytes = NRLEAFDBT(data->size);
	if ((u_int32_t)(h->upper - h->lower) < nbytes + sizeof(indx_t)) {
		status = __bt_split(t, h, NULL, data, dflags, nbytes, idx);
		if (status == RET_SUCCESS)
			++t->bt_nrecs;
		return (status);
	}

	if (idx < (nxtindex = NEXTINDEX(h)))
		memmove(h->linp + idx + 1, h->linp + idx,
		    (nxtindex - idx) * sizeof(indx_t));
	h->lower += sizeof(indx_t);

	h->linp[idx] = h->upper -= nbytes;
	dest = (char *)h + h->upper;
	WR_RLEAF(dest, data, dflags);

	++t->bt_nrecs;
	F_SET(t, B_MODIFIED);
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);

	return (RET_SUCCESS);
}
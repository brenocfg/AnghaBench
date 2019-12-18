#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  size_t indx_t ;
struct TYPE_22__ {int flags; int /*<<< orphan*/  ksize; int /*<<< orphan*/  bytes; } ;
struct TYPE_21__ {int bt_psize; int /*<<< orphan*/  bt_mp; } ;
struct TYPE_20__ {size_t index; int /*<<< orphan*/  pgno; } ;
struct TYPE_19__ {scalar_t__ pgno; int lower; int upper; size_t* linp; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PAGE ;
typedef  TYPE_2__ EPGNO ;
typedef  TYPE_3__ BTREE ;
typedef  TYPE_4__ BINTERNAL ;

/* Variables and functions */
 int BTDATAOFF ; 
 TYPE_2__* BT_POP (TYPE_3__*) ; 
 TYPE_4__* GETBINTERNAL (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int NBINTERNAL (int /*<<< orphan*/ ) ; 
 size_t NEXTINDEX (TYPE_1__*) ; 
 int P_BIGKEY ; 
 int /*<<< orphan*/  P_BLEAF ; 
 scalar_t__ P_ROOT ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ __bt_free (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ __bt_relink (TYPE_3__*,TYPE_1__*) ; 
 int __ovfl_delete (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 TYPE_1__* mpool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpool_put (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__bt_pdelete(BTREE *t, PAGE *h)
{
	BINTERNAL *bi;
	PAGE *pg;
	EPGNO *parent;
	indx_t cnt, idx, *ip, offset;
	u_int32_t nksize;
	char *from;

	/*
	 * Walk the parent page stack -- a LIFO stack of the pages that were
	 * traversed when we searched for the page where the delete occurred.
	 * Each stack entry is a page number and a page index offset.  The
	 * offset is for the page traversed on the search.  We've just deleted
	 * a page, so we have to delete the key from the parent page.
	 *
	 * If the delete from the parent page makes it empty, this process may
	 * continue all the way up the tree.  We stop if we reach the root page
	 * (which is never deleted, it's just not worth the effort) or if the
	 * delete does not empty the page.
	 */
	while ((parent = BT_POP(t)) != NULL) {
		/* Get the parent page. */
		if ((pg = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
			return (RET_ERROR);

		idx = parent->index;
		bi = GETBINTERNAL(pg, idx);

		/* Free any overflow pages. */
		if (bi->flags & P_BIGKEY &&
		    __ovfl_delete(t, bi->bytes) == RET_ERROR) {
			mpool_put(t->bt_mp, pg, 0);
			return (RET_ERROR);
		}

		/*
		 * Free the parent if it has only the one key and it's not the
		 * root page. If it's the rootpage, turn it back into an empty
		 * leaf page.
		 */
		if (NEXTINDEX(pg) == 1) {
			if (pg->pgno == P_ROOT) {
				pg->lower = BTDATAOFF;
				pg->upper = t->bt_psize;
				pg->flags = P_BLEAF;
			} else {
				if (__bt_relink(t, pg) || __bt_free(t, pg))
					return (RET_ERROR);
				continue;
			}
		} else {
			/* Pack remaining key items at the end of the page. */
			nksize = NBINTERNAL(bi->ksize);
			from = (char *)pg + pg->upper;
			memmove(from + nksize, from, (char *)bi - from);
			pg->upper += nksize;

			/* Adjust indices' offsets, shift the indices down. */
			offset = pg->linp[idx];
			for (cnt = idx, ip = &pg->linp[0]; cnt--; ++ip)
				if (ip[0] < offset)
					ip[0] += nksize;
			for (cnt = NEXTINDEX(pg) - idx; --cnt; ++ip)
				ip[0] = ip[1] < offset ? ip[1] + nksize : ip[1];
			pg->lower -= sizeof(indx_t);
		}

		mpool_put(t->bt_mp, pg, MPOOL_DIRTY);
		break;
	}

	/* Free the leaf page, as long as it wasn't the root. */
	if (h->pgno == P_ROOT) {
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
		return (RET_SUCCESS);
	}
	return (__bt_relink(t, h) || __bt_free(t, h));
}
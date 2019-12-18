#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int indx_t ;
struct TYPE_26__ {int flags; int /*<<< orphan*/  ksize; } ;
struct TYPE_25__ {int flags; } ;
struct TYPE_21__ {scalar_t__ pgno; int index; } ;
struct TYPE_23__ {TYPE_1__ pg; } ;
struct TYPE_24__ {int bt_psize; TYPE_3__ bt_cursor; } ;
struct TYPE_22__ {int flags; int* linp; int upper; int lower; scalar_t__ pgno; } ;
typedef  int /*<<< orphan*/  RLEAF ;
typedef  TYPE_2__ PAGE ;
typedef  TYPE_3__ CURSOR ;
typedef  TYPE_4__ BTREE ;
typedef  TYPE_5__ BLEAF ;
typedef  TYPE_6__ BINTERNAL ;

/* Variables and functions */
 int BTDATAOFF ; 
 int /*<<< orphan*/  CURS_INIT ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* GETBINTERNAL (TYPE_2__*,int) ; 
 TYPE_5__* GETBLEAF (TYPE_2__*,int) ; 
 void* GETRINTERNAL (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * GETRLEAF (TYPE_2__*,int) ; 
 int MAX_PAGE_OFFSET ; 
 int NBINTERNAL (int /*<<< orphan*/ ) ; 
 int NBLEAF (TYPE_5__*) ; 
 int NEXTINDEX (TYPE_2__*) ; 
 int NRINTERNAL ; 
 int NRLEAF (int /*<<< orphan*/ *) ; 
 int P_BIGKEY ; 
#define  P_BINTERNAL 131 
#define  P_BLEAF 130 
#define  P_RINTERNAL 129 
#define  P_RLEAF 128 
 int P_TYPE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memmove (char*,void*,int) ; 

__attribute__((used)) static PAGE *
bt_psplit(BTREE *t, PAGE *h, PAGE *l, PAGE *r, indx_t *pskip, size_t ilen)
{
	BINTERNAL *bi;
	BLEAF *bl;
	CURSOR *c;
	RLEAF *rl;
	PAGE *rval;
	void *src;
	indx_t full, half, nxt, off, skip, top, used;
	u_int32_t nbytes;
	int bigkeycnt, isbigkey;

	/*
	 * Split the data to the left and right pages.  Leave the skip index
	 * open.  Additionally, make some effort not to split on an overflow
	 * key.  This makes internal page processing faster and can save
	 * space as overflow keys used by internal pages are never deleted.
	 */
	bigkeycnt = 0;
	skip = *pskip;
	full = t->bt_psize - BTDATAOFF;
	half = full / 2;
	used = 0;
	for (nxt = off = 0, top = NEXTINDEX(h); nxt < top; ++off) {
		if (skip == off) {
			nbytes = ilen;
			isbigkey = 0;		/* XXX: not really known. */
		} else
			switch (h->flags & P_TYPE) {
			case P_BINTERNAL:
				src = bi = GETBINTERNAL(h, nxt);
				nbytes = NBINTERNAL(bi->ksize);
				isbigkey = bi->flags & P_BIGKEY;
				break;
			case P_BLEAF:
				src = bl = GETBLEAF(h, nxt);
				nbytes = NBLEAF(bl);
				isbigkey = bl->flags & P_BIGKEY;
				break;
			case P_RINTERNAL:
				src = GETRINTERNAL(h, nxt);
				nbytes = NRINTERNAL;
				isbigkey = 0;
				break;
			case P_RLEAF:
				src = rl = GETRLEAF(h, nxt);
				nbytes = NRLEAF(rl);
				isbigkey = 0;
				break;
			default:
				abort();
			}

		/*
		 * If the key/data pairs are substantial fractions of the max
		 * possible size for the page, it's possible to get situations
		 * where we decide to try and copy too much onto the left page.
		 * Make sure that doesn't happen.
		 */
		if ((skip <= off && used + nbytes + sizeof(indx_t) >= full) ||
		    nxt == top - 1) {
			--off;
			break;
		}

		/* Copy the key/data pair, if not the skipped index. */
		if (skip != off) {
			++nxt;

			l->linp[off] = l->upper -= nbytes;
			memmove((char *)l + l->upper, src, nbytes);
		}

		used += nbytes + sizeof(indx_t);
		if (used >= half) {
			if (!isbigkey || bigkeycnt == 3)
				break;
			else
				++bigkeycnt;
		}
	}

	/*
	 * Off is the last offset that's valid for the left page.
	 * Nxt is the first offset to be placed on the right page.
	 */
	l->lower += (off + 1) * sizeof(indx_t);

	/*
	 * If splitting the page that the cursor was on, the cursor has to be
	 * adjusted to point to the same record as before the split.  If the
	 * cursor is at or past the skipped slot, the cursor is incremented by
	 * one.  If the cursor is on the right page, it is decremented by the
	 * number of records split to the left page.
	 */
	c = &t->bt_cursor;
	if (F_ISSET(c, CURS_INIT) && c->pg.pgno == h->pgno) {
		if (c->pg.index >= skip)
			++c->pg.index;
		if (c->pg.index < nxt)			/* Left page. */
			c->pg.pgno = l->pgno;
		else {					/* Right page. */
			c->pg.pgno = r->pgno;
			c->pg.index -= nxt;
		}
	}

	/*
	 * If the skipped index was on the left page, just return that page.
	 * Otherwise, adjust the skip index to reflect the new position on
	 * the right page.
	 */
	if (skip <= off) {
		skip = MAX_PAGE_OFFSET;
		rval = l;
	} else {
		rval = r;
		*pskip -= nxt;
	}

	for (off = 0; nxt < top; ++off) {
		if (skip == nxt) {
			++off;
			skip = MAX_PAGE_OFFSET;
		}
		switch (h->flags & P_TYPE) {
		case P_BINTERNAL:
			src = bi = GETBINTERNAL(h, nxt);
			nbytes = NBINTERNAL(bi->ksize);
			break;
		case P_BLEAF:
			src = bl = GETBLEAF(h, nxt);
			nbytes = NBLEAF(bl);
			break;
		case P_RINTERNAL:
			src = GETRINTERNAL(h, nxt);
			nbytes = NRINTERNAL;
			break;
		case P_RLEAF:
			src = rl = GETRLEAF(h, nxt);
			nbytes = NRLEAF(rl);
			break;
		default:
			abort();
		}
		++nxt;
		r->linp[off] = r->upper -= nbytes;
		memmove((char *)r + r->upper, src, nbytes);
	}
	r->lower += off * sizeof(indx_t);

	/* If the key is being appended to the page, adjust the index. */
	if (skip == top)
		r->lower += sizeof(indx_t);

	return (rval);
}
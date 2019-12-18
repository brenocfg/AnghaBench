#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_4__ {int MAX_BUCKET; int LOW_MASK; int SSHIFT; int nsegs; int DSIZE; int OVFL_POINT; int HIGH_MASK; int /*<<< orphan*/ * SPARES; int /*<<< orphan*/  exsegs; int /*<<< orphan*/  SGSIZE; int /*<<< orphan*/ ** dir; } ;
typedef  int /*<<< orphan*/  SEGMENT ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 int __log2 (int) ; 
 int __split_page (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hash_expansions ; 
 int /*<<< orphan*/  hash_realloc (int /*<<< orphan*/ ***,int,int) ; 

int
__expand_table(HTAB *hashp)
{
	u_int32_t old_bucket, new_bucket;
	int dirsize, new_segnum, spare_ndx;

#ifdef HASH_STATISTICS
	hash_expansions++;
#endif
	new_bucket = ++hashp->MAX_BUCKET;
	old_bucket = (hashp->MAX_BUCKET & hashp->LOW_MASK);

	new_segnum = new_bucket >> hashp->SSHIFT;

	/* Check if we need a new segment */
	if (new_segnum >= hashp->nsegs) {
		/* Check if we need to expand directory */
		if (new_segnum >= hashp->DSIZE) {
			/* Reallocate directory */
			dirsize = hashp->DSIZE * sizeof(SEGMENT *);
			if (!hash_realloc(&hashp->dir, dirsize, dirsize << 1))
				return (-1);
			hashp->DSIZE = dirsize << 1;
		}
		if ((hashp->dir[new_segnum] =
		    calloc(hashp->SGSIZE, sizeof(SEGMENT))) == NULL)
			return (-1);
		hashp->exsegs++;
		hashp->nsegs++;
	}
	/*
	 * If the split point is increasing (MAX_BUCKET's log base 2
	 * * increases), we need to copy the current contents of the spare
	 * split bucket to the next bucket.
	 */
	spare_ndx = __log2(hashp->MAX_BUCKET + 1);
	if (spare_ndx > hashp->OVFL_POINT) {
		hashp->SPARES[spare_ndx] = hashp->SPARES[hashp->OVFL_POINT];
		hashp->OVFL_POINT = spare_ndx;
	}

	if (new_bucket > hashp->HIGH_MASK) {
		/* Starting a new doubling */
		hashp->LOW_MASK = hashp->HIGH_MASK;
		hashp->HIGH_MASK = new_bucket | hashp->LOW_MASK;
	}
	/* Relocate records to the new bucket */
	return (__split_page(hashp, old_bucket, new_bucket));
}
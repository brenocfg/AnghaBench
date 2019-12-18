#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  ckhc_t ;
struct TYPE_3__ {int prng_state; unsigned int lg_minbuckets; unsigned int lg_curbuckets; int /*<<< orphan*/ * tab; int /*<<< orphan*/ * keycomp; int /*<<< orphan*/ * hash; scalar_t__ count; scalar_t__ nrelocs; scalar_t__ ninserts; scalar_t__ nshrinkfails; scalar_t__ nshrinks; scalar_t__ ngrows; } ;
typedef  TYPE_1__ ckh_t ;
typedef  int /*<<< orphan*/  ckh_keycomp_t ;
typedef  int /*<<< orphan*/  ckh_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 unsigned int LG_CKH_BUCKET_CELLS ; 
 size_t SC_LARGE_MAXCLASS ; 
 unsigned int ZU (int) ; 
 int /*<<< orphan*/  arena_ichoose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ipallocztm (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t sz_sa2u (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

bool
ckh_new(tsd_t *tsd, ckh_t *ckh, size_t minitems, ckh_hash_t *hash,
    ckh_keycomp_t *keycomp) {
	bool ret;
	size_t mincells, usize;
	unsigned lg_mincells;

	assert(minitems > 0);
	assert(hash != NULL);
	assert(keycomp != NULL);

#ifdef CKH_COUNT
	ckh->ngrows = 0;
	ckh->nshrinks = 0;
	ckh->nshrinkfails = 0;
	ckh->ninserts = 0;
	ckh->nrelocs = 0;
#endif
	ckh->prng_state = 42; /* Value doesn't really matter. */
	ckh->count = 0;

	/*
	 * Find the minimum power of 2 that is large enough to fit minitems
	 * entries.  We are using (2+,2) cuckoo hashing, which has an expected
	 * maximum load factor of at least ~0.86, so 0.75 is a conservative load
	 * factor that will typically allow mincells items to fit without ever
	 * growing the table.
	 */
	assert(LG_CKH_BUCKET_CELLS > 0);
	mincells = ((minitems + (3 - (minitems % 3))) / 3) << 2;
	for (lg_mincells = LG_CKH_BUCKET_CELLS;
	    (ZU(1) << lg_mincells) < mincells;
	    lg_mincells++) {
		/* Do nothing. */
	}
	ckh->lg_minbuckets = lg_mincells - LG_CKH_BUCKET_CELLS;
	ckh->lg_curbuckets = lg_mincells - LG_CKH_BUCKET_CELLS;
	ckh->hash = hash;
	ckh->keycomp = keycomp;

	usize = sz_sa2u(sizeof(ckhc_t) << lg_mincells, CACHELINE);
	if (unlikely(usize == 0 || usize > SC_LARGE_MAXCLASS)) {
		ret = true;
		goto label_return;
	}
	ckh->tab = (ckhc_t *)ipallocztm(tsd_tsdn(tsd), usize, CACHELINE, true,
	    NULL, true, arena_ichoose(tsd, NULL));
	if (ckh->tab == NULL) {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	return ret;
}
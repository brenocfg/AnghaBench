#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void const* data; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ ckhc_t ;
struct TYPE_5__ {int /*<<< orphan*/  count; TYPE_1__* tab; int /*<<< orphan*/  prng_state; } ;
typedef  TYPE_2__ ckh_t ;

/* Variables and functions */
 unsigned int LG_CKH_BUCKET_CELLS ; 
 unsigned int ZU (int) ; 
 scalar_t__ prng_lg_range_u64 (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool
ckh_try_bucket_insert(ckh_t *ckh, size_t bucket, const void *key,
    const void *data) {
	ckhc_t *cell;
	unsigned offset, i;

	/*
	 * Cycle through the cells in the bucket, starting at a random position.
	 * The randomness avoids worst-case search overhead as buckets fill up.
	 */
	offset = (unsigned)prng_lg_range_u64(&ckh->prng_state,
	    LG_CKH_BUCKET_CELLS);
	for (i = 0; i < (ZU(1) << LG_CKH_BUCKET_CELLS); i++) {
		cell = &ckh->tab[(bucket << LG_CKH_BUCKET_CELLS) +
		    ((i + offset) & ((ZU(1) << LG_CKH_BUCKET_CELLS) - 1))];
		if (cell->key == NULL) {
			cell->key = key;
			cell->data = data;
			ckh->count++;
			return false;
		}
	}

	return true;
}
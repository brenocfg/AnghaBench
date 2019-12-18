#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct biovec_slab {int /*<<< orphan*/  slab; } ;
struct bio_vec {int dummy; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_BUG_ON (int) ; 
 unsigned int BVEC_POOL_MAX ; 
 unsigned int BVEC_POOL_NR ; 
 struct biovec_slab* bvec_slabs ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bio_vec*) ; 
 int /*<<< orphan*/  mempool_free (struct bio_vec*,int /*<<< orphan*/ *) ; 

void bvec_free(mempool_t *pool, struct bio_vec *bv, unsigned int idx)
{
	if (!idx)
		return;
	idx--;

	BIO_BUG_ON(idx >= BVEC_POOL_NR);

	if (idx == BVEC_POOL_MAX) {
		mempool_free(bv, pool);
	} else {
		struct biovec_slab *bvs = bvec_slabs + idx;

		kmem_cache_free(bvs->slab, bv);
	}
}
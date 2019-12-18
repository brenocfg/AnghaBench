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
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int BVEC_POOL_MAX ; 
 struct biovec_slab* bvec_slabs ; 
 int mempool_init_slab_pool (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int biovec_init_pool(mempool_t *pool, int pool_entries)
{
	struct biovec_slab *bp = bvec_slabs + BVEC_POOL_MAX;

	return mempool_init_slab_pool(pool, pool_entries, bp->slab);
}
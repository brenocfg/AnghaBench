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
struct TYPE_4__ {TYPE_2__* l2_cache; TYPE_2__* cache; } ;
typedef  TYPE_1__ rtree_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/ * leaf; void* leafkey; } ;
typedef  TYPE_2__ rtree_ctx_cache_elm_t ;

/* Variables and functions */
 unsigned int RTREE_CTX_NCACHE ; 
 unsigned int RTREE_CTX_NCACHE_L2 ; 
 void* RTREE_LEAFKEY_INVALID ; 

void
rtree_ctx_data_init(rtree_ctx_t *ctx) {
	for (unsigned i = 0; i < RTREE_CTX_NCACHE; i++) {
		rtree_ctx_cache_elm_t *cache = &ctx->cache[i];
		cache->leafkey = RTREE_LEAFKEY_INVALID;
		cache->leaf = NULL;
	}
	for (unsigned i = 0; i < RTREE_CTX_NCACHE_L2; i++) {
		rtree_ctx_cache_elm_t *cache = &ctx->l2_cache[i];
		cache->leafkey = RTREE_LEAFKEY_INVALID;
		cache->leaf = NULL;
	}
}
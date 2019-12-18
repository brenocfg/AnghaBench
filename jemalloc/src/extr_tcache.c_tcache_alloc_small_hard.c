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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_4__ {int /*<<< orphan*/ * arena; } ;
typedef  TYPE_1__ tcache_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  cache_bin_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_tcache_fill_small (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* cache_bin_alloc_easy (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

void *
tcache_alloc_small_hard(tsdn_t *tsdn, arena_t *arena, tcache_t *tcache,
    cache_bin_t *tbin, szind_t binind, bool *tcache_success) {
	void *ret;

	assert(tcache->arena != NULL);
	arena_tcache_fill_small(tsdn, arena, tcache, tbin, binind);
	ret = cache_bin_alloc_easy(tbin, tcache_success, binind);

	return ret;
}
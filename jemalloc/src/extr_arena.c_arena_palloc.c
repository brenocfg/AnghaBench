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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t CACHELINE ; 
 size_t PAGE ; 
 size_t PAGE_MASK ; 
 size_t SC_SMALL_MAXCLASS ; 
 void* arena_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 void* large_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 void* large_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 

void *
arena_palloc(tsdn_t *tsdn, arena_t *arena, size_t usize, size_t alignment,
    bool zero, tcache_t *tcache) {
	void *ret;

	if (usize <= SC_SMALL_MAXCLASS
	    && (alignment < PAGE
	    || (alignment == PAGE && (usize & PAGE_MASK) == 0))) {
		/* Small; alignment doesn't require special slab placement. */
		ret = arena_malloc(tsdn, arena, usize, sz_size2index(usize),
		    zero, tcache, true);
	} else {
		if (likely(alignment <= CACHELINE)) {
			ret = large_malloc(tsdn, arena, usize, zero);
		} else {
			ret = large_palloc(tsdn, arena, usize, alignment, zero);
		}
	}
	return ret;
}
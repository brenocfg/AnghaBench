#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {void* e_addr; } ;
typedef  TYPE_1__ extent_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 void* ALIGNMENT_ADDR2BASE (void*,size_t) ; 
 int /*<<< orphan*/  CACHELINE_CEILING (size_t) ; 
 unsigned int LG_PAGE ; 
 size_t PAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ extent_addr_get (TYPE_1__*) ; 
 scalar_t__ extent_base_get (TYPE_1__*) ; 
 unsigned int lg_floor (int /*<<< orphan*/ ) ; 
 scalar_t__ prng_lg_range_u64 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * tsd_prng_statep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsdn_tsd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extent_addr_randomize(tsdn_t *tsdn, arena_t *arena, extent_t *extent,
    size_t alignment) {
	assert(extent_base_get(extent) == extent_addr_get(extent));

	if (alignment < PAGE) {
		unsigned lg_range = LG_PAGE -
		    lg_floor(CACHELINE_CEILING(alignment));
		size_t r;
		if (!tsdn_null(tsdn)) {
			tsd_t *tsd = tsdn_tsd(tsdn);
			r = (size_t)prng_lg_range_u64(
			    tsd_prng_statep_get(tsd), lg_range);
		} else {
			uint64_t stack_value = (uint64_t)(uintptr_t)&r;
			r = (size_t)prng_lg_range_u64(&stack_value, lg_range);
		}
		uintptr_t random_offset = ((uintptr_t)r) << (LG_PAGE -
		    lg_range);
		extent->e_addr = (void *)((uintptr_t)extent->e_addr +
		    random_offset);
		assert(ALIGNMENT_ADDR2BASE(extent->e_addr, alignment) ==
		    extent->e_addr);
	}
}
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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 unsigned int UINT64_C (int) ; 
 int /*<<< orphan*/  assert_u64_eq (unsigned int,unsigned int,char*,...) ; 
 int /*<<< orphan*/  assert_u64_ne (unsigned int,unsigned int,char*) ; 
 unsigned int prng_lg_range_u64 (unsigned int*,unsigned int) ; 

__attribute__((used)) static void
test_prng_lg_range_u64(void) {
	uint64_t sa, sb, ra, rb;
	unsigned lg_range;

	sa = 42;
	ra = prng_lg_range_u64(&sa, 64);
	sa = 42;
	rb = prng_lg_range_u64(&sa, 64);
	assert_u64_eq(ra, rb,
	    "Repeated generation should produce repeated results");

	sb = 42;
	rb = prng_lg_range_u64(&sb, 64);
	assert_u64_eq(ra, rb,
	    "Equivalent generation should produce equivalent results");

	sa = 42;
	ra = prng_lg_range_u64(&sa, 64);
	rb = prng_lg_range_u64(&sa, 64);
	assert_u64_ne(ra, rb,
	    "Full-width results must not immediately repeat");

	sa = 42;
	ra = prng_lg_range_u64(&sa, 64);
	for (lg_range = 63; lg_range > 0; lg_range--) {
		sb = 42;
		rb = prng_lg_range_u64(&sb, lg_range);
		assert_u64_eq((rb & (UINT64_C(0xffffffffffffffff) << lg_range)),
		    0, "High order bits should be 0, lg_range=%u", lg_range);
		assert_u64_eq(rb, (ra >> (64 - lg_range)),
		    "Expected high order bits of full-width result, "
		    "lg_range=%u", lg_range);
	}
}
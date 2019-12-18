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
typedef  int uint8_t ;

/* Variables and functions */
 int MAGIC ; 
 size_t ZU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_u_eq (int,int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  dallocx (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ mallocx (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ rallocx (int*,size_t,int /*<<< orphan*/ ) ; 
 size_t sallocx (int*,int /*<<< orphan*/ ) ; 
 size_t xallocx (int*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_zero(size_t sz_min, size_t sz_max) {
	uint8_t *s;
	size_t sz_prev, sz, i;
#define MAGIC	((uint8_t)0x61)

	sz_prev = 0;
	s = (uint8_t *)mallocx(sz_min, 0);
	assert_ptr_not_null((void *)s, "Unexpected mallocx() failure");

	for (sz = sallocx(s, 0); sz <= sz_max;
	    sz_prev = sz, sz = sallocx(s, 0)) {
		if (sz_prev > 0) {
			assert_u_eq(s[0], MAGIC,
			    "Previously allocated byte %zu/%zu is corrupted",
			    ZU(0), sz_prev);
			assert_u_eq(s[sz_prev-1], MAGIC,
			    "Previously allocated byte %zu/%zu is corrupted",
			    sz_prev-1, sz_prev);
		}

		for (i = sz_prev; i < sz; i++) {
			assert_u_eq(s[i], 0x0,
			    "Newly allocated byte %zu/%zu isn't zero-filled",
			    i, sz);
			s[i] = MAGIC;
		}

		if (xallocx(s, sz+1, 0, 0) == sz) {
			s = (uint8_t *)rallocx(s, sz+1, 0);
			assert_ptr_not_null((void *)s,
			    "Unexpected rallocx() failure");
		}
	}

	dallocx(s, 0);
#undef MAGIC
}
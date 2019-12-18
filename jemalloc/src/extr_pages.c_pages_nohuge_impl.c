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

/* Variables and functions */
 void* HUGEPAGE_ADDR2BASE (void*) ; 
 size_t HUGEPAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  MADV_NOHUGEPAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ madvise (void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pages_nohuge_impl(void *addr, size_t size, bool aligned) {
	if (aligned) {
		assert(HUGEPAGE_ADDR2BASE(addr) == addr);
		assert(HUGEPAGE_CEILING(size) == size);
	}

#ifdef JEMALLOC_HAVE_MADVISE_HUGE
	return (madvise(addr, size, MADV_NOHUGEPAGE) != 0);
#else
	return false;
#endif
}
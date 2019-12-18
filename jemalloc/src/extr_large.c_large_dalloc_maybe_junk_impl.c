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
 scalar_t__ config_fill ; 
 scalar_t__ extent_in_dss (void*) ; 
 scalar_t__ have_dss ; 
 int /*<<< orphan*/  large_dalloc_junk (void*,size_t) ; 
 int /*<<< orphan*/  opt_junk_free ; 
 scalar_t__ opt_retain ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
large_dalloc_maybe_junk_impl(void *ptr, size_t size) {
	if (config_fill && have_dss && unlikely(opt_junk_free)) {
		/*
		 * Only bother junk filling if the extent isn't about to be
		 * unmapped.
		 */
		if (opt_retain || (have_dss && extent_in_dss(ptr))) {
			large_dalloc_junk(ptr, size);
		}
	}
}
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
 int /*<<< orphan*/  large_dalloc_maybe_junk_orig (void*,size_t) ; 
 int saw_junking ; 
 void* watch_for_junking ; 

__attribute__((used)) static void
large_dalloc_maybe_junk_intercept(void *ptr, size_t usize) {
	large_dalloc_maybe_junk_orig(ptr, usize);
	if (ptr == watch_for_junking) {
		saw_junking = true;
	}
}
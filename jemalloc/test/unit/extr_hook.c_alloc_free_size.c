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
 int /*<<< orphan*/  MALLOCX_TCACHE_NONE ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* mallocx (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alloc_free_size(size_t sz) {
	void *ptr = mallocx(1, 0);
	free(ptr);
	ptr = mallocx(1, 0);
	free(ptr);
	ptr = mallocx(1, MALLOCX_TCACHE_NONE);
	dallocx(ptr, MALLOCX_TCACHE_NONE);
}
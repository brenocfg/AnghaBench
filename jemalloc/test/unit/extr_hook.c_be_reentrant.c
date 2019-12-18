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
 int /*<<< orphan*/  alloc_free_size (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* mallocx (int,int /*<<< orphan*/ ) ; 
 void* rallocx (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_reentrant() {
	/* Let's make sure the tcache is non-empty if enabled. */
	alloc_free_size(1);
	alloc_free_size(1024);
	alloc_free_size(64 * 1024);
	alloc_free_size(256 * 1024);
	alloc_free_size(1024 * 1024);

	/* Some reallocation. */
	void *ptr = mallocx(129, 0);
	ptr = rallocx(ptr, 130, 0);
	free(ptr);

	ptr = mallocx(2 * 1024 * 1024, 0);
	free(ptr);
	ptr = mallocx(1 * 1024 * 1024, 0);
	ptr = rallocx(ptr, 2 * 1024 * 1024, 0);
	free(ptr);

	ptr = mallocx(1, 0);
	ptr = rallocx(ptr, 1000, 0);
	free(ptr);
}
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
 uintptr_t ALIGNMENT_CEILING (uintptr_t,size_t) ; 
 void* PAGE_ADDR2BASE (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t os_page ; 
 void* os_pages_map (int /*<<< orphan*/ *,size_t,size_t,int*) ; 
 void* os_pages_trim (void*,size_t,size_t,size_t,int*) ; 

__attribute__((used)) static void *
pages_map_slow(size_t size, size_t alignment, bool *commit) {
	size_t alloc_size = size + alignment - os_page;
	/* Beware size_t wrap-around. */
	if (alloc_size < size) {
		return NULL;
	}

	void *ret;
	do {
		void *pages = os_pages_map(NULL, alloc_size, alignment, commit);
		if (pages == NULL) {
			return NULL;
		}
		size_t leadsize = ALIGNMENT_CEILING((uintptr_t)pages, alignment)
		    - (uintptr_t)pages;
		ret = os_pages_trim(pages, alloc_size, leadsize, size, commit);
	} while (ret == NULL);

	assert(ret != NULL);
	assert(PAGE_ADDR2BASE(ret) == ret);
	return ret;
}
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
 void* ALIGNMENT_ADDR2BASE (void*,int /*<<< orphan*/ ) ; 
 size_t ALIGNMENT_CEILING (size_t,int /*<<< orphan*/ ) ; 
 void* MAP_FAILED ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 int PAGES_PROT_COMMIT ; 
 int PAGES_PROT_DECOMMIT ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 void* VirtualAlloc (void*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* mmap (void*,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap_flags ; 
 scalar_t__ os_overcommits ; 
 int /*<<< orphan*/  os_page ; 
 int /*<<< orphan*/  os_pages_unmap (void*,size_t) ; 

__attribute__((used)) static void *
os_pages_map(void *addr, size_t size, size_t alignment, bool *commit) {
	assert(ALIGNMENT_ADDR2BASE(addr, os_page) == addr);
	assert(ALIGNMENT_CEILING(size, os_page) == size);
	assert(size != 0);

	if (os_overcommits) {
		*commit = true;
	}

	void *ret;
#ifdef _WIN32
	/*
	 * If VirtualAlloc can't allocate at the given address when one is
	 * given, it fails and returns NULL.
	 */
	ret = VirtualAlloc(addr, size, MEM_RESERVE | (*commit ? MEM_COMMIT : 0),
	    PAGE_READWRITE);
#else
	/*
	 * We don't use MAP_FIXED here, because it can cause the *replacement*
	 * of existing mappings, and we only want to create new mappings.
	 */
	{
		int prot = *commit ? PAGES_PROT_COMMIT : PAGES_PROT_DECOMMIT;

		ret = mmap(addr, size, prot, mmap_flags, -1, 0);
	}
	assert(ret != NULL);

	if (ret == MAP_FAILED) {
		ret = NULL;
	} else if (addr != NULL && ret != addr) {
		/*
		 * We succeeded in mapping memory, but not in the right place.
		 */
		os_pages_unmap(ret, size);
		ret = NULL;
	}
#endif
	assert(ret == NULL || (addr == NULL && ret != addr) || (addr != NULL &&
	    ret == addr));
	return ret;
}
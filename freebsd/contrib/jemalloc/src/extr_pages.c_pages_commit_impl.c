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
 void* MAP_FAILED ; 
 int MAP_FIXED ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_DECOMMIT ; 
 int PAGES_PROT_COMMIT ; 
 int PAGES_PROT_DECOMMIT ; 
 void* PAGE_ADDR2BASE (void*) ; 
 size_t PAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 void* VirtualAlloc (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualFree (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int mmap_flags ; 
 scalar_t__ os_overcommits ; 
 int /*<<< orphan*/  os_pages_unmap (void*,size_t) ; 

__attribute__((used)) static bool
pages_commit_impl(void *addr, size_t size, bool commit) {
	assert(PAGE_ADDR2BASE(addr) == addr);
	assert(PAGE_CEILING(size) == size);

	if (os_overcommits) {
		return true;
	}

#ifdef _WIN32
	return (commit ? (addr != VirtualAlloc(addr, size, MEM_COMMIT,
	    PAGE_READWRITE)) : (!VirtualFree(addr, size, MEM_DECOMMIT)));
#else
	{
		int prot = commit ? PAGES_PROT_COMMIT : PAGES_PROT_DECOMMIT;
		void *result = mmap(addr, size, prot, mmap_flags | MAP_FIXED,
		    -1, 0);
		if (result == MAP_FAILED) {
			return true;
		}
		if (result != addr) {
			/*
			 * We succeeded in mapping memory, but not in the right
			 * place.
			 */
			os_pages_unmap(result, size);
			return true;
		}
		return false;
	}
#endif
}
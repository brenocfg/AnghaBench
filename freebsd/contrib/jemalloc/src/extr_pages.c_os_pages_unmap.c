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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* ALIGNMENT_ADDR2BASE (void*,int /*<<< orphan*/ ) ; 
 size_t ALIGNMENT_CEILING (size_t,int /*<<< orphan*/ ) ; 
 int BUFERROR_BUF ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 scalar_t__ VirtualFree (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buferror (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_errno () ; 
 int /*<<< orphan*/  malloc_printf (char*,char*) ; 
 int munmap (void*,size_t) ; 
 scalar_t__ opt_abort ; 
 int /*<<< orphan*/  os_page ; 

__attribute__((used)) static void
os_pages_unmap(void *addr, size_t size) {
	assert(ALIGNMENT_ADDR2BASE(addr, os_page) == addr);
	assert(ALIGNMENT_CEILING(size, os_page) == size);

#ifdef _WIN32
	if (VirtualFree(addr, 0, MEM_RELEASE) == 0)
#else
	if (munmap(addr, size) == -1)
#endif
	{
		char buf[BUFERROR_BUF];

		buferror(get_errno(), buf, sizeof(buf));
		malloc_printf("<jemalloc>: Error in "
#ifdef _WIN32
		    "VirtualFree"
#else
		    "munmap"
#endif
		    "(): %s\n", buf);
		if (opt_abort) {
			abort();
		}
	}
}
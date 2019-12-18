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
typedef  scalar_t__ vm_paddr_t ;
typedef  int uintmax_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bufinit () ; 
 int /*<<< orphan*/  cpu_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  decr_init () ; 
 int /*<<< orphan*/  kmi ; 
 int /*<<< orphan*/  perfmon_init () ; 
 scalar_t__* phys_avail ; 
 scalar_t__ physmem ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int ptoa (int) ; 
 scalar_t__ realmem ; 
 int virtual_avail ; 
 int virtual_end ; 
 scalar_t__ vm_free_count () ; 
 int /*<<< orphan*/  vm_ksubmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_bufferinit () ; 

__attribute__((used)) static void
cpu_startup(void *dummy)
{

	/*
	 * Initialise the decrementer-based clock.
	 */
	decr_init();

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	cpu_setup(PCPU_GET(cpuid));

#ifdef PERFMON
	perfmon_init();
#endif
	printf("real memory  = %ju (%ju MB)\n", ptoa((uintmax_t)physmem),
	    ptoa((uintmax_t)physmem) / 1048576);
	realmem = physmem;

	if (bootverbose)
		printf("available KVA = %zu (%zu MB)\n",
		    virtual_end - virtual_avail,
		    (virtual_end - virtual_avail) / 1048576);

	/*
	 * Display any holes after the first chunk of extended memory.
	 */
	if (bootverbose) {
		int indx;

		printf("Physical memory chunk(s):\n");
		for (indx = 0; phys_avail[indx + 1] != 0; indx += 2) {
			vm_paddr_t size1 =
			    phys_avail[indx + 1] - phys_avail[indx];

			#ifdef __powerpc64__
			printf("0x%016jx - 0x%016jx, %ju bytes (%ju pages)\n",
			#else
			printf("0x%09jx - 0x%09jx, %ju bytes (%ju pages)\n",
			#endif
			    (uintmax_t)phys_avail[indx],
			    (uintmax_t)phys_avail[indx + 1] - 1,
			    (uintmax_t)size1, (uintmax_t)size1 / PAGE_SIZE);
		}
	}

	vm_ksubmap_init(&kmi);

	printf("avail memory = %ju (%ju MB)\n",
	    ptoa((uintmax_t)vm_free_count()),
	    ptoa((uintmax_t)vm_free_count()) / 1048576);

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bufinit();
	vm_pager_bufferinit();
}
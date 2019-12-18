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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDB_WHY_BOOTFLAGS ; 
 int MIPS_KSEG0_TO_PHYS (int /*<<< orphan*/ ) ; 
 int PHYS_AVAIL_ENTRIES ; 
 int RB_KDB ; 
 int boothowto ; 
 int* dump_avail ; 
 int /*<<< orphan*/  init_param1 () ; 
 int /*<<< orphan*/  init_param2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kdb_init () ; 
 int /*<<< orphan*/  kernel_kseg0_end ; 
 int /*<<< orphan*/  mips_cpu_init () ; 
 int /*<<< orphan*/  mips_proc0_init () ; 
 int /*<<< orphan*/  mutex_init () ; 
 int* phys_avail ; 
 int /*<<< orphan*/  physmem ; 
 int /*<<< orphan*/  pmap_bootstrap () ; 
 int /*<<< orphan*/  realmem ; 

__attribute__((used)) static void
mips_init(unsigned long memsize, uint64_t ememsize)
{
	int i;

	for (i = 0; i < PHYS_AVAIL_ENTRIES; i++) {
		phys_avail[i] = 0;
	}

	/*
	 * memsize is the amount of RAM available below 256MB.
	 * ememsize is the total amount of RAM available.
	 *
	 * The second bank starts at 0x90000000.
	 */

	/* phys_avail regions are in bytes */
	phys_avail[0] = MIPS_KSEG0_TO_PHYS(kernel_kseg0_end);
	phys_avail[1] = memsize;
	dump_avail[0] = 0;
	dump_avail[1] = phys_avail[1];

	/* Only specify the extended region if it's set */
	if (ememsize > memsize) {
		phys_avail[2] = 0x90000000;
		phys_avail[3] = 0x90000000 + (ememsize - memsize);
		dump_avail[2] = phys_avail[2];
		dump_avail[3] = phys_avail[3];
	}

	/* XXX realmem assigned in the caller of mips_init() */
	physmem = realmem;

	init_param1();
	init_param2(physmem);
	mips_cpu_init();
	pmap_bootstrap();
	mips_proc0_init();
	mutex_init();
	kdb_init();
#ifdef KDB
	if (boothowto & RB_KDB)
		kdb_enter(KDB_WHY_BOOTFLAGS, "Boot flags requested debugger");
#endif
}
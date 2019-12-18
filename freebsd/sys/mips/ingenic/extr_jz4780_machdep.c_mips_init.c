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
typedef  int uint64_t ;
struct mem_region {scalar_t__ mr_start; scalar_t__ mr_size; } ;

/* Variables and functions */
 int FDT_MEM_REGIONS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KDB_WHY_BOOTFLAGS ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MIPS_KSEG0_TO_PHYS (int /*<<< orphan*/ ) ; 
 int RB_KDB ; 
 int boothowto ; 
 int /*<<< orphan*/  btoc (int) ; 
 int /*<<< orphan*/  ctob (int /*<<< orphan*/ ) ; 
 scalar_t__* dump_avail ; 
 scalar_t__ fdt_get_mem_regions (struct mem_region*,int*,int*) ; 
 int /*<<< orphan*/  init_param1 () ; 
 int /*<<< orphan*/  init_param2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kdb_init () ; 
 int /*<<< orphan*/  kernel_kseg0_end ; 
 int* led ; 
 int /*<<< orphan*/  mips_cpu_init () ; 
 int /*<<< orphan*/  mips_proc0_init () ; 
 int /*<<< orphan*/  mutex_init () ; 
 scalar_t__* phys_avail ; 
 int /*<<< orphan*/  physmem ; 
 int /*<<< orphan*/  pmap_bootstrap () ; 
 int /*<<< orphan*/  realmem ; 

__attribute__((used)) static void
mips_init(void)
{
	int i;
#ifdef FDT
	struct mem_region mr[FDT_MEM_REGIONS];
	uint64_t val;
	int mr_cnt;
	int j;
#endif

	for (i = 0; i < 10; i++) {
		phys_avail[i] = 0;
	}

	/* The minimal amount of memory Ingenic SoC can have. */
	dump_avail[0] = phys_avail[0] = MIPS_KSEG0_TO_PHYS(kernel_kseg0_end);
	physmem = realmem = btoc(32 * 1024 * 1024);

	/*
	 * X1000 mips cpu special.
	 * TODO: do anyone know what is this ?
	 */
	__asm(
		"li	$2, 0xa9000000	\n\t"
		"mtc0	$2, $5, 4	\n\t"
		"nop			\n\t"
		::"r"(2));

#ifdef FDT
	if (fdt_get_mem_regions(mr, &mr_cnt, &val) == 0) {

		physmem = realmem = btoc(val);

		KASSERT((phys_avail[0] >= mr[0].mr_start) && \
			(phys_avail[0] < (mr[0].mr_start + mr[0].mr_size)),
			("First region is not within FDT memory range"));

		/* Limit size of the first region */
		phys_avail[1] = (mr[0].mr_start + MIN(mr[0].mr_size, ctob(realmem)));
		dump_avail[1] = phys_avail[1];

		/* Add the rest of regions */
		for (i = 1, j = 2; i < mr_cnt; i++, j+=2) {
			phys_avail[j] = mr[i].mr_start;
			phys_avail[j+1] = (mr[i].mr_start + mr[i].mr_size);
			dump_avail[j] = phys_avail[j];
			dump_avail[j+1] = phys_avail[j+1];
		}
	}
#endif

	init_param1();
	init_param2(physmem);
	mips_cpu_init();
	pmap_bootstrap();
	mips_proc0_init();
	mutex_init();
	kdb_init();
	led[0] = 0x8000;
#ifdef KDB
	if (boothowto & RB_KDB)
		kdb_enter(KDB_WHY_BOOTFLAGS, "Boot flags requested debugger");
#endif
}
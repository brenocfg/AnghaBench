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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_TRACE (char*,scalar_t__) ; 
 scalar_t__ CFE_MI_AVAILABLE ; 
 int /*<<< orphan*/  KDB_WHY_BOOTFLAGS ; 
 scalar_t__ MIPS_KSEG0_TO_PHYS (int /*<<< orphan*/ ) ; 
 int RB_KDB ; 
 int boothowto ; 
 scalar_t__ btoc (scalar_t__) ; 
 int cfe_enummem (int,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__* dump_avail ; 
 int /*<<< orphan*/  init_param1 () ; 
 int /*<<< orphan*/  init_param2 (scalar_t__) ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kdb_init () ; 
 int /*<<< orphan*/  kernel_kseg0_end ; 
 int /*<<< orphan*/  mips_cpu_init () ; 
 int /*<<< orphan*/  mips_proc0_init () ; 
 int /*<<< orphan*/  mutex_init () ; 
 scalar_t__* phys_avail ; 
 scalar_t__ physmem ; 
 int /*<<< orphan*/  pmap_bootstrap () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ realmem ; 

__attribute__((used)) static void
mips_init(void)
{
	int i, j;

	printf("entry: mips_init()\n");

#ifdef CFE
	/*
	 * Query DRAM memory map from CFE.
	 */
	physmem = 0;
	for (i = 0; i < 10; i += 2) {
		int result;
		uint64_t addr, len, type;

		result = cfe_enummem(i / 2, 0, &addr, &len, &type);
		if (result < 0) {
			BCM_TRACE("There is no phys memory for: %d\n", i);
			phys_avail[i] = phys_avail[i + 1] = 0;
			break;
		}
		if (type != CFE_MI_AVAILABLE) {
			BCM_TRACE("phys memory is not available: %d\n", i);
			continue;
		}

		phys_avail[i] = addr;
		if (i == 0 && addr == 0) {
			/*
			 * If this is the first physical memory segment probed
			 * from CFE, omit the region at the start of physical
			 * memory where the kernel has been loaded.
			 */
			phys_avail[i] += MIPS_KSEG0_TO_PHYS(kernel_kseg0_end);
		}
		
		BCM_TRACE("phys memory is available for: %d\n", i);
		BCM_TRACE(" => addr =  %jx\n", addr);
		BCM_TRACE(" => len =  %jd\n", len);

		phys_avail[i + 1] = addr + len;
		physmem += len;
	}

	BCM_TRACE("Total phys memory is : %ld\n", physmem);
	realmem = btoc(physmem);
#endif

	for (j = 0; j < i; j++)
		dump_avail[j] = phys_avail[j];

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
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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_LOCAL_BASE ; 
 int /*<<< orphan*/  ARM_LOCAL_SIZE ; 
 scalar_t__ BSRD4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSWR4 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MBOX0CLR_CORE (int) ; 
 int /*<<< orphan*/  MBOX3CLR_CORE (int) ; 
 int /*<<< orphan*/  MBOX3SET_CORE (int) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  bs_periph ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sev () ; 
 int /*<<< orphan*/  wmb () ; 

void
bcm2836_mp_start_ap(platform_t plat)
{
	uint32_t val;
	int i, retry;

	DPRINTF("platform_mp_start_ap\n");

	/* initialize */
	if (bus_space_map(fdtbus_bs_tag, ARM_LOCAL_BASE, ARM_LOCAL_SIZE,
	    0, &bs_periph) != 0)
		panic("can't map local peripheral\n");
	for (i = 0; i < mp_ncpus; i++) {
		/* clear mailbox 0/3 */
		BSWR4(MBOX0CLR_CORE(i), 0xffffffff);
		BSWR4(MBOX3CLR_CORE(i), 0xffffffff);
	}
	wmb();
	dcache_wbinv_poc_all();

	/* boot secondary CPUs */
	for (i = 1; i < mp_ncpus; i++) {
		/* set entry point to mailbox 3 */
		BSWR4(MBOX3SET_CORE(i),
		    (uint32_t)pmap_kextract((vm_offset_t)mpentry));
		/* Firmware put cores in WFE state, need SEV to wake up. */
		dsb();
		sev();

		/* wait for bootup */
		retry = 1000;
		do {
			/* check entry point */
			val = BSRD4(MBOX3CLR_CORE(i));
			if (val == 0)
				break;
			DELAY(100);
			retry--;
			if (retry <= 0) {
				printf("can't start for CPU%d\n", i);
				break;
			}
		} while (1);

		/* dsb and sev */
		dsb();
		sev();

		/* recode AP in CPU map */
		CPU_SET(i, &all_cpus);
	}
}
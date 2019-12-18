#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {unsigned long n_counter; unsigned long name; int flags; } ;

/* Variables and functions */
 int MAX_HWEVENTS ; 
 int PPMU_ARCH_207S ; 
 int PPMU_HAS_SIER ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_MMCR1 ; 
 int /*<<< orphan*/  SPRN_MMCR2 ; 
 int /*<<< orphan*/  SPRN_MMCRA ; 
 int /*<<< orphan*/  SPRN_SDAR ; 
 int /*<<< orphan*/  SPRN_SIAR ; 
 int /*<<< orphan*/  SPRN_SIER ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 TYPE_1__* ppmu ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int read_pmc (int) ; 
 unsigned long smp_processor_id () ; 

void perf_event_print_debug(void)
{
	unsigned long sdar, sier, flags;
	u32 pmcs[MAX_HWEVENTS];
	int i;

	if (!ppmu) {
		pr_info("Performance monitor hardware not registered.\n");
		return;
	}

	if (!ppmu->n_counter)
		return;

	local_irq_save(flags);

	pr_info("CPU: %d PMU registers, ppmu = %s n_counters = %d",
		 smp_processor_id(), ppmu->name, ppmu->n_counter);

	for (i = 0; i < ppmu->n_counter; i++)
		pmcs[i] = read_pmc(i + 1);

	for (; i < MAX_HWEVENTS; i++)
		pmcs[i] = 0xdeadbeef;

	pr_info("PMC1:  %08x PMC2: %08x PMC3: %08x PMC4: %08x\n",
		 pmcs[0], pmcs[1], pmcs[2], pmcs[3]);

	if (ppmu->n_counter > 4)
		pr_info("PMC5:  %08x PMC6: %08x PMC7: %08x PMC8: %08x\n",
			 pmcs[4], pmcs[5], pmcs[6], pmcs[7]);

	pr_info("MMCR0: %016lx MMCR1: %016lx MMCRA: %016lx\n",
		mfspr(SPRN_MMCR0), mfspr(SPRN_MMCR1), mfspr(SPRN_MMCRA));

	sdar = sier = 0;
#ifdef CONFIG_PPC64
	sdar = mfspr(SPRN_SDAR);

	if (ppmu->flags & PPMU_HAS_SIER)
		sier = mfspr(SPRN_SIER);

	if (ppmu->flags & PPMU_ARCH_207S) {
		pr_info("MMCR2: %016lx EBBHR: %016lx\n",
			mfspr(SPRN_MMCR2), mfspr(SPRN_EBBHR));
		pr_info("EBBRR: %016lx BESCR: %016lx\n",
			mfspr(SPRN_EBBRR), mfspr(SPRN_BESCR));
	}
#endif
	pr_info("SIAR:  %016lx SDAR:  %016lx SIER:  %016lx\n",
		mfspr(SPRN_SIAR), sdar, sier);

	local_irq_restore(flags);
}
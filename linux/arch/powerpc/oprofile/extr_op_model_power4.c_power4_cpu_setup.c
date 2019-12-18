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
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 unsigned int MMCR0_FC ; 
 unsigned int MMCR0_FCECE ; 
 unsigned int MMCR0_FCM1 ; 
 unsigned int MMCR0_PMC1CE ; 
 unsigned int MMCR0_PMCjCE ; 
 unsigned int MMCR0_PMXE ; 
 unsigned long MMCRA_SAMPLE_ENABLE ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_MMCR1 ; 
 int /*<<< orphan*/  SPRN_MMCRA ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 unsigned int mmcr0_val ; 
 unsigned long mmcr1_val ; 
 scalar_t__ mmcra_must_set_sample () ; 
 unsigned long mmcra_val ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ppc_enable_pmcs () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int power4_cpu_setup(struct op_counter_config *ctr)
{
	unsigned int mmcr0 = mmcr0_val;
	unsigned long mmcra = mmcra_val;

	ppc_enable_pmcs();

	/* set the freeze bit */
	mmcr0 |= MMCR0_FC;
	mtspr(SPRN_MMCR0, mmcr0);

	mmcr0 |= MMCR0_FCM1|MMCR0_PMXE|MMCR0_FCECE;
	mmcr0 |= MMCR0_PMC1CE|MMCR0_PMCjCE;
	mtspr(SPRN_MMCR0, mmcr0);

	mtspr(SPRN_MMCR1, mmcr1_val);

	if (mmcra_must_set_sample())
		mmcra |= MMCRA_SAMPLE_ENABLE;
	mtspr(SPRN_MMCRA, mmcra);

	dbg("setup on cpu %d, mmcr0 %lx\n", smp_processor_id(),
	    mfspr(SPRN_MMCR0));
	dbg("setup on cpu %d, mmcr1 %lx\n", smp_processor_id(),
	    mfspr(SPRN_MMCR1));
	dbg("setup on cpu %d, mmcra %lx\n", smp_processor_id(),
	    mfspr(SPRN_MMCRA));

	return 0;
}
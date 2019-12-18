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
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int CPUID_TO_MODEL (int /*<<< orphan*/ ) ; 
#define  CPU_VENDOR_AMD 130 
#define  CPU_VENDOR_CENTAUR 129 
#define  CPU_VENDOR_INTEL 128 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  cpu_id ; 
 int cpu_vendor_id ; 
 scalar_t__ first_msi_irq ; 
 int /*<<< orphan*/  intr_register_pic (int /*<<< orphan*/ *) ; 
 int msi_enabled ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  msi_pic ; 
 int msix_disable_migration ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ num_io_irqs ; 
 scalar_t__ num_msi_irqs ; 
 int /*<<< orphan*/  panic (char*) ; 

void
msi_init(void)
{

	/* Check if we have a supported CPU. */
	switch (cpu_vendor_id) {
	case CPU_VENDOR_INTEL:
	case CPU_VENDOR_AMD:
		break;
	case CPU_VENDOR_CENTAUR:
		if (CPUID_TO_FAMILY(cpu_id) == 0x6 &&
		    CPUID_TO_MODEL(cpu_id) >= 0xf)
			break;
		/* FALLTHROUGH */
	default:
		return;
	}

#ifdef SMP
	if (msix_disable_migration == -1) {
		/* The default is to allow migration of MSI-X interrupts. */
		msix_disable_migration = 0;
	}
#endif

	if (num_msi_irqs == 0)
		return;

	first_msi_irq = num_io_irqs;
	if (num_msi_irqs > UINT_MAX - first_msi_irq)
		panic("num_msi_irqs too high");
	num_io_irqs = first_msi_irq + num_msi_irqs;

	msi_enabled = 1;
	intr_register_pic(&msi_pic);
	mtx_init(&msi_lock, "msi", NULL, MTX_DEF);
}
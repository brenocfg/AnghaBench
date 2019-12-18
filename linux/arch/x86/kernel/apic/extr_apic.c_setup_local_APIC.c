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
struct TYPE_2__ {scalar_t__ dest_logical; int /*<<< orphan*/  (* init_apic_ldr ) () ;int /*<<< orphan*/  (* apic_id_registered ) () ;scalar_t__ disable_esr; } ;

/* Variables and functions */
 unsigned int APIC_DM_EXTINT ; 
 unsigned int APIC_DM_NMI ; 
 int /*<<< orphan*/  APIC_ESR ; 
 scalar_t__ APIC_EXTNMI_ALL ; 
 scalar_t__ APIC_EXTNMI_NONE ; 
 int /*<<< orphan*/  APIC_LDR ; 
 int /*<<< orphan*/  APIC_LVT0 ; 
 int /*<<< orphan*/  APIC_LVT1 ; 
 unsigned int APIC_LVT_LEVEL_TRIGGER ; 
 unsigned int APIC_LVT_MASKED ; 
 int /*<<< orphan*/  APIC_SPIV ; 
 unsigned int APIC_SPIV_APIC_ENABLED ; 
 unsigned int APIC_SPIV_FOCUS_DISABLED ; 
 int /*<<< orphan*/  APIC_TASKPRI ; 
 unsigned int APIC_TPRI_MASK ; 
 unsigned int APIC_VECTOR_MASK ; 
 int /*<<< orphan*/  APIC_VERBOSE ; 
 int BAD_APICID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GET_APIC_LOGICAL_ID (unsigned int) ; 
 unsigned int SPURIOUS_APIC_VECTOR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* apic ; 
 scalar_t__ apic_extnmi ; 
 int /*<<< orphan*/  apic_pending_intr_clear () ; 
 int /*<<< orphan*/  apic_printk (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cmci_recheck () ; 
 scalar_t__ disable_apic ; 
 int /*<<< orphan*/  disable_ioapic_support () ; 
 int early_per_cpu (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lapic_is_integrated () ; 
 int /*<<< orphan*/  perf_events_lapic_init () ; 
 scalar_t__ pic_mode ; 
 scalar_t__ skip_ioapic_setup ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  x86_cpu_to_logical_apicid ; 

__attribute__((used)) static void setup_local_APIC(void)
{
	int cpu = smp_processor_id();
	unsigned int value;

	if (disable_apic) {
		disable_ioapic_support();
		return;
	}

	/*
	 * If this comes from kexec/kcrash the APIC might be enabled in
	 * SPIV. Soft disable it before doing further initialization.
	 */
	value = apic_read(APIC_SPIV);
	value &= ~APIC_SPIV_APIC_ENABLED;
	apic_write(APIC_SPIV, value);

#ifdef CONFIG_X86_32
	/* Pound the ESR really hard over the head with a big hammer - mbligh */
	if (lapic_is_integrated() && apic->disable_esr) {
		apic_write(APIC_ESR, 0);
		apic_write(APIC_ESR, 0);
		apic_write(APIC_ESR, 0);
		apic_write(APIC_ESR, 0);
	}
#endif
	/*
	 * Double-check whether this APIC is really registered.
	 * This is meaningless in clustered apic mode, so we skip it.
	 */
	BUG_ON(!apic->apic_id_registered());

	/*
	 * Intel recommends to set DFR, LDR and TPR before enabling
	 * an APIC.  See e.g. "AP-388 82489DX User's Manual" (Intel
	 * document number 292116).  So here it goes...
	 */
	apic->init_apic_ldr();

#ifdef CONFIG_X86_32
	if (apic->dest_logical) {
		int logical_apicid, ldr_apicid;

		/*
		 * APIC LDR is initialized.  If logical_apicid mapping was
		 * initialized during get_smp_config(), make sure it matches
		 * the actual value.
		 */
		logical_apicid = early_per_cpu(x86_cpu_to_logical_apicid, cpu);
		ldr_apicid = GET_APIC_LOGICAL_ID(apic_read(APIC_LDR));
		if (logical_apicid != BAD_APICID)
			WARN_ON(logical_apicid != ldr_apicid);
		/* Always use the value from LDR. */
		early_per_cpu(x86_cpu_to_logical_apicid, cpu) = ldr_apicid;
	}
#endif

	/*
	 * Set Task Priority to 'accept all except vectors 0-31'.  An APIC
	 * vector in the 16-31 range could be delivered if TPR == 0, but we
	 * would think it's an exception and terrible things will happen.  We
	 * never change this later on.
	 */
	value = apic_read(APIC_TASKPRI);
	value &= ~APIC_TPRI_MASK;
	value |= 0x10;
	apic_write(APIC_TASKPRI, value);

	/* Clear eventually stale ISR/IRR bits */
	apic_pending_intr_clear();

	/*
	 * Now that we are all set up, enable the APIC
	 */
	value = apic_read(APIC_SPIV);
	value &= ~APIC_VECTOR_MASK;
	/*
	 * Enable APIC
	 */
	value |= APIC_SPIV_APIC_ENABLED;

#ifdef CONFIG_X86_32
	/*
	 * Some unknown Intel IO/APIC (or APIC) errata is biting us with
	 * certain networking cards. If high frequency interrupts are
	 * happening on a particular IOAPIC pin, plus the IOAPIC routing
	 * entry is masked/unmasked at a high rate as well then sooner or
	 * later IOAPIC line gets 'stuck', no more interrupts are received
	 * from the device. If focus CPU is disabled then the hang goes
	 * away, oh well :-(
	 *
	 * [ This bug can be reproduced easily with a level-triggered
	 *   PCI Ne2000 networking cards and PII/PIII processors, dual
	 *   BX chipset. ]
	 */
	/*
	 * Actually disabling the focus CPU check just makes the hang less
	 * frequent as it makes the interrupt distributon model be more
	 * like LRU than MRU (the short-term load is more even across CPUs).
	 */

	/*
	 * - enable focus processor (bit==0)
	 * - 64bit mode always use processor focus
	 *   so no need to set it
	 */
	value &= ~APIC_SPIV_FOCUS_DISABLED;
#endif

	/*
	 * Set spurious IRQ vector
	 */
	value |= SPURIOUS_APIC_VECTOR;
	apic_write(APIC_SPIV, value);

	perf_events_lapic_init();

	/*
	 * Set up LVT0, LVT1:
	 *
	 * set up through-local-APIC on the boot CPU's LINT0. This is not
	 * strictly necessary in pure symmetric-IO mode, but sometimes
	 * we delegate interrupts to the 8259A.
	 */
	/*
	 * TODO: set up through-local-APIC from through-I/O-APIC? --macro
	 */
	value = apic_read(APIC_LVT0) & APIC_LVT_MASKED;
	if (!cpu && (pic_mode || !value || skip_ioapic_setup)) {
		value = APIC_DM_EXTINT;
		apic_printk(APIC_VERBOSE, "enabled ExtINT on CPU#%d\n", cpu);
	} else {
		value = APIC_DM_EXTINT | APIC_LVT_MASKED;
		apic_printk(APIC_VERBOSE, "masked ExtINT on CPU#%d\n", cpu);
	}
	apic_write(APIC_LVT0, value);

	/*
	 * Only the BSP sees the LINT1 NMI signal by default. This can be
	 * modified by apic_extnmi= boot option.
	 */
	if ((!cpu && apic_extnmi != APIC_EXTNMI_NONE) ||
	    apic_extnmi == APIC_EXTNMI_ALL)
		value = APIC_DM_NMI;
	else
		value = APIC_DM_NMI | APIC_LVT_MASKED;

	/* Is 82489DX ? */
	if (!lapic_is_integrated())
		value |= APIC_LVT_LEVEL_TRIGGER;
	apic_write(APIC_LVT1, value);

#ifdef CONFIG_X86_MCE_INTEL
	/* Recheck CMCI information after local APIC is up on CPU #0 */
	if (!cpu)
		cmci_recheck();
#endif
}
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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct vioapic {int id; TYPE_1__* rtbl; int /*<<< orphan*/  vm; } ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_2__ {int reg; int acnt; } ;

/* Variables and functions */
 int APIC_ID_MASK ; 
#define  IOAPIC_ARB 130 
#define  IOAPIC_ID 129 
 int IOAPIC_REDTBL ; 
#define  IOAPIC_VER 128 
 int IOART_INTMASK ; 
 int IOART_INTMCLR ; 
 int IOART_INTPOL ; 
 int IOART_REM_IRR ; 
 int REDIR_ENTRIES ; 
 int RTBL_RO_BITS ; 
 int /*<<< orphan*/  VIOAPIC_CTR1 (struct vioapic*,char*,int) ; 
 int /*<<< orphan*/  VIOAPIC_CTR2 (struct vioapic*,char*,int,int) ; 
 int /*<<< orphan*/  VIOAPIC_LOCK (struct vioapic*) ; 
 int /*<<< orphan*/  VIOAPIC_UNLOCK (struct vioapic*) ; 
 int /*<<< orphan*/  vioapic_send_intr (struct vioapic*,int) ; 
 int /*<<< orphan*/  vioapic_update_tmr ; 
 int /*<<< orphan*/  vm_active_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_smp_rendezvous (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vioapic_write(struct vioapic *vioapic, int vcpuid, uint32_t addr, uint32_t data)
{
	uint64_t data64, mask64;
	uint64_t last, changed;
	int regnum, pin, lshift;
	cpuset_t allvcpus;

	regnum = addr & 0xff;
	switch (regnum) {
	case IOAPIC_ID:
		vioapic->id = data & APIC_ID_MASK;
		break;
	case IOAPIC_VER:
	case IOAPIC_ARB:
		/* readonly */
		break;
	default:
		break;
	}

	/* redirection table entries */
	if (regnum >= IOAPIC_REDTBL &&
	    regnum < IOAPIC_REDTBL + REDIR_ENTRIES * 2) {
		pin = (regnum - IOAPIC_REDTBL) / 2;
		if ((regnum - IOAPIC_REDTBL) % 2)
			lshift = 32;
		else
			lshift = 0;

		last = vioapic->rtbl[pin].reg;

		data64 = (uint64_t)data << lshift;
		mask64 = (uint64_t)0xffffffff << lshift;
		vioapic->rtbl[pin].reg &= ~mask64 | RTBL_RO_BITS;
		vioapic->rtbl[pin].reg |= data64 & ~RTBL_RO_BITS;

		VIOAPIC_CTR2(vioapic, "ioapic pin%d: redir table entry %#lx",
		    pin, vioapic->rtbl[pin].reg);

		/*
		 * If any fields in the redirection table entry (except mask
		 * or polarity) have changed then rendezvous all the vcpus
		 * to update their vlapic trigger-mode registers.
		 */
		changed = last ^ vioapic->rtbl[pin].reg;
		if (changed & ~(IOART_INTMASK | IOART_INTPOL)) {
			VIOAPIC_CTR1(vioapic, "ioapic pin%d: recalculate "
			    "vlapic trigger-mode register", pin);
			VIOAPIC_UNLOCK(vioapic);
			allvcpus = vm_active_cpus(vioapic->vm);
			vm_smp_rendezvous(vioapic->vm, vcpuid, allvcpus,
			    vioapic_update_tmr, NULL);
			VIOAPIC_LOCK(vioapic);
		}

		/*
		 * Generate an interrupt if the following conditions are met:
		 * - pin is not masked
		 * - previous interrupt has been EOIed
		 * - pin level is asserted
		 */
		if ((vioapic->rtbl[pin].reg & IOART_INTMASK) == IOART_INTMCLR &&
		    (vioapic->rtbl[pin].reg & IOART_REM_IRR) == 0 &&
		    (vioapic->rtbl[pin].acnt > 0)) {
			VIOAPIC_CTR2(vioapic, "ioapic pin%d: asserted at rtbl "
			    "write, acnt %d", pin, vioapic->rtbl[pin].acnt);
			vioapic_send_intr(vioapic, pin);
		}
	}
}
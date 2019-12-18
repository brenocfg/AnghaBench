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
struct vm {int dummy; } ;
struct vioapic {TYPE_1__* rtbl; } ;
struct TYPE_2__ {int reg; scalar_t__ acnt; } ;

/* Variables and functions */
 int IOART_INTVEC ; 
 int IOART_REM_IRR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int REDIR_ENTRIES ; 
 int /*<<< orphan*/  VIOAPIC_CTR1 (struct vioapic*,char*,int) ; 
 int /*<<< orphan*/  VIOAPIC_CTR2 (struct vioapic*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  VIOAPIC_LOCK (struct vioapic*) ; 
 int /*<<< orphan*/  VIOAPIC_UNLOCK (struct vioapic*) ; 
 int /*<<< orphan*/  vioapic_send_intr (struct vioapic*,int) ; 
 struct vioapic* vm_ioapic (struct vm*) ; 

void
vioapic_process_eoi(struct vm *vm, int vcpuid, int vector)
{
	struct vioapic *vioapic;
	int pin;

	KASSERT(vector >= 0 && vector < 256,
	    ("vioapic_process_eoi: invalid vector %d", vector));

	vioapic = vm_ioapic(vm);
	VIOAPIC_CTR1(vioapic, "ioapic processing eoi for vector %d", vector);

	/*
	 * XXX keep track of the pins associated with this vector instead
	 * of iterating on every single pin each time.
	 */
	VIOAPIC_LOCK(vioapic);
	for (pin = 0; pin < REDIR_ENTRIES; pin++) {
		if ((vioapic->rtbl[pin].reg & IOART_REM_IRR) == 0)
			continue;
		if ((vioapic->rtbl[pin].reg & IOART_INTVEC) != vector)
			continue;
		vioapic->rtbl[pin].reg &= ~IOART_REM_IRR;
		if (vioapic->rtbl[pin].acnt > 0) {
			VIOAPIC_CTR2(vioapic, "ioapic pin%d: asserted at eoi, "
			    "acnt %d", pin, vioapic->rtbl[pin].acnt);
			vioapic_send_intr(vioapic, pin);
		}
	}
	VIOAPIC_UNLOCK(vioapic);
}
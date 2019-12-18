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
typedef  int uint32_t ;
struct vioapic {int /*<<< orphan*/  vm; TYPE_1__* rtbl; } ;
struct TYPE_2__ {int reg; } ;

/* Variables and functions */
 int APIC_ID_SHIFT ; 
 int IOART_DELMOD ; 
 int IOART_DESTMOD ; 
 int IOART_DESTPHY ; 
 int IOART_INTMASK ; 
 int IOART_INTMSET ; 
 int IOART_INTVEC ; 
 int IOART_REM_IRR ; 
 int IOART_TRGRLVL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int REDIR_ENTRIES ; 
 int /*<<< orphan*/  VIOAPIC_CTR1 (struct vioapic*,char*,int) ; 
 int VIOAPIC_LOCKED (struct vioapic*) ; 
 int /*<<< orphan*/  vlapic_deliver_intr (int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static void
vioapic_send_intr(struct vioapic *vioapic, int pin)
{
	int vector, delmode;
	uint32_t low, high, dest;
	bool level, phys;

	KASSERT(pin >= 0 && pin < REDIR_ENTRIES,
	    ("vioapic_set_pinstate: invalid pin number %d", pin));

	KASSERT(VIOAPIC_LOCKED(vioapic),
	    ("vioapic_set_pinstate: vioapic is not locked"));

	low = vioapic->rtbl[pin].reg;
	high = vioapic->rtbl[pin].reg >> 32;

	if ((low & IOART_INTMASK) == IOART_INTMSET) {
		VIOAPIC_CTR1(vioapic, "ioapic pin%d: masked", pin);
		return;
	}

	phys = ((low & IOART_DESTMOD) == IOART_DESTPHY);
	delmode = low & IOART_DELMOD;
	level = low & IOART_TRGRLVL ? true : false;
	if (level)
		vioapic->rtbl[pin].reg |= IOART_REM_IRR;

	vector = low & IOART_INTVEC;
	dest = high >> APIC_ID_SHIFT;
	vlapic_deliver_intr(vioapic->vm, level, dest, phys, delmode, vector);
}
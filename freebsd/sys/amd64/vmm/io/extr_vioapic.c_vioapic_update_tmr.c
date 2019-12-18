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
struct vm {int dummy; } ;
struct vlapic {int dummy; } ;
struct vioapic {TYPE_1__* rtbl; } ;
struct TYPE_2__ {int reg; } ;

/* Variables and functions */
 int APIC_ID_SHIFT ; 
 int IOART_DELMOD ; 
 int IOART_DESTMOD ; 
 int IOART_DESTPHY ; 
 int IOART_INTVEC ; 
 int IOART_TRGRLVL ; 
 int REDIR_ENTRIES ; 
 int /*<<< orphan*/  VIOAPIC_LOCK (struct vioapic*) ; 
 int /*<<< orphan*/  VIOAPIC_UNLOCK (struct vioapic*) ; 
 int /*<<< orphan*/  vlapic_reset_tmr (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_set_tmr_level (struct vlapic*,int,int,int,int) ; 
 struct vioapic* vm_ioapic (struct vm*) ; 
 struct vlapic* vm_lapic (struct vm*,int) ; 

__attribute__((used)) static void
vioapic_update_tmr(struct vm *vm, int vcpuid, void *arg)
{
	struct vioapic *vioapic;
	struct vlapic *vlapic;
	uint32_t low, high, dest;
	int delmode, pin, vector;
	bool level, phys;

	vlapic = vm_lapic(vm, vcpuid);
	vioapic = vm_ioapic(vm);

	VIOAPIC_LOCK(vioapic);
	/*
	 * Reset all vectors to be edge-triggered.
	 */
	vlapic_reset_tmr(vlapic);
	for (pin = 0; pin < REDIR_ENTRIES; pin++) {
		low = vioapic->rtbl[pin].reg;
		high = vioapic->rtbl[pin].reg >> 32;

		level = low & IOART_TRGRLVL ? true : false;
		if (!level)
			continue;

		/*
		 * For a level-triggered 'pin' let the vlapic figure out if
		 * an assertion on this 'pin' would result in an interrupt
		 * being delivered to it. If yes, then it will modify the
		 * TMR bit associated with this vector to level-triggered.
		 */
		phys = ((low & IOART_DESTMOD) == IOART_DESTPHY);
		delmode = low & IOART_DELMOD;
		vector = low & IOART_INTVEC;
		dest = high >> APIC_ID_SHIFT;
		vlapic_set_tmr_level(vlapic, dest, phys, delmode, vector);
	}
	VIOAPIC_UNLOCK(vioapic);
}
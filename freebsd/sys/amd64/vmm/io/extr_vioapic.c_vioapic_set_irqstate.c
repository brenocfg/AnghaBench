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
struct vm {int dummy; } ;
struct vioapic {int dummy; } ;
typedef  enum irqstate { ____Placeholder_irqstate } irqstate ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQSTATE_ASSERT 130 
#define  IRQSTATE_DEASSERT 129 
#define  IRQSTATE_PULSE 128 
 int REDIR_ENTRIES ; 
 int /*<<< orphan*/  VIOAPIC_LOCK (struct vioapic*) ; 
 int /*<<< orphan*/  VIOAPIC_UNLOCK (struct vioapic*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  vioapic_set_pinstate (struct vioapic*,int,int) ; 
 struct vioapic* vm_ioapic (struct vm*) ; 

__attribute__((used)) static int
vioapic_set_irqstate(struct vm *vm, int irq, enum irqstate irqstate)
{
	struct vioapic *vioapic;

	if (irq < 0 || irq >= REDIR_ENTRIES)
		return (EINVAL);

	vioapic = vm_ioapic(vm);

	VIOAPIC_LOCK(vioapic);
	switch (irqstate) {
	case IRQSTATE_ASSERT:
		vioapic_set_pinstate(vioapic, irq, true);
		break;
	case IRQSTATE_DEASSERT:
		vioapic_set_pinstate(vioapic, irq, false);
		break;
	case IRQSTATE_PULSE:
		vioapic_set_pinstate(vioapic, irq, true);
		vioapic_set_pinstate(vioapic, irq, false);
		break;
	default:
		panic("vioapic_set_irqstate: invalid irqstate %d", irqstate);
	}
	VIOAPIC_UNLOCK(vioapic);

	return (0);
}
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
struct intr_event {int /*<<< orphan*/  ie_handlers; } ;
struct apb_softc {int /*<<< orphan*/ * sc_intr_counter; struct intr_event** sc_eventstab; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_intr_frame; } ;

/* Variables and functions */
 int APB_NIRQS ; 
 scalar_t__ AR5312_SYSREG_AHBDMAE ; 
 scalar_t__ AR5312_SYSREG_AHBPERR ; 
 scalar_t__ AR5312_SYSREG_BASE ; 
 scalar_t__ AR5312_SYSREG_MISC_INTSTAT ; 
 scalar_t__ AR5315_SYSREG_BASE ; 
 scalar_t__ AR5315_SYSREG_MISC_INTSTAT ; 
 scalar_t__ AR531X_SOC_AR5315 ; 
 int ATH_READ_REG (scalar_t__) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int) ; 
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int FILTER_HANDLED ; 
 TYPE_1__* PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ ar531x_soc ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  intr_event_handle (struct intr_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_intrcnt_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
apb_filter(void *arg)
{
	struct apb_softc *sc = arg;
	struct intr_event *event;
	uint32_t reg, irq;

	if(ar531x_soc >= AR531X_SOC_AR5315)
		reg = ATH_READ_REG(AR5315_SYSREG_BASE +
			AR5315_SYSREG_MISC_INTSTAT);
	else
		reg = ATH_READ_REG(AR5312_SYSREG_BASE +
			AR5312_SYSREG_MISC_INTSTAT);

	for (irq = 0; irq < APB_NIRQS; irq++) {
		if (reg & (1 << irq)) {

			if(ar531x_soc >= AR531X_SOC_AR5315) {
				ATH_WRITE_REG(AR5315_SYSREG_BASE +
				    AR5315_SYSREG_MISC_INTSTAT,
				    reg & ~(1 << irq));
			} else {
				ATH_WRITE_REG(AR5312_SYSREG_BASE +
				    AR5312_SYSREG_MISC_INTSTAT,
				    reg & ~(1 << irq));
			}

			event = sc->sc_eventstab[irq];
			if (!event || CK_SLIST_EMPTY(&event->ie_handlers)) {
				if(irq == 1 && ar531x_soc < AR531X_SOC_AR5315) {
					ATH_READ_REG(AR5312_SYSREG_BASE +
						AR5312_SYSREG_AHBPERR);
					ATH_READ_REG(AR5312_SYSREG_BASE +
						AR5312_SYSREG_AHBDMAE);
				}
				/* Ignore non handle interrupts */
				if (irq != 0 && irq != 6)
					printf("Stray APB IRQ %d\n", irq);

				continue;
			}

			intr_event_handle(event, PCPU_GET(curthread)->td_intr_frame);
			mips_intrcnt_inc(sc->sc_intr_counter[irq]);
		}
	}

	return (FILTER_HANDLED);
}
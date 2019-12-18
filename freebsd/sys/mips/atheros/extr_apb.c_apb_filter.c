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
typedef  int uint32_t ;
struct trapframe {int dummy; } ;
struct thread {struct trapframe* td_intr_frame; } ;
struct intr_event {int /*<<< orphan*/  ie_handlers; } ;
struct apb_softc {int /*<<< orphan*/ * sc_intr_counter; struct intr_event** sc_eventstab; } ;

/* Variables and functions */
 int APB_INTR_PMC ; 
 int APB_NIRQS ; 
 int /*<<< orphan*/  AR71XX_MISC_INTR_STATUS ; 
#define  AR71XX_SOC_AR7240 139 
#define  AR71XX_SOC_AR7241 138 
#define  AR71XX_SOC_AR7242 137 
#define  AR71XX_SOC_AR9330 136 
#define  AR71XX_SOC_AR9331 135 
#define  AR71XX_SOC_AR9341 134 
#define  AR71XX_SOC_AR9342 133 
#define  AR71XX_SOC_AR9344 132 
#define  AR71XX_SOC_QCA9533 131 
#define  AR71XX_SOC_QCA9533_V2 130 
#define  AR71XX_SOC_QCA9556 129 
#define  AR71XX_SOC_QCA9558 128 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int FILTER_HANDLED ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int ar71xx_soc ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  intr_event_handle (struct intr_event*,struct trapframe*) ; 
 int /*<<< orphan*/  mips_intrcnt_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_intr (struct trapframe*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct trapframe*) ; 

__attribute__((used)) static int
apb_filter(void *arg)
{
	struct apb_softc *sc = arg;
	struct intr_event *event;
	uint32_t reg, irq;
	struct thread *td;
	struct trapframe *tf;

	reg = ATH_READ_REG(AR71XX_MISC_INTR_STATUS);
	for (irq = 0; irq < APB_NIRQS; irq++) {
		if (reg & (1 << irq)) {

			switch (ar71xx_soc) {
			case AR71XX_SOC_AR7240:
			case AR71XX_SOC_AR7241:
			case AR71XX_SOC_AR7242:
			case AR71XX_SOC_AR9330:
			case AR71XX_SOC_AR9331:
			case AR71XX_SOC_AR9341:
			case AR71XX_SOC_AR9342:
			case AR71XX_SOC_AR9344:
			case AR71XX_SOC_QCA9533:
			case AR71XX_SOC_QCA9533_V2:
			case AR71XX_SOC_QCA9556:
			case AR71XX_SOC_QCA9558:
				/* ACK/clear the given interrupt */
				ATH_WRITE_REG(AR71XX_MISC_INTR_STATUS,
				    (1 << irq));
				break;
			default:
				/* fallthrough */
				break;
			}

			event = sc->sc_eventstab[irq];
			/* always count interrupts; spurious or otherwise */
			mips_intrcnt_inc(sc->sc_intr_counter[irq]);
			if (!event || CK_SLIST_EMPTY(&event->ie_handlers)) {
				if (irq == APB_INTR_PMC) {
					td = PCPU_GET(curthread);
					tf = td->td_intr_frame;

					if (pmc_intr)
						(*pmc_intr)(tf);
					continue;
				}
				/* Ignore timer interrupts */
				if (irq != 0 && irq != 8 && irq != 9 && irq != 10)
					printf("Stray APB IRQ %d\n", irq);
				continue;
			}

			intr_event_handle(event, PCPU_GET(curthread)->td_intr_frame);
		}
	}

	return (FILTER_HANDLED);
}
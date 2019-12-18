#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct mv_mpic_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* mpic_isrcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmi_isrc; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int MPIC_CPU_READ (struct mv_mpic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPIC_INT_CTL (unsigned int) ; 
 int MPIC_INT_IRQ_FIQ_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPIC_PPI_CAUSE ; 
 int MPIC_READ (struct mv_mpic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpic_mask_irq (unsigned int) ; 

__attribute__((used)) static int
mpic_intr(void *arg)
{
	struct mv_mpic_softc *sc;
	uint32_t cause, irqsrc;
	unsigned int irq;
	u_int cpuid;

	sc = arg;
	cpuid = PCPU_GET(cpuid);
	irq = 0;

	for (cause = MPIC_CPU_READ(sc, MPIC_PPI_CAUSE); cause > 0;
	    cause >>= 1, irq++) {
		if (cause & 1) {
			irqsrc = MPIC_READ(sc, MPIC_INT_CTL(irq));
			if ((irqsrc & MPIC_INT_IRQ_FIQ_MASK(cpuid)) == 0)
				continue;
			if (intr_isrc_dispatch(&sc->mpic_isrcs[irq].mmi_isrc,
			    curthread->td_intr_frame) != 0) {
				mpic_mask_irq(irq);
				device_printf(sc->sc_dev, "Stray irq %u "
				    "disabled\n", irq);
			}
		}
	}

	return (FILTER_HANDLED);
}
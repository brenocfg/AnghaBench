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
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int dummy; } ;
struct bcm_lintc_softc {int /*<<< orphan*/  bls_dev; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_LINTC_GPU_IRQ ; 
 int BCM_LINTC_GPU_IRQ_MASK ; 
 int BCM_LINTC_MBOX0_IRQ_MASK ; 
 int BCM_LINTC_PENDING_MASK ; 
 int /*<<< orphan*/  BCM_LINTC_PENDING_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_LINTC_PMU_IRQ ; 
 int BCM_LINTC_PMU_IRQ_MASK ; 
 int /*<<< orphan*/  BCM_LINTC_TIMER0_IRQ ; 
 int BCM_LINTC_TIMER0_IRQ_MASK ; 
 int /*<<< orphan*/  BCM_LINTC_TIMER1_IRQ ; 
 int BCM_LINTC_TIMER1_IRQ_MASK ; 
 int /*<<< orphan*/  BCM_LINTC_TIMER2_IRQ ; 
 int BCM_LINTC_TIMER2_IRQ_MASK ; 
 int /*<<< orphan*/  BCM_LINTC_TIMER3_IRQ ; 
 int BCM_LINTC_TIMER3_IRQ_MASK ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_lintc_ipi_dispatch (struct bcm_lintc_softc*,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  bcm_lintc_irq_dispatch (struct bcm_lintc_softc*,int /*<<< orphan*/ ,struct trapframe*) ; 
 int bcm_lintc_read_4 (struct bcm_lintc_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
bcm_lintc_intr(void *arg)
{
	struct bcm_lintc_softc *sc;
	u_int cpu;
	uint32_t num, reg;
	struct trapframe *tf;

	sc = arg;
	cpu = PCPU_GET(cpuid);
	tf = curthread->td_intr_frame;

	for (num = 0; ; num++) {
		reg = bcm_lintc_read_4(sc, BCM_LINTC_PENDING_REG(cpu));
		if ((reg & BCM_LINTC_PENDING_MASK) == 0)
			break;
#ifdef SMP
		if (reg & BCM_LINTC_MBOX0_IRQ_MASK)
			bcm_lintc_ipi_dispatch(sc, cpu, tf);
#endif
		if (reg & BCM_LINTC_TIMER0_IRQ_MASK)
			bcm_lintc_irq_dispatch(sc, BCM_LINTC_TIMER0_IRQ, tf);
		if (reg & BCM_LINTC_TIMER1_IRQ_MASK)
			bcm_lintc_irq_dispatch(sc, BCM_LINTC_TIMER1_IRQ, tf);
		if (reg & BCM_LINTC_TIMER2_IRQ_MASK)
			bcm_lintc_irq_dispatch(sc, BCM_LINTC_TIMER2_IRQ, tf);
		if (reg & BCM_LINTC_TIMER3_IRQ_MASK)
			bcm_lintc_irq_dispatch(sc, BCM_LINTC_TIMER3_IRQ, tf);
		if (reg & BCM_LINTC_GPU_IRQ_MASK)
			bcm_lintc_irq_dispatch(sc, BCM_LINTC_GPU_IRQ, tf);
		if (reg & BCM_LINTC_PMU_IRQ_MASK)
			bcm_lintc_irq_dispatch(sc, BCM_LINTC_PMU_IRQ, tf);

		arm_irq_memory_barrier(0); /* XXX */
	}
	reg &= ~BCM_LINTC_PENDING_MASK;
	if (reg != 0)
		device_printf(sc->bls_dev, "Unknown interrupt(s) %x\n", reg);
	else if (num == 0 && bootverbose)
		device_printf(sc->bls_dev, "Spurious interrupt detected\n");

	return (FILTER_HANDLED);
}
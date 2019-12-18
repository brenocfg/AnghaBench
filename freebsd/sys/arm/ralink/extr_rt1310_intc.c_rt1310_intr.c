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
typedef  size_t uint32_t ;
struct rt1310_intc_softc {int /*<<< orphan*/  dev; TYPE_1__* ri_isrcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  ri_isrc; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  RT_INTC_ICCR ; 
 int /*<<< orphan*/  RT_INTC_IPR ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intc_read_4 (struct rt1310_intc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intc_write_4 (struct rt1310_intc_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt1310_intr(void *arg)
{
	uint32_t irq;
	struct rt1310_intc_softc *sc = arg;

	irq = ffs(intc_read_4(sc, RT_INTC_IPR)) - 1;

	if (intr_isrc_dispatch(&sc->ri_isrcs[irq].ri_isrc,
	    curthread->td_intr_frame) != 0) {
	      	intc_write_4(sc, RT_INTC_ICCR, 1 << irq);
		device_printf(sc->dev, "Stray irq %u disabled\n", irq);
	}

	arm_irq_memory_barrier(0);

	return (FILTER_HANDLED);
}
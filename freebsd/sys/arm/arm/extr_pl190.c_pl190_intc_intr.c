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
struct pl190_intc_softc {int dummy; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int INTC_VIC_READ_4 (struct pl190_intc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VICIRQSTATUS ; 
 int /*<<< orphan*/  VIC_LOCK (struct pl190_intc_softc*) ; 
 int VIC_NIRQS ; 
 int /*<<< orphan*/  VIC_UNLOCK (struct pl190_intc_softc*) ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  pl190_intc_irq_dispatch (struct pl190_intc_softc*,int,struct trapframe*) ; 

__attribute__((used)) static int
pl190_intc_intr(void *arg)
{
	struct pl190_intc_softc *sc;
	u_int cpu;
	uint32_t num, pending;
	struct trapframe *tf;

	sc = arg;
	cpu = PCPU_GET(cpuid);
	tf = curthread->td_intr_frame;

	VIC_LOCK(sc);
	pending = INTC_VIC_READ_4(sc, VICIRQSTATUS);
	VIC_UNLOCK(sc);
	for (num = 0 ; num < VIC_NIRQS; num++) {
		if (pending & (1 << num))
			pl190_intc_irq_dispatch(sc, num, tf);
	}

	return (FILTER_HANDLED);
}
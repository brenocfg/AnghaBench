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
typedef  scalar_t__ uint32_t ;
struct trapframe {int dummy; } ;
struct plic_softc {int dummy; } ;
struct TYPE_2__ {struct trapframe* td_intr_frame; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIC_CLAIM (struct plic_softc*,scalar_t__) ; 
 scalar_t__ RD4 (struct plic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct plic_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  plic_irq_dispatch (struct plic_softc*,scalar_t__,struct trapframe*) ; 

__attribute__((used)) static int
plic_intr(void *arg)
{
	struct plic_softc *sc;
	struct trapframe *tf;
	uint32_t pending;
	uint32_t cpu;

	sc = arg;
	cpu = PCPU_GET(cpuid);

	pending = RD4(sc, PLIC_CLAIM(sc, cpu));
	if (pending) {
		tf = curthread->td_intr_frame;
		plic_irq_dispatch(sc, pending, tf);
		WR4(sc, PLIC_CLAIM(sc, cpu), pending);
	}

	return (FILTER_HANDLED);
}
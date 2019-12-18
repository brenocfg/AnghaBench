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
typedef  void* u_int ;
struct xicp_softc {int intvecs; int /*<<< orphan*/  ibm_set_xive; struct xicp_intvec* ipi_vec; } ;
struct xicp_intvec {int cpu; void* vector; void* irq; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int cell_t ;

/* Variables and functions */
 void* MAX_XICP_IRQS ; 
 int /*<<< orphan*/  OPAL_SET_XIVE ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XICP_PRIORITY ; 
 struct xicp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwref ; 
 int /*<<< orphan*/  mb () ; 
 int opal_call (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,void*,int,int) ; 
 int /*<<< orphan*/  rtas_call_method (int /*<<< orphan*/ ,int,int,void*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtas_exists () ; 
 struct xicp_intvec* xicp_setup_priv (struct xicp_softc*,void*,void**) ; 
 int /*<<< orphan*/  xicp_unmask (int /*<<< orphan*/ ,void*,struct xicp_intvec*) ; 

__attribute__((used)) static void
xicp_enable(device_t dev, u_int irq, u_int vector, void **priv)
{
	struct xicp_softc *sc;
	struct xicp_intvec *intr;
	cell_t status, cpu;

	sc = device_get_softc(dev);

	/* Bind to this CPU to start: distrib. ID is last entry in gserver# */
	cpu = PCPU_GET(hwref);

	intr = xicp_setup_priv(sc, irq, priv);

	intr->irq = irq;
	intr->vector = vector;
	intr->cpu = cpu;
	mb();

	/* IPIs are also enabled.  Stash off the vector index */
	if (irq == MAX_XICP_IRQS) {
		sc->ipi_vec = intr - sc->intvecs;
		return;
	}

	if (rtas_exists()) {
		rtas_call_method(sc->ibm_set_xive, 3, 1, irq, cpu,
		    XICP_PRIORITY, &status);
		xicp_unmask(dev, irq, intr);
#ifdef POWERNV
	} else {
		status = opal_call(OPAL_SET_XIVE, irq, cpu << 2, XICP_PRIORITY);
		/* Unmask implicit for OPAL */

		if (status != 0)
			panic("OPAL_SET_XIVE IRQ %d -> cpu %d failed: %d", irq,
			    cpu, status);
#endif
	}
}
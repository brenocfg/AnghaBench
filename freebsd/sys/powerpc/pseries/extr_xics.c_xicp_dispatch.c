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
typedef  int uint64_t ;
struct xicp_softc {int ipi_vec; int nintvecs; TYPE_1__* intvecs; scalar_t__ xics_emu; } ;
struct trapframe {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int irq; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_IPI ; 
 int /*<<< orphan*/  H_XIRR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAX_XICP_IRQS ; 
 int /*<<< orphan*/  OPAL_INT_GET_XIRR ; 
 int /*<<< orphan*/  OPAL_INT_SET_MFRR ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int PSL_HV ; 
 int XICP_IPI ; 
 int bus_read_4 (struct resource*,int) ; 
 int /*<<< orphan*/  bus_write_1 (struct resource*,int,int) ; 
 int* cpu_xirr ; 
 int /*<<< orphan*/  cpuid ; 
 struct xicp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwref ; 
 int mfmsr () ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  phyp_hcall (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  phyp_pft_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  powerpc_dispatch_intr (int /*<<< orphan*/ ,struct trapframe*) ; 
 struct resource* xicp_mem_for_cpu (size_t) ; 

__attribute__((used)) static void
xicp_dispatch(device_t dev, struct trapframe *tf)
{
	struct xicp_softc *sc;
	struct resource *regs = NULL;
	uint64_t xirr, junk;
	int i;

	sc = device_get_softc(dev);
#ifdef POWERNV
	if ((mfmsr() & PSL_HV) && !sc->xics_emu) {
		regs = xicp_mem_for_cpu(PCPU_GET(hwref));
		KASSERT(regs != NULL,
		    ("Can't find regs for CPU %ld", (uintptr_t)PCPU_GET(hwref)));
	}
#endif

	for (;;) {
		/* Return value in R4, use the PFT call */
		if (regs) {
			xirr = bus_read_4(regs, 4);
#ifdef POWERNV
		} else if (sc->xics_emu) {
			opal_call(OPAL_INT_GET_XIRR, &cpu_xirr[PCPU_GET(cpuid)],
			    false);
			xirr = cpu_xirr[PCPU_GET(cpuid)];
#endif
		} else {
			/* Return value in R4, use the PFT call */
			phyp_pft_hcall(H_XIRR, 0, 0, 0, 0, &xirr, &junk, &junk);
		}
		xirr &= 0x00ffffff;

		if (xirr == 0) /* No more pending interrupts? */
			break;

		if (xirr == XICP_IPI) {		/* Magic number for IPIs */
			xirr = MAX_XICP_IRQS;	/* Map to FreeBSD magic */

			/* Clear IPI */
			if (regs)
				bus_write_1(regs, 12, 0xff);
#ifdef POWERNV
			else if (sc->xics_emu)
				opal_call(OPAL_INT_SET_MFRR,
				    PCPU_GET(hwref), 0xff);
#endif
			else
				phyp_hcall(H_IPI, (uint64_t)(PCPU_GET(hwref)),
				    0xff);
			i = sc->ipi_vec;
		} else {

			/* XXX: super inefficient */
			for (i = 0; i < sc->nintvecs; i++) {
				if (sc->intvecs[i].irq == xirr)
					break;
			}
			KASSERT(i < sc->nintvecs, ("Unmapped XIRR"));
		}

		powerpc_dispatch_intr(sc->intvecs[i].vector, tf);
	}
}
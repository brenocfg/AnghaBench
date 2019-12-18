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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct isa_regs {scalar_t__ size; } ;
struct ebus_softc {int sc_flags; int /*<<< orphan*/  sc_ign; int /*<<< orphan*/  sc_iinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  obd_name; } ;
struct ebus_devinfo {int /*<<< orphan*/  edi_rl; TYPE_1__ edi_obdinfo; } ;
typedef  int /*<<< orphan*/  rintr ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  struct isa_regs ofw_isa_intr_t ;
typedef  int /*<<< orphan*/  intr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUS_PCI ; 
 scalar_t__ INTMAP_VEC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ISA_REG_PHYS (struct isa_regs*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OF_getprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (struct isa_regs*) ; 
 scalar_t__ PCI_INVALID_IRQ ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ebus_destroy_dinfo (struct ebus_devinfo*) ; 
 int /*<<< orphan*/  free (struct ebus_devinfo*,int /*<<< orphan*/ ) ; 
 struct ebus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ofw_bus_lookup_imap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct isa_regs*,int,struct isa_regs*,int,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_isa_route_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct isa_regs) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ebus_devinfo *
ebus_setup_dinfo(device_t dev, struct ebus_softc *sc, phandle_t node)
{
	struct isa_regs reg, *regs;
	ofw_isa_intr_t intr, *intrs;
	struct ebus_devinfo *edi;
	uint64_t start;
	uint32_t rintr;
	int i, nintr, nreg, rv;

	edi = malloc(sizeof(*edi), M_DEVBUF, M_ZERO | M_WAITOK);
	if (ofw_bus_gen_setup_devinfo(&edi->edi_obdinfo, node) != 0) {
		free(edi, M_DEVBUF);
		return (NULL);
	}
	resource_list_init(&edi->edi_rl);
	nreg = OF_getprop_alloc_multi(node, "reg", sizeof(*regs), (void **)&regs);
	if (nreg == -1) {
		device_printf(dev, "<%s>: incomplete\n",
		    edi->edi_obdinfo.obd_name);
		ebus_destroy_dinfo(edi);
		return (NULL);
	}
	for (i = 0; i < nreg; i++) {
		start = ISA_REG_PHYS(regs + i);
		(void)resource_list_add(&edi->edi_rl, SYS_RES_MEMORY, i,
		    start, start + regs[i].size - 1, regs[i].size);
	}
	OF_prop_free(regs);

	nintr = OF_getprop_alloc_multi(node, "interrupts",  sizeof(*intrs),
	    (void **)&intrs);
	if (nintr == -1)
		return (edi);
	for (i = 0; i < nintr; i++) {
		rv = 0;
		if ((sc->sc_flags & EBUS_PCI) != 0) {
			rintr = ofw_isa_route_intr(dev, node, &sc->sc_iinfo,
			    intrs[i]);
		} else {
			intr = intrs[i];
			rv = ofw_bus_lookup_imap(node, &sc->sc_iinfo, &reg,
			    sizeof(reg), &intr, sizeof(intr), &rintr,
			    sizeof(rintr), NULL);
#ifndef SUN4V
			if (rv != 0)
				rintr = INTMAP_VEC(sc->sc_ign, rintr);
#endif
		}
		if ((sc->sc_flags & EBUS_PCI) == 0 ? rv == 0 :
		    rintr == PCI_INVALID_IRQ) {
			device_printf(dev,
			    "<%s>: could not map EBus interrupt %d\n",
			    edi->edi_obdinfo.obd_name, intrs[i]);
			continue;
		}
		(void)resource_list_add(&edi->edi_rl, SYS_RES_IRQ, i, rintr,
		    rintr, 1);
	}
	OF_prop_free(intrs);
	return (edi);
}
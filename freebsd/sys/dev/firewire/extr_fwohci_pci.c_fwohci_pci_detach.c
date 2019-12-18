#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * bdev; } ;
struct TYPE_6__ {TYPE_5__ fc; scalar_t__ bsh; scalar_t__ bst; int /*<<< orphan*/ * bsr; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * ih; } ;
typedef  TYPE_1__ fwohci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FWOHCI_INTMASKCLR ; 
 int /*<<< orphan*/  FW_GMTX (TYPE_5__*) ; 
 int /*<<< orphan*/  OHCI_INT_EN ; 
 int /*<<< orphan*/  PCI_CBMEM ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fwohci_detach (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwohci_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ ) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
fwohci_pci_detach(device_t self)
{
	fwohci_softc_t *sc = device_get_softc(self);
	int s;

	s = splfw();

	if (sc->bsr)
		fwohci_stop(sc, self);

	bus_generic_detach(self);

	if (sc->fc.bdev) {
		device_delete_child(self, sc->fc.bdev);
		sc->fc.bdev = NULL;
	}

	/* disable interrupts that might have been switched on */
	if (sc->bst && sc->bsh)
		bus_space_write_4(sc->bst, sc->bsh,
				  FWOHCI_INTMASKCLR, OHCI_INT_EN);

	if (sc->irq_res) {
		int err;
		if (sc->ih) {
			err = bus_teardown_intr(self, sc->irq_res, sc->ih);
			if (err)
				device_printf(self,
					 "Could not tear down irq, %d\n", err);
			sc->ih = NULL;
		}
		bus_release_resource(self, SYS_RES_IRQ, 0, sc->irq_res);
		sc->irq_res = NULL;
	}

	if (sc->bsr) {
		bus_release_resource(self, SYS_RES_MEMORY, PCI_CBMEM, sc->bsr);
		sc->bsr = NULL;
		sc->bst = 0;
		sc->bsh = 0;
	}

	fwohci_detach(sc, self);
	mtx_destroy(FW_GMTX(&sc->fc));
	splx(s);

	return 0;
}
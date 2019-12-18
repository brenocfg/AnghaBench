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
struct tpm_sc {int interrupts; int intr_type; int /*<<< orphan*/  transmit; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/ * irq_res; scalar_t__ irq_rid; int /*<<< orphan*/ * mem_res; scalar_t__ mem_rid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tpm_sc*,int /*<<< orphan*/ *) ; 
 struct tpm_sc* device_get_softc (int /*<<< orphan*/ ) ; 
 int tpm20_init (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmtis_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpmtis_intr_handler ; 
 int tpmtis_setup_intr (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmtis_transmit ; 

__attribute__((used)) static int
tpmtis_attach(device_t dev)
{
	struct tpm_sc *sc;
	int result;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->mem_rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->mem_rid,
		    RF_ACTIVE);
	if (sc->mem_res == NULL)
		return (ENXIO);

	sc->irq_rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irq_rid,
		    RF_ACTIVE | RF_SHAREABLE);
	if (sc->irq_res != NULL) {
		if (bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
		    NULL, tpmtis_intr_handler, sc, &sc->intr_cookie))
			sc->interrupts = false;
		else
			sc->interrupts = tpmtis_setup_intr(sc);
	} else {
		sc->interrupts = false;
	}

	sc->intr_type = -1;

	sc->transmit = tpmtis_transmit;

	result = tpm20_init(sc);
	if (result != 0)
		tpmtis_detach(dev);

	return (result);
}
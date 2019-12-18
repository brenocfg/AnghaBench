#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int ich_cmd; int /*<<< orphan*/ * irq_res; scalar_t__ irq_rid; int /*<<< orphan*/ * io_res; int /*<<< orphan*/  io_rid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ICH_HOSTC ; 
 int /*<<< orphan*/  ICH_HOSTC_HST_EN ; 
 int /*<<< orphan*/  ICH_SMB_BASE ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 void* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__* const,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ichsmb_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichsmb_release_resources (TYPE_1__* const) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ichsmb_pci_attach(device_t dev)
{
	const sc_p sc = device_get_softc(dev);
	int error;

	/* Initialize private state */
	bzero(sc, sizeof(*sc));
	sc->ich_cmd = -1;
	sc->dev = dev;

	/* Allocate an I/O range */
	sc->io_rid = ICH_SMB_BASE;
	sc->io_res = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT,
	    &sc->io_rid, 16, RF_ACTIVE);
	if (sc->io_res == NULL)
		sc->io_res = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT,
		    &sc->io_rid, 32, RF_ACTIVE);
	if (sc->io_res == NULL) {
		device_printf(dev, "can't map I/O\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate interrupt */
	sc->irq_rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->irq_rid, RF_ACTIVE | RF_SHAREABLE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "can't get IRQ\n");
		error = ENXIO;
		goto fail;
	}

	/* Enable device */
	pci_write_config(dev, ICH_HOSTC, ICH_HOSTC_HST_EN, 1);

	/* Done */
	error = ichsmb_attach(dev);
	if (error)
		goto fail;
	return (0);

fail:
	/* Attach failed, release resources */
	ichsmb_release_resources(sc);
	return (error);
}
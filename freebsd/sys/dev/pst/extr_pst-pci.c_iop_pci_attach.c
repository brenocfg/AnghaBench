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
struct iop_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; scalar_t__ ibase; struct i2o_registers* reg; void* r_mem; void* r_irq; } ;
struct i2o_registers {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 struct iop_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_init (struct iop_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_virtual (void*) ; 

__attribute__((used)) static int
iop_pci_attach(device_t dev)
{
    struct iop_softc *sc = device_get_softc(dev);
    int rid;

    /* get resources */
    rid = PCIR_BAR(0);
    sc->r_mem = 
	bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);

    if (!sc->r_mem)
	return ENXIO;

    rid = 0x00;
    sc->r_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
				       RF_SHAREABLE | RF_ACTIVE);

    /* now setup the infrastructure to talk to the device */
    pci_enable_busmaster(dev);

    sc->ibase = rman_get_virtual(sc->r_mem);
    sc->reg = (struct i2o_registers *)sc->ibase;
    sc->dev = dev;
    mtx_init(&sc->mtx, "pst lock", NULL, MTX_DEF);

    if (!iop_init(sc))
	return 0;
    return bus_generic_attach(dev);
}
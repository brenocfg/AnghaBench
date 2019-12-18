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
struct amdsmb_softc {int /*<<< orphan*/  smbus; int /*<<< orphan*/  lock; int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  amdsmb_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct amdsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amdsmb_attach(device_t dev)
{
	struct amdsmb_softc *amdsmb_sc = device_get_softc(dev);

	/* Allocate I/O space */
	amdsmb_sc->rid = PCIR_BAR(0);
	
	amdsmb_sc->res = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		&amdsmb_sc->rid, RF_ACTIVE);

	if (amdsmb_sc->res == NULL) {
		device_printf(dev, "could not map i/o space\n");
		return (ENXIO);
	}

	mtx_init(&amdsmb_sc->lock, device_get_nameunit(dev), "amdsmb", MTX_DEF);

	/* Allocate a new smbus device */
	amdsmb_sc->smbus = device_add_child(dev, "smbus", -1);
	if (!amdsmb_sc->smbus) {
		amdsmb_detach(dev);
		return (EINVAL);
	}

	bus_generic_attach(dev);

	return (0);
}
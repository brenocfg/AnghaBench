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
struct vmxnet3_softc {int /*<<< orphan*/ * vmx_res1; void* vmx_ioh1; void* vmx_iot1; int /*<<< orphan*/ * vmx_res0; void* vmx_ioh0; void* vmx_iot0; int /*<<< orphan*/  vmx_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vmxnet3_alloc_resources(struct vmxnet3_softc *sc)
{
	device_t dev;
	int rid;

	dev = sc->vmx_dev;

	rid = PCIR_BAR(0);
	sc->vmx_res0 = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->vmx_res0 == NULL) {
		device_printf(dev,
		    "could not map BAR0 memory\n");
		return (ENXIO);
	}

	sc->vmx_iot0 = rman_get_bustag(sc->vmx_res0);
	sc->vmx_ioh0 = rman_get_bushandle(sc->vmx_res0);

	rid = PCIR_BAR(1);
	sc->vmx_res1 = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->vmx_res1 == NULL) {
		device_printf(dev,
		    "could not map BAR1 memory\n");
		return (ENXIO);
	}

	sc->vmx_iot1 = rman_get_bustag(sc->vmx_res1);
	sc->vmx_ioh1 = rman_get_bushandle(sc->vmx_res1);

	return (0);
}
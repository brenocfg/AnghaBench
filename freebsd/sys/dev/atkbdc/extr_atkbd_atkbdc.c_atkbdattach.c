#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/ * intr; int /*<<< orphan*/  ih; } ;
typedef  TYPE_1__ atkbd_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int KBDC_RID_KBD ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int atkbd_attach_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atkbdintr ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbdattach(device_t dev)
{
	atkbd_softc_t *sc;
	keyboard_t *kbd;
	u_long irq;
	int flags;
	int rid;
	int error;

	sc = device_get_softc(dev);

	rid = KBDC_RID_KBD;
	irq = bus_get_resource_start(dev, SYS_RES_IRQ, rid);
	flags = device_get_flags(dev);
	error = atkbd_attach_unit(dev, &kbd, irq, flags);
	if (error)
		return error;

	/* declare our interrupt handler */
	sc->intr = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->intr == NULL)
		return ENXIO;
	error = bus_setup_intr(dev, sc->intr, INTR_TYPE_TTY, NULL, atkbdintr,
			       kbd, &sc->ih);
	if (error)
		bus_release_resource(dev, SYS_RES_IRQ, rid, sc->intr);

	return error;
}
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
struct chvgpio_softc {scalar_t__* sc_pins; int /*<<< orphan*/ * sc_irq_res; scalar_t__ sc_irq_rid; int /*<<< orphan*/ * sc_mem_res; scalar_t__ sc_mem_rid; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/  sc_ngroups; int /*<<< orphan*/  sc_npins; int /*<<< orphan*/  sc_pin_names; int /*<<< orphan*/  sc_bank_prefix; int /*<<< orphan*/  sc_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHVGPIO_INTERRUPT_MASK ; 
 int /*<<< orphan*/  CHVGPIO_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  CHVGPIO_LOCK_DESTROY (struct chvgpio_softc*) ; 
 int /*<<< orphan*/  CHVGPIO_LOCK_INIT (struct chvgpio_softc*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  E_BANK_PREFIX ; 
#define  E_UID 131 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  N_BANK_PREFIX ; 
#define  N_UID 130 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SE_BANK_PREFIX ; 
#define  SE_UID 129 
 int /*<<< orphan*/  SW_BANK_PREFIX ; 
#define  SW_UID 128 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct chvgpio_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chv_east_pin_names ; 
 scalar_t__* chv_east_pins ; 
 int /*<<< orphan*/  chv_north_pin_names ; 
 scalar_t__* chv_north_pins ; 
 int /*<<< orphan*/  chv_southeast_pin_names ; 
 scalar_t__* chv_southeast_pins ; 
 int /*<<< orphan*/  chv_southwest_pin_names ; 
 scalar_t__* chv_southwest_pins ; 
 int /*<<< orphan*/  chvgpio_intr ; 
 struct chvgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chvgpio_attach(device_t dev)
{
	struct chvgpio_softc *sc;
	ACPI_STATUS status;
	int uid;
	int i;
	int error;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_handle = acpi_get_handle(dev);

	status = acpi_GetInteger(sc->sc_handle, "_UID", &uid);
	if (ACPI_FAILURE(status)) {
		device_printf(dev, "failed to read _UID\n");
		return (ENXIO);
	}

	CHVGPIO_LOCK_INIT(sc);

	switch (uid) {
	case SW_UID:
		sc->sc_bank_prefix = SW_BANK_PREFIX;
		sc->sc_pins = chv_southwest_pins;
		sc->sc_pin_names = chv_southwest_pin_names;
		break;
	case N_UID:
		sc->sc_bank_prefix = N_BANK_PREFIX;
		sc->sc_pins = chv_north_pins;
		sc->sc_pin_names = chv_north_pin_names;
		break;
	case E_UID:
		sc->sc_bank_prefix = E_BANK_PREFIX;
		sc->sc_pins = chv_east_pins;
		sc->sc_pin_names = chv_east_pin_names;
		break;
	case SE_UID:
		sc->sc_bank_prefix = SE_BANK_PREFIX;
		sc->sc_pins = chv_southeast_pins;
		sc->sc_pin_names = chv_southeast_pin_names;
		break;
	default:
		device_printf(dev, "invalid _UID value: %d\n", uid);
		return (ENXIO);
	}

	for (i = 0; sc->sc_pins[i] >= 0; i++) {
		sc->sc_npins += sc->sc_pins[i];
		sc->sc_ngroups++;
	}

	sc->sc_mem_rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(sc->sc_dev, SYS_RES_MEMORY,
		&sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		CHVGPIO_LOCK_DESTROY(sc);
		device_printf(dev, "can't allocate memory resource\n");
		return (ENOMEM);
	}

	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		&sc->sc_irq_rid, RF_ACTIVE);

	if (!sc->sc_irq_res) {
		CHVGPIO_LOCK_DESTROY(sc);
		bus_release_resource(dev, SYS_RES_MEMORY,
			sc->sc_mem_rid, sc->sc_mem_res);
		device_printf(dev, "can't allocate irq resource\n");
		return (ENOMEM);
	}

	error = bus_setup_intr(sc->sc_dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
		NULL, chvgpio_intr, sc, &sc->intr_handle);


	if (error) {
		device_printf(sc->sc_dev, "unable to setup irq: error %d\n", error);
		CHVGPIO_LOCK_DESTROY(sc);
		bus_release_resource(dev, SYS_RES_MEMORY,
			sc->sc_mem_rid, sc->sc_mem_res);
		bus_release_resource(dev, SYS_RES_IRQ,
			sc->sc_irq_rid, sc->sc_irq_res);
		return (ENXIO);
	}

	/* Mask and ack all interrupts. */
	bus_write_4(sc->sc_mem_res, CHVGPIO_INTERRUPT_MASK, 0);
	bus_write_4(sc->sc_mem_res, CHVGPIO_INTERRUPT_STATUS, 0xffff);

	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL) {
		CHVGPIO_LOCK_DESTROY(sc);
		bus_release_resource(dev, SYS_RES_MEMORY,
			sc->sc_mem_rid, sc->sc_mem_res);
		bus_release_resource(dev, SYS_RES_IRQ,
			sc->sc_irq_rid, sc->sc_irq_res);
		return (ENXIO);
	}

	return (0);
}
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
typedef  int uint32_t ;
struct bytgpio_softc {int sc_npins; int* sc_pad_funcs; int /*<<< orphan*/ * sc_mem_res; scalar_t__ sc_mem_rid; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_pinpad_map; int /*<<< orphan*/  sc_bank_prefix; int /*<<< orphan*/  sc_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int BYGPIO_PIN_REGISTER (struct bytgpio_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BYTGPIO_LOCK_DESTROY (struct bytgpio_softc*) ; 
 int /*<<< orphan*/  BYTGPIO_LOCK_INIT (struct bytgpio_softc*) ; 
 int /*<<< orphan*/  BYTGPIO_PCONF0 ; 
 int BYTGPIO_PCONF0_FUNC_MASK ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NCORE_BANK_PREFIX ; 
 int NCORE_PINS ; 
#define  NCORE_UID 130 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SCORE_BANK_PREFIX ; 
 int SCORE_PINS ; 
#define  SCORE_UID 129 
 int /*<<< orphan*/  SUS_BANK_PREFIX ; 
 int SUS_PINS ; 
#define  SUS_UID 128 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytgpio_ncore_pins ; 
 int bytgpio_read_4 (struct bytgpio_softc*,int) ; 
 int /*<<< orphan*/  bytgpio_score_pins ; 
 int /*<<< orphan*/  bytgpio_sus_pins ; 
 struct bytgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bytgpio_attach(device_t dev)
{
	struct bytgpio_softc	*sc;
	ACPI_STATUS status;
	int uid;
	int pin;
	uint32_t reg, val;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_handle = acpi_get_handle(dev);
	status = acpi_GetInteger(sc->sc_handle, "_UID", &uid);
	if (ACPI_FAILURE(status)) {
		device_printf(dev, "failed to read _UID\n");
		return (ENXIO);
	}

	BYTGPIO_LOCK_INIT(sc);

	switch (uid) {
	case SCORE_UID:
		sc->sc_npins = SCORE_PINS;
		sc->sc_bank_prefix = SCORE_BANK_PREFIX;
		sc->sc_pinpad_map = bytgpio_score_pins;
		break;
	case NCORE_UID:
		sc->sc_npins = NCORE_PINS;
		sc->sc_bank_prefix = NCORE_BANK_PREFIX;
		sc->sc_pinpad_map = bytgpio_ncore_pins;
		break;
	case SUS_UID:
		sc->sc_npins = SUS_PINS;
		sc->sc_bank_prefix = SUS_BANK_PREFIX;
		sc->sc_pinpad_map = bytgpio_sus_pins;
		break;
	default:
		device_printf(dev, "invalid _UID value: %d\n", uid);
		goto error;
	}

	sc->sc_pad_funcs = malloc(sizeof(int)*sc->sc_npins, M_DEVBUF,
	    M_WAITOK | M_ZERO);

	sc->sc_mem_rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(sc->sc_dev,
	    SYS_RES_MEMORY, &sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "can't allocate resource\n");
		goto error;
	}

	for (pin = 0; pin < sc->sc_npins; pin++) {
	    reg = BYGPIO_PIN_REGISTER(sc, pin, BYTGPIO_PCONF0);
	    val = bytgpio_read_4(sc, reg);
	    sc->sc_pad_funcs[pin] = val & BYTGPIO_PCONF0_FUNC_MASK;
	}

	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL) {
		BYTGPIO_LOCK_DESTROY(sc);
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_mem_rid, sc->sc_mem_res);
		return (ENXIO);
	}

	return (0);

error:
	BYTGPIO_LOCK_DESTROY(sc);

	return (ENXIO);
}
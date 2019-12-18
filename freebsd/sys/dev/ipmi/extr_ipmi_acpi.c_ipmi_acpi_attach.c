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
typedef  int /*<<< orphan*/  uintmax_t ;
struct ipmi_softc {int ipmi_io_rid; int ipmi_io_type; int ipmi_io_spacing; int ipmi_irq_rid; void* ipmi_irq_res; int /*<<< orphan*/  ipmi_dev; int /*<<< orphan*/ ** ipmi_io_res; } ;
struct ipmi_get_info {int address; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  BT_MODE 131 
 int ENXIO ; 
#define  KCS_MODE 130 
 int MAX_RES ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
#define  SMIC_MODE 129 
#define  SSIF_MODE 128 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ipmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ipmi_attach (int /*<<< orphan*/ ) ; 
 int ipmi_kcs_attach (struct ipmi_softc*) ; 
 int /*<<< orphan*/  ipmi_release_resources (int /*<<< orphan*/ ) ; 
 int ipmi_smic_attach (struct ipmi_softc*) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipmi_acpi_attach(device_t dev)
{
	ACPI_HANDLE devh;
	const char *mode;
	struct ipmi_get_info info;
	struct ipmi_softc *sc = device_get_softc(dev);
	int count, error, flags, i, type;
	int interface_type = 0, interface_version = 0;

	error = 0;
	devh = acpi_get_handle(dev);
	if (ACPI_FAILURE(acpi_GetInteger(devh, "_IFT", &interface_type)))
		return (ENXIO);

	if (ACPI_FAILURE(acpi_GetInteger(devh, "_SRV", &interface_version)))
		return (ENXIO);

	switch (interface_type) {
	case KCS_MODE:
		count = 2;
		mode = "KCS";
		break;
	case SMIC_MODE:
		count = 3;
		mode = "SMIC";
		break;
	case BT_MODE:
		device_printf(dev, "BT interface not supported\n");
		return (ENXIO);
	case SSIF_MODE:
		if (ACPI_FAILURE(acpi_GetInteger(devh, "_ADR", &flags)))
			return (ENXIO);
		info.address = flags;
		device_printf(dev, "SSIF interface not supported on ACPI\n");
		return (0);
	default:
		return (ENXIO);
	}

	if (bus_get_resource(dev, SYS_RES_IOPORT, 0, NULL, NULL) == 0)
		type = SYS_RES_IOPORT;
	else if (bus_get_resource(dev, SYS_RES_MEMORY, 0, NULL, NULL) == 0)
		type = SYS_RES_MEMORY;
	else {
		device_printf(dev, "unknown resource type\n");
		return (ENXIO);
	}

	sc->ipmi_io_rid = 0;
	sc->ipmi_io_res[0] = bus_alloc_resource_any(dev, type,
	    &sc->ipmi_io_rid, RF_ACTIVE);
	sc->ipmi_io_type = type;
	sc->ipmi_io_spacing = 1;
	if (sc->ipmi_io_res[0] == NULL) {
		device_printf(dev, "couldn't configure I/O resource\n");
		return (ENXIO);
	}

	/* If we have multiple resources, allocate up to MAX_RES. */
	for (i = 1; i < MAX_RES; i++) {
		sc->ipmi_io_rid = i;
		sc->ipmi_io_res[i] = bus_alloc_resource_any(dev, type,
		    &sc->ipmi_io_rid, RF_ACTIVE);
		if (sc->ipmi_io_res[i] == NULL)
			break;
	}
	sc->ipmi_io_rid = 0;

	/* If we have multiple resources, make sure we have enough of them. */
	if (sc->ipmi_io_res[1] != NULL && sc->ipmi_io_res[count - 1] == NULL) {
		device_printf(dev, "too few I/O resources\n");
		error = ENXIO;
		goto bad;
	}

	device_printf(dev, "%s mode found at %s 0x%jx on %s\n",
	    mode, type == SYS_RES_IOPORT ? "io" : "mem",
	    (uintmax_t)rman_get_start(sc->ipmi_io_res[0]),
	    device_get_name(device_get_parent(dev)));

	sc->ipmi_dev = dev;

	/*
	 * Setup an interrupt if we have an interrupt resource.  We
	 * don't support GPE interrupts via _GPE yet.
	 */
	sc->ipmi_irq_rid = 0;
	sc->ipmi_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->ipmi_irq_rid, RF_SHAREABLE | RF_ACTIVE);

	/* Warn if _GPE exists. */
	if (ACPI_SUCCESS(AcpiEvaluateObject(devh, "_GPE", NULL, NULL)))
		device_printf(dev, "_GPE support not implemented\n");

	/*
	 * We assume an alignment of 1 byte as currently the IPMI spec
	 * doesn't provide any way to determine the alignment via ACPI.
	 */
	switch (interface_type) {
	case KCS_MODE:
		error = ipmi_kcs_attach(sc);
		if (error)
			goto bad;
		break;
	case SMIC_MODE:
		error = ipmi_smic_attach(sc);
		if (error)
			goto bad;
		break;
	}
	error = ipmi_attach(dev);
	if (error)
		goto bad;

	return (0);
bad:
	ipmi_release_resources(dev);
	return (error);
}
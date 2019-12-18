#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fdc_data {int /*<<< orphan*/  fdc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_9__ {TYPE_2__* Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_7__ {int /*<<< orphan*/  Pointer; } ;
struct TYPE_8__ {TYPE_1__ Buffer; } ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVALUATE_OBJECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FDC_BUFLEN ; 
 int ENXIO ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int fdc_acpi_probe_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdc_attach (int /*<<< orphan*/ ) ; 
 int fdc_hints_probe (int /*<<< orphan*/ ) ; 
 int fdc_isa_alloc_resources (int /*<<< orphan*/ ,struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_release_resources (struct fdc_data*) ; 
 int /*<<< orphan*/  fdc_start_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fdc_acpi_attach(device_t dev)
{
	struct fdc_data *sc;
	ACPI_BUFFER buf;
	ACPI_OBJECT *obj;
	device_t bus;
	int error;

	/* Get our softc and use the same accessor as ISA. */
	sc = device_get_softc(dev);
	sc->fdc_dev = dev;

	/* Initialize variables and get a temporary buffer for _FDE. */
	error = ENXIO;
	buf.Length = ACPI_FDC_BUFLEN;
	buf.Pointer = malloc(buf.Length, M_TEMP, M_NOWAIT | M_ZERO);
	if (buf.Pointer == NULL)
		goto out;

	/* Allocate resources the same as the ISA attachment. */
	error = fdc_isa_alloc_resources(dev, sc);
	if (error != 0)
		goto out;

	/* Call common attach code in fdc(4) first. */
	error = fdc_attach(dev);
	if (error != 0)
		goto out;

	/*
	 * Enumerate _FDE, which lists floppy drives that are present.  If
	 * this fails, fall back to the ISA hints-based probe method.
	 */
	bus = device_get_parent(dev);
	if (ACPI_FAILURE(ACPI_EVALUATE_OBJECT(bus, dev, "_FDE", NULL, &buf))) {
		error = fdc_hints_probe(dev);
		goto out;
	}

	/* Add fd child devices as specified. */
	obj = buf.Pointer;
	error = fdc_acpi_probe_children(bus, dev, obj->Buffer.Pointer);

out:
	if (buf.Pointer)
		free(buf.Pointer, M_TEMP);
	if (error != 0)
		fdc_release_resources(sc);
	else
		fdc_start_worker(dev);

	return (error);
}
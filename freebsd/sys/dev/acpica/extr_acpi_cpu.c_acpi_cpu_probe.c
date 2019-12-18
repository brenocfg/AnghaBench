#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct acpi_cpu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_6__ {int ProcId; } ;
struct TYPE_7__ {scalar_t__ Type; TYPE_1__ Processor; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_2__*) ; 
#define  CPUDEV_DEVICE_ID 128 
 int ENXIO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ acpi_cpu_disabled ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_pcpu_get_id (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  acpi_set_private (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/ ** cpu_softc ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int) ; 
 int mp_maxid ; 

__attribute__((used)) static int
acpi_cpu_probe(device_t dev)
{
    static char		   *cpudev_ids[] = { CPUDEV_DEVICE_ID, NULL };
    int			   acpi_id, cpu_id;
    ACPI_BUFFER		   buf;
    ACPI_HANDLE		   handle;
    ACPI_OBJECT		   *obj;
    ACPI_STATUS		   status;
    ACPI_OBJECT_TYPE	   type;

    if (acpi_disabled("cpu") || acpi_cpu_disabled)
	return (ENXIO);
    type = acpi_get_type(dev);
    if (type != ACPI_TYPE_PROCESSOR && type != ACPI_TYPE_DEVICE)
	return (ENXIO);
    if (type == ACPI_TYPE_DEVICE &&
	ACPI_ID_PROBE(device_get_parent(dev), dev, cpudev_ids, NULL) >= 0)
	return (ENXIO);

    handle = acpi_get_handle(dev);
    if (cpu_softc == NULL)
	cpu_softc = malloc(sizeof(struct acpi_cpu_softc *) *
	    (mp_maxid + 1), M_TEMP /* XXX */, M_WAITOK | M_ZERO);

    if (type == ACPI_TYPE_PROCESSOR) {
	/* Get our Processor object. */
	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	status = AcpiEvaluateObject(handle, NULL, NULL, &buf);
	if (ACPI_FAILURE(status)) {
	    device_printf(dev, "probe failed to get Processor obj - %s\n",
		AcpiFormatException(status));
	    return (ENXIO);
	}
	obj = (ACPI_OBJECT *)buf.Pointer;
	if (obj->Type != ACPI_TYPE_PROCESSOR) {
	    device_printf(dev, "Processor object has bad type %d\n",
		obj->Type);
	    AcpiOsFree(obj);
	    return (ENXIO);
	}

	/*
	 * Find the processor associated with our unit.  We could use the
	 * ProcId as a key, however, some boxes do not have the same values
	 * in their Processor object as the ProcId values in the MADT.
	 */
	acpi_id = obj->Processor.ProcId;
	AcpiOsFree(obj);
    } else {
	status = acpi_GetInteger(handle, "_UID", &acpi_id);
	if (ACPI_FAILURE(status)) {
	    device_printf(dev, "Device object has bad value - %s\n",
		AcpiFormatException(status));
	    return (ENXIO);
	}
    }
    if (acpi_pcpu_get_id(dev, &acpi_id, &cpu_id) != 0)
	return (ENXIO);

    /*
     * Check if we already probed this processor.  We scan the bus twice
     * so it's possible we've already seen this one.
     */
    if (cpu_softc[cpu_id] != NULL)
	return (ENXIO);

    /* Mark this processor as in-use and save our derived id for attach. */
    cpu_softc[cpu_id] = (void *)1;
    acpi_set_private(dev, (void*)(intptr_t)cpu_id);
    device_set_desc(dev, "ACPI CPU");

    if (!bootverbose && device_get_unit(dev) != 0) {
	    device_quiet(dev);
	    device_quiet_children(dev);
    }

    return (0);
}
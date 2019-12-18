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
struct cf_setting {int freq; } ;
struct acpi_throttle_softc {int /*<<< orphan*/  cpu_p_blk_len; int /*<<< orphan*/  cpu_p_blk; int /*<<< orphan*/  cpu_handle; int /*<<< orphan*/  cpu_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_6__ {int /*<<< orphan*/  PblkLength; int /*<<< orphan*/  PblkAddress; } ;
struct TYPE_7__ {TYPE_1__ Processor; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_2__*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_thr_set (int /*<<< orphan*/ ,struct cf_setting*) ; 
 int acpi_throttle_evaluate (struct acpi_throttle_softc*) ; 
 int /*<<< orphan*/  acpi_throttle_quirks (struct acpi_throttle_softc*) ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 struct acpi_throttle_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_throttle_attach(device_t dev)
{
	struct acpi_throttle_softc *sc;
	struct cf_setting set;
	ACPI_BUFFER buf;
	ACPI_OBJECT *obj;
	ACPI_STATUS status;
	int error;

	sc = device_get_softc(dev);
	sc->cpu_dev = dev;
	sc->cpu_handle = acpi_get_handle(dev);

	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	status = AcpiEvaluateObject(sc->cpu_handle, NULL, NULL, &buf);
	if (ACPI_FAILURE(status)) {
		device_printf(dev, "attach failed to get Processor obj - %s\n",
		    AcpiFormatException(status));
		return (ENXIO);
	}
	obj = (ACPI_OBJECT *)buf.Pointer;
	sc->cpu_p_blk = obj->Processor.PblkAddress;
	sc->cpu_p_blk_len = obj->Processor.PblkLength;
	AcpiOsFree(obj);

	/* If this is the first device probed, check for quirks. */
	if (device_get_unit(dev) == 0)
		acpi_throttle_quirks(sc);

	/* Attempt to attach the actual throttling register. */
	error = acpi_throttle_evaluate(sc);
	if (error)
		return (error);

	/*
	 * Set our initial frequency to the highest since some systems
	 * seem to boot with this at the lowest setting.
	 */
	set.freq = 10000;
	acpi_thr_set(dev, &set);

	/* Everything went ok, register with cpufreq(4). */
	cpufreq_register(dev);
	return (0);
}
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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_PKG_VALID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
#define  EOPNOTSUPP 128 
 int acpi_PkgGas (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,struct resource**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_perf_probe(device_t dev)
{
	ACPI_HANDLE handle;
	ACPI_OBJECT *pkg;
	struct resource *res;
	ACPI_BUFFER buf;
	int error, rid, type;

	if (resource_disabled("acpi_perf", 0))
		return (ENXIO);

	/*
	 * Check the performance state registers.  If they are of type
	 * "functional fixed hardware", we attach quietly since we will
	 * only be providing information on settings to other drivers.
	 */
	error = ENXIO;
	handle = acpi_get_handle(dev);
	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	if (ACPI_FAILURE(AcpiEvaluateObject(handle, "_PCT", NULL, &buf)))
		return (error);
	pkg = (ACPI_OBJECT *)buf.Pointer;
	if (ACPI_PKG_VALID(pkg, 2)) {
		rid = 0;
		error = acpi_PkgGas(dev, pkg, 0, &type, &rid, &res, 0);
		switch (error) {
		case 0:
			bus_release_resource(dev, type, rid, res);
			bus_delete_resource(dev, type, rid);
			device_set_desc(dev, "ACPI CPU Frequency Control");
			break;
		case EOPNOTSUPP:
			device_quiet(dev);
			error = 0;
			break;
		}
	}
	AcpiOsFree(buf.Pointer);

	return (error);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_panasonic_softc {int /*<<< orphan*/  dev; } ;
typedef  int UINT64 ;
typedef  int UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_5__ {int Value; } ;
struct TYPE_6__ {scalar_t__ Type; TYPE_1__ Integer; } ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  panasonic ; 

__attribute__((used)) static int
acpi_panasonic_hkey_event(struct acpi_panasonic_softc *sc, ACPI_HANDLE h,
    UINT32 *arg)
{
	ACPI_BUFFER buf;
	ACPI_OBJECT *res;
	UINT64 val;
	int status;

	ACPI_SERIAL_ASSERT(panasonic);
	status = ENXIO;

	buf.Length = ACPI_ALLOCATE_BUFFER;
	buf.Pointer = NULL;
	AcpiEvaluateObject(h, "HINF", NULL, &buf);
	res = (ACPI_OBJECT *)buf.Pointer;
	if (res->Type != ACPI_TYPE_INTEGER) {
		device_printf(sc->dev, "HINF returned non-integer\n");
		goto end;
	}
	val = res->Integer.Value;
#ifdef ACPI_PANASONIC_DEBUG
	device_printf(sc->dev, "%s button Fn+F%d\n",
		      (val & 0x80) ? "Pressed" : "Released",
		      (int)(val & 0x7f));
#endif
	if ((val & 0x7f) > 0 && (val & 0x7f) < 11) {
		*arg = val;
		status = 0;
	}
end:
	if (buf.Pointer)
		AcpiOsFree(buf.Pointer);

	return (status);
}
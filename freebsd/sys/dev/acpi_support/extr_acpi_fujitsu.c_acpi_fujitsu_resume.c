#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ exists; } ;
struct acpi_fujitsu_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; TYPE_1__ gmou; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 struct acpi_fujitsu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fujitsu ; 

__attribute__((used)) static int
acpi_fujitsu_resume(device_t dev)
{
	struct acpi_fujitsu_softc   *sc;
	ACPI_STATUS		    status;

	sc = device_get_softc(dev);

	/*
	 * The pointer needs to be re-enabled for
	 * some revisions of the P series (2120).
	 */
	ACPI_SERIAL_BEGIN(fujitsu);

	if(sc->gmou.exists) {
		status = acpi_SetInteger(sc->handle, "SMOU", 1);
		if (ACPI_FAILURE(status))
			device_printf(sc->dev, "Couldn't enable pointer\n");
	}
	ACPI_SERIAL_END(fujitsu);

	return (0);
}
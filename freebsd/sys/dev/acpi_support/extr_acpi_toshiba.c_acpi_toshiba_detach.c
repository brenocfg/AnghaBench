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
struct acpi_toshiba_softc {int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  AcpiRemoveNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_toshiba_notify ; 
 struct acpi_toshiba_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ enable_fn_keys ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_toshiba_detach(device_t dev)
{
	struct		acpi_toshiba_softc *sc;

	sc = device_get_softc(dev);
	if (enable_fn_keys != 0) {
		AcpiRemoveNotifyHandler(sc->handle, ACPI_DEVICE_NOTIFY,
					acpi_toshiba_notify);
	}
	sysctl_ctx_free(&sc->sysctl_ctx);

	return (0);
}
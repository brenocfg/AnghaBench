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
struct acpi_isab_softc {int /*<<< orphan*/  ap_handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  ACPI_IVAR_HANDLE 128 
 int ENOENT ; 
 struct acpi_isab_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_isab_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct acpi_isab_softc *sc = device_get_softc(dev);

	switch (which) {
	case ACPI_IVAR_HANDLE:
		*result = (uintptr_t)sc->ap_handle;
		return (0);
	}
	return (ENOENT);
}
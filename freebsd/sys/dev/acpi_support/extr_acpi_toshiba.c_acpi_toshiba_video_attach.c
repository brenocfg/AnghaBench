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
struct acpi_toshiba_softc {int /*<<< orphan*/  video_handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_toshiba_devclass ; 
 struct acpi_toshiba_softc* devclass_get_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_toshiba_video_attach(device_t dev)
{
	struct		acpi_toshiba_softc *sc;

	sc = devclass_get_softc(acpi_toshiba_devclass, 0);
	if (sc == NULL)
		return (ENXIO);
	sc->video_handle = acpi_get_handle(dev);
	return (0);
}
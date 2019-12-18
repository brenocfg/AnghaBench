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
struct acpi_panasonic_softc {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_SET ; 
 struct acpi_panasonic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hkey_sound_mute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
acpi_panasonic_shutdown(device_t dev)
{
	struct acpi_panasonic_softc *sc;
	int mute;

	/* Mute the main audio during reboot to prevent static burst to speaker. */
	sc = device_get_softc(dev);
	mute = 1;
	hkey_sound_mute(sc->handle, HKEY_SET, &mute);
	return (0);
}
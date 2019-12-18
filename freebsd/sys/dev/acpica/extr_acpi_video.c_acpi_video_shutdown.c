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
struct acpi_video_softc {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOS_SWITCH_BY_BIOS ; 
 struct acpi_video_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vid_set_switch_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_video_shutdown(device_t dev)
{
	struct acpi_video_softc *sc;

	sc = device_get_softc(dev);
	vid_set_switch_policy(sc->handle, DOS_SWITCH_BY_BIOS);

	return (0);
}
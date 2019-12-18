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
struct imx_usbmisc_softc {int /*<<< orphan*/ * mmio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct imx_usbmisc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_usbmisc_detach(device_t dev)
{
	struct imx_usbmisc_softc *sc;

	sc = device_get_softc(dev);

	if (sc->mmio != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mmio);

	return (0);
}
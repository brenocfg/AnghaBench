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
struct imx_hdmi_softc {int /*<<< orphan*/ * eh_tag; int /*<<< orphan*/  i2c_xref; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER_NOWAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,void (*) (void*),void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_attach ; 
 struct imx_hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc_hdmi_init (void*) ; 

__attribute__((used)) static void
imx_hdmi_init(void *dev)
{
	struct imx_hdmi_softc *sc;

	sc = device_get_softc((device_t)dev);

	if (OF_device_from_xref(sc->i2c_xref) != NULL) {
		if (sc->eh_tag != NULL) {
			EVENTHANDLER_DEREGISTER_NOWAIT(device_attach,
			    sc->eh_tag);
		}
		dwc_hdmi_init(dev);
		return;
	}

	if (bootverbose)
		device_printf((device_t)dev, "Waiting for DDC i2c device\n");

	if (sc->eh_tag == NULL) {
		sc->eh_tag = EVENTHANDLER_REGISTER(device_attach, 
		    imx_hdmi_init, dev, EVENTHANDLER_PRI_ANY);
	}
}
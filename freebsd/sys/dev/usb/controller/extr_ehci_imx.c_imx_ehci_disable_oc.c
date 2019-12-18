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
typedef  int /*<<< orphan*/  usbmprops ;
struct imx_ehci_softc {int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * OF_device_from_xref (int) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  USBNC_OVER_CUR_DIS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  imx_usbmisc_set_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
imx_ehci_disable_oc(struct imx_ehci_softc *sc)
{
	device_t usbmdev;
	pcell_t usbmprops[2];
	phandle_t node;
	ssize_t size;
	int index;

	/* Get the reference to the usbmisc driver from the fdt data */
	node = ofw_bus_get_node(sc->dev);
	size = OF_getencprop(node, "fsl,usbmisc", usbmprops,
	    sizeof(usbmprops));
	if (size < sizeof(usbmprops)) {
		device_printf(sc->dev, "failed to retrieve fsl,usbmisc "
		   "property, cannot disable overcurrent protection");
		return;
	}
	/* Retrieve the device_t via the xref handle. */
	usbmdev = OF_device_from_xref(usbmprops[0]);
	if (usbmdev == NULL) {
		device_printf(sc->dev, "usbmisc device not found, "
		    "cannot disable overcurrent protection");
		return;
	}
	/* Call the device routine to set the overcurrent disable bit. */
	index = usbmprops[1];
	imx_usbmisc_set_ctrl(usbmdev, index, USBNC_OVER_CUR_DIS);
}
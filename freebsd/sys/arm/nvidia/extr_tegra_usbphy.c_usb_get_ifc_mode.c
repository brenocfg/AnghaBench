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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  enum usb_ifc_type { ____Placeholder_usb_ifc_type } usb_ifc_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int USB_IFC_TYPE_ULPI ; 
 int USB_IFC_TYPE_UNKNOWN ; 
 int USB_IFC_TYPE_UTMI ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static enum usb_ifc_type
usb_get_ifc_mode(device_t dev, phandle_t node, char *name)
{
	char *tmpstr;
	int rv;
	enum usb_ifc_type ret;

	rv = OF_getprop_alloc(node, name, (void **)&tmpstr);
	if (rv <= 0)
		return (USB_IFC_TYPE_UNKNOWN);

	ret = USB_IFC_TYPE_UNKNOWN;
	if (strcmp(tmpstr, "utmi") == 0)
		ret = USB_IFC_TYPE_UTMI;
	else if (strcmp(tmpstr, "ulpi") == 0)
		ret = USB_IFC_TYPE_ULPI;
	else
		device_printf(dev, "Unsupported phy type: %s\n", tmpstr);
	OF_prop_free(tmpstr);
	return (ret);
}
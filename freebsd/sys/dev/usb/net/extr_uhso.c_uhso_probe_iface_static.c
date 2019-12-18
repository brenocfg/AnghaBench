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
struct usb_device {int dummy; } ;
struct usb_config_descriptor {int bNumInterface; } ;

/* Variables and functions */
 int UHSO_IFACE_SPEC (int,int,int /*<<< orphan*/ ) ; 
 int UHSO_IF_BULK ; 
 int UHSO_IF_MUX ; 
 int UHSO_IF_NET ; 
 int UHSO_PORT_NETWORK ; 
 int UHSO_PORT_SERIAL ; 
 int /*<<< orphan*/  UHSO_PORT_TYPE_DIAG ; 
 int /*<<< orphan*/  UHSO_PORT_TYPE_DIAG2 ; 
 int /*<<< orphan*/  UHSO_PORT_TYPE_MODEM ; 
 int /*<<< orphan*/  UHSO_PORT_TYPE_NETWORK ; 
 struct usb_config_descriptor* usbd_get_config_descriptor (struct usb_device*) ; 

__attribute__((used)) static int
uhso_probe_iface_static(struct usb_device *udev, int index)
{
	struct usb_config_descriptor *cd;

	cd = usbd_get_config_descriptor(udev);
	if (cd->bNumInterface <= 3) {
		/* Cards with 3 or less interfaces */
		switch (index) {
		case 0:
			return UHSO_IFACE_SPEC(UHSO_IF_NET | UHSO_IF_MUX,
			    UHSO_PORT_SERIAL | UHSO_PORT_NETWORK,
			    UHSO_PORT_TYPE_NETWORK);
		case 1:
			return UHSO_IFACE_SPEC(UHSO_IF_BULK,
			    UHSO_PORT_SERIAL, UHSO_PORT_TYPE_DIAG);
		case 2:
			return UHSO_IFACE_SPEC(UHSO_IF_BULK,
			    UHSO_PORT_SERIAL, UHSO_PORT_TYPE_MODEM);
		}
	} else {
		/* Cards with 4 interfaces */
		switch (index) {
		case 0:
			return UHSO_IFACE_SPEC(UHSO_IF_NET | UHSO_IF_MUX,
			    UHSO_PORT_SERIAL | UHSO_PORT_NETWORK,
			    UHSO_PORT_TYPE_NETWORK);
		case 1:
			return UHSO_IFACE_SPEC(UHSO_IF_BULK,
			    UHSO_PORT_SERIAL, UHSO_PORT_TYPE_DIAG2);
		case 2:
			return UHSO_IFACE_SPEC(UHSO_IF_BULK,
			    UHSO_PORT_SERIAL, UHSO_PORT_TYPE_MODEM);
		case 3:
			return UHSO_IFACE_SPEC(UHSO_IF_BULK,
			    UHSO_PORT_SERIAL, UHSO_PORT_TYPE_DIAG);
		}
	}
	return (0);
}
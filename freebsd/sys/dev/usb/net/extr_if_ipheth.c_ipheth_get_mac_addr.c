#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device_request {scalar_t__* wLength; scalar_t__* wIndex; scalar_t__* wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct TYPE_2__ {int /*<<< orphan*/  ue_eaddr; int /*<<< orphan*/  ue_udev; } ;
struct ipheth_softc {int /*<<< orphan*/  sc_data; TYPE_1__ sc_ue; scalar_t__ sc_iface_no; } ;

/* Variables and functions */
 scalar_t__ ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IPHETH_CMD_GET_MACADDR ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipheth_get_mac_addr(struct ipheth_softc *sc)
{
	struct usb_device_request req;
	int error;

	req.bmRequestType = UT_READ_VENDOR_DEVICE;
	req.bRequest = IPHETH_CMD_GET_MACADDR;
	req.wValue[0] = 0;
	req.wValue[1] = 0;
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	req.wLength[0] = ETHER_ADDR_LEN;
	req.wLength[1] = 0;

	error = usbd_do_request(sc->sc_ue.ue_udev, NULL, &req, sc->sc_data);

	if (error)
		return (error);

	memcpy(sc->sc_ue.ue_eaddr, sc->sc_data, ETHER_ADDR_LEN);

	return (0);
}
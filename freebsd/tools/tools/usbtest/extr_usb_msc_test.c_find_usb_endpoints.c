#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct libusb20_interface {scalar_t__ num_endpoints; struct libusb20_endpoint* endpoints; TYPE_1__ desc; } ;
struct TYPE_4__ {int bmAttributes; int bEndpointAddress; } ;
struct libusb20_endpoint {TYPE_2__ desc; } ;
struct libusb20_device {int dummy; } ;
struct libusb20_config {scalar_t__ num_interface; struct libusb20_interface* interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libusb20_config*) ; 
 struct libusb20_config* libusb20_dev_alloc_config (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_dev_get_config_index (struct libusb20_device*) ; 

void
find_usb_endpoints(struct libusb20_device *pdev, uint8_t class,
    uint8_t subclass, uint8_t protocol, uint8_t alt_setting,
    uint8_t *pif, uint8_t *in_ep, uint8_t *out_ep, uint8_t next_if)
{
	struct libusb20_config *pcfg;
	struct libusb20_interface *iface;
	struct libusb20_endpoint *ep;
	uint8_t x;
	uint8_t y;
	uint8_t z;

	*in_ep = 0;
	*out_ep = 0;
	*pif = 0;

	pcfg = libusb20_dev_alloc_config(pdev,
	    libusb20_dev_get_config_index(pdev));

	if (pcfg == NULL)
		return;

	for (x = 0; x != pcfg->num_interface; x++) {

		y = alt_setting;

		iface = (pcfg->interface + x);

		if ((iface->desc.bInterfaceClass == class) &&
		    (iface->desc.bInterfaceSubClass == subclass ||
		    subclass == 255) &&
		    (iface->desc.bInterfaceProtocol == protocol ||
		    protocol == 255)) {

			if (next_if) {
				x++;
				if (x == pcfg->num_interface)
					break;
				iface = (pcfg->interface + x);
			}
			*pif = x;

			for (z = 0; z != iface->num_endpoints; z++) {
				ep = iface->endpoints + z;

				/* BULK only */
				if ((ep->desc.bmAttributes & 3) != 2)
					continue;

				if (ep->desc.bEndpointAddress & 0x80)
					*in_ep = ep->desc.bEndpointAddress;
				else
					*out_ep = ep->desc.bEndpointAddress;
			}
			break;
		}
	}

	free(pcfg);
}
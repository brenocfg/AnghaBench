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
typedef  scalar_t__ uint8_t ;
struct libusb_interface_descriptor {int bNumEndpoints; struct libusb_endpoint_descriptor* endpoint; } ;
struct libusb_interface {int num_altsetting; struct libusb_interface_descriptor* altsetting; } ;
struct libusb_endpoint_descriptor {scalar_t__ bEndpointAddress; int wMaxPacketSize; } ;
struct libusb_config_descriptor {int bNumInterfaces; struct libusb_interface* interface; } ;
typedef  int /*<<< orphan*/  libusb_device ;

/* Variables and functions */
 int LIBUSB_ERROR_NOT_FOUND ; 
 int LIBUSB_ERROR_NO_DEVICE ; 
 int /*<<< orphan*/  libusb_free_config_descriptor (struct libusb_config_descriptor*) ; 
 int libusb_get_active_config_descriptor (int /*<<< orphan*/ *,struct libusb_config_descriptor**) ; 

int
libusb_get_max_packet_size(libusb_device *dev, uint8_t endpoint)
{
	struct libusb_config_descriptor *pdconf;
	struct libusb_interface *pinf;
	struct libusb_interface_descriptor *pdinf;
	struct libusb_endpoint_descriptor *pdend;
	int i;
	int j;
	int k;
	int ret;

	if (dev == NULL)
		return (LIBUSB_ERROR_NO_DEVICE);

	ret = libusb_get_active_config_descriptor(dev, &pdconf);
	if (ret < 0)
		return (ret);

	ret = LIBUSB_ERROR_NOT_FOUND;
	for (i = 0; i < pdconf->bNumInterfaces; i++) {
		pinf = &pdconf->interface[i];
		for (j = 0; j < pinf->num_altsetting; j++) {
			pdinf = &pinf->altsetting[j];
			for (k = 0; k < pdinf->bNumEndpoints; k++) {
				pdend = &pdinf->endpoint[k];
				if (pdend->bEndpointAddress == endpoint) {
					ret = pdend->wMaxPacketSize;
					goto out;
				}
			}
		}
	}

out:
	libusb_free_config_descriptor(pdconf);
	return (ret);
}
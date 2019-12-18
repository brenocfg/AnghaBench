#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct libusb_interface_descriptor {scalar_t__ extra_length; int* extra; struct libusb_endpoint_descriptor* endpoint; int /*<<< orphan*/  iInterface; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bNumEndpoints; int /*<<< orphan*/  bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb_endpoint_descriptor {scalar_t__ extra_length; int* extra; int /*<<< orphan*/  bSynchAddress; int /*<<< orphan*/  bRefresh; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb_config_descriptor {scalar_t__ extra_length; int* extra; TYPE_7__* interface; int /*<<< orphan*/  MaxPower; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; int /*<<< orphan*/  bConfigurationValue; int /*<<< orphan*/  bNumInterfaces; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct TYPE_15__ {scalar_t__ len; int /*<<< orphan*/  ptr; } ;
struct TYPE_11__ {int /*<<< orphan*/  iInterface; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bNumEndpoints; int /*<<< orphan*/  bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_interface {int num_endpoints; int num_altsetting; struct libusb20_endpoint* endpoints; TYPE_6__ extra; TYPE_2__ desc; struct libusb20_interface* altsetting; } ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  ptr; } ;
struct TYPE_12__ {int /*<<< orphan*/  bSynchAddress; int /*<<< orphan*/  bRefresh; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_endpoint {TYPE_4__ extra; TYPE_3__ desc; } ;
struct libusb20_device {int dummy; } ;
struct TYPE_14__ {scalar_t__ len; int /*<<< orphan*/  ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/  bMaxPower; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; int /*<<< orphan*/  bConfigurationValue; int /*<<< orphan*/  bNumInterfaces; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_config {int num_interface; struct libusb20_interface* interface; TYPE_5__ extra; TYPE_1__ desc; } ;
typedef  struct libusb_interface_descriptor libusb_interface_descriptor ;
struct TYPE_16__ {int num_altsetting; struct libusb_interface_descriptor* altsetting; } ;
typedef  TYPE_7__ libusb_interface ;
typedef  struct libusb_endpoint_descriptor libusb_endpoint_descriptor ;
struct TYPE_17__ {struct libusb20_device* os_priv; } ;
typedef  TYPE_8__ libusb_device ;
typedef  int /*<<< orphan*/  libusb_config_descriptor ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NOT_FOUND ; 
 int LIBUSB_ERROR_NO_MEM ; 
 scalar_t__ N_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  free (struct libusb20_config*) ; 
 struct libusb20_config* libusb20_dev_alloc_config (struct libusb20_device*,int) ; 
 struct libusb_config_descriptor* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct libusb_config_descriptor*,int /*<<< orphan*/ ,scalar_t__) ; 

int
libusb_get_config_descriptor(libusb_device *dev, uint8_t config_index,
    struct libusb_config_descriptor **config)
{
	struct libusb20_device *pdev;
	struct libusb20_config *pconf;
	struct libusb20_interface *pinf;
	struct libusb20_endpoint *pend;
	struct libusb_config_descriptor *pconfd;
	struct libusb_interface_descriptor *ifd;
	struct libusb_endpoint_descriptor *endd;
	uint8_t *pextra;
	uint16_t nextra;
	uint8_t nif;
	uint8_t nep;
	uint8_t nalt;
	uint8_t i;
	uint8_t j;
	uint8_t k;

	if (dev == NULL || config == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	*config = NULL;

	pdev = dev->os_priv;
	pconf = libusb20_dev_alloc_config(pdev, config_index);

	if (pconf == NULL)
		return (LIBUSB_ERROR_NOT_FOUND);

	nalt = nif = pconf->num_interface;
	nep = 0;
	nextra = N_ALIGN(pconf->extra.len);

	for (i = 0; i < nif; i++) {

		pinf = pconf->interface + i;
		nextra += N_ALIGN(pinf->extra.len);
		nep += pinf->num_endpoints;
		k = pinf->num_endpoints;
		pend = pinf->endpoints;
		while (k--) {
			nextra += N_ALIGN(pend->extra.len);
			pend++;
		}

		j = pinf->num_altsetting;
		nalt += pinf->num_altsetting;
		pinf = pinf->altsetting;
		while (j--) {
			nextra += N_ALIGN(pinf->extra.len);
			nep += pinf->num_endpoints;
			k = pinf->num_endpoints;
			pend = pinf->endpoints;
			while (k--) {
				nextra += N_ALIGN(pend->extra.len);
				pend++;
			}
			pinf++;
		}
	}

	nextra = nextra +
	    (1 * sizeof(libusb_config_descriptor)) +
	    (nif * sizeof(libusb_interface)) +
	    (nalt * sizeof(libusb_interface_descriptor)) +
	    (nep * sizeof(libusb_endpoint_descriptor));

	nextra = N_ALIGN(nextra);

	pconfd = malloc(nextra);

	if (pconfd == NULL) {
		free(pconf);
		return (LIBUSB_ERROR_NO_MEM);
	}
	/* make sure memory is initialised */
	memset(pconfd, 0, nextra);

	pconfd->interface = (libusb_interface *) (pconfd + 1);

	ifd = (libusb_interface_descriptor *) (pconfd->interface + nif);
	endd = (libusb_endpoint_descriptor *) (ifd + nalt);
	pextra = (uint8_t *)(endd + nep);

	/* fill in config descriptor */

	pconfd->bLength = pconf->desc.bLength;
	pconfd->bDescriptorType = pconf->desc.bDescriptorType;
	pconfd->wTotalLength = pconf->desc.wTotalLength;
	pconfd->bNumInterfaces = pconf->desc.bNumInterfaces;
	pconfd->bConfigurationValue = pconf->desc.bConfigurationValue;
	pconfd->iConfiguration = pconf->desc.iConfiguration;
	pconfd->bmAttributes = pconf->desc.bmAttributes;
	pconfd->MaxPower = pconf->desc.bMaxPower;

	if (pconf->extra.len != 0) {
		pconfd->extra_length = pconf->extra.len;
		pconfd->extra = pextra;
		memcpy(pextra, pconf->extra.ptr, pconfd->extra_length);
		pextra += N_ALIGN(pconfd->extra_length);
	}
	/* setup all interface and endpoint pointers */

	for (i = 0; i < nif; i++) {

		pconfd->interface[i].altsetting = ifd;
		ifd->endpoint = endd;
		endd += pconf->interface[i].num_endpoints;
		ifd++;

		for (j = 0; j < pconf->interface[i].num_altsetting; j++) {
			ifd->endpoint = endd;
			endd += pconf->interface[i].altsetting[j].num_endpoints;
			ifd++;
		}
	}

	/* fill in all interface and endpoint data */

	for (i = 0; i < nif; i++) {
		pinf = &pconf->interface[i];
		pconfd->interface[i].num_altsetting = pinf->num_altsetting + 1;
		for (j = 0; j < pconfd->interface[i].num_altsetting; j++) {
			if (j != 0)
				pinf = &pconf->interface[i].altsetting[j - 1];
			ifd = &pconfd->interface[i].altsetting[j];
			ifd->bLength = pinf->desc.bLength;
			ifd->bDescriptorType = pinf->desc.bDescriptorType;
			ifd->bInterfaceNumber = pinf->desc.bInterfaceNumber;
			ifd->bAlternateSetting = pinf->desc.bAlternateSetting;
			ifd->bNumEndpoints = pinf->desc.bNumEndpoints;
			ifd->bInterfaceClass = pinf->desc.bInterfaceClass;
			ifd->bInterfaceSubClass = pinf->desc.bInterfaceSubClass;
			ifd->bInterfaceProtocol = pinf->desc.bInterfaceProtocol;
			ifd->iInterface = pinf->desc.iInterface;
			if (pinf->extra.len != 0) {
				ifd->extra_length = pinf->extra.len;
				ifd->extra = pextra;
				memcpy(pextra, pinf->extra.ptr, pinf->extra.len);
				pextra += N_ALIGN(pinf->extra.len);
			}
			for (k = 0; k < pinf->num_endpoints; k++) {
				pend = &pinf->endpoints[k];
				endd = &ifd->endpoint[k];
				endd->bLength = pend->desc.bLength;
				endd->bDescriptorType = pend->desc.bDescriptorType;
				endd->bEndpointAddress = pend->desc.bEndpointAddress;
				endd->bmAttributes = pend->desc.bmAttributes;
				endd->wMaxPacketSize = pend->desc.wMaxPacketSize;
				endd->bInterval = pend->desc.bInterval;
				endd->bRefresh = pend->desc.bRefresh;
				endd->bSynchAddress = pend->desc.bSynchAddress;
				if (pend->extra.len != 0) {
					endd->extra_length = pend->extra.len;
					endd->extra = pextra;
					memcpy(pextra, pend->extra.ptr, pend->extra.len);
					pextra += N_ALIGN(pend->extra.len);
				}
			}
		}
	}

	free(pconf);

	*config = pconfd;

	return (0);			/* success */
}
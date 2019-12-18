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
typedef  int uint8_t ;
struct usb_temp_setup {int /*<<< orphan*/  size; scalar_t__ bInterfaceNumber; scalar_t__ buf; } ;
struct usb_interface_assoc_descriptor {int /*<<< orphan*/  bFirstInterface; } ;
struct usb_cdc_union_descriptor {int /*<<< orphan*/ * bSlaveInterface; int /*<<< orphan*/  bMasterInterface; } ;
struct usb_cdc_cm_descriptor {int /*<<< orphan*/  bDataInterface; } ;

/* Variables and functions */
 int const UDESCSUB_CDC_CM ; 
 int const UDESCSUB_CDC_UNION ; 
 int const UDESC_CS_INTERFACE ; 
 int const UDESC_IFACE_ASSOC ; 
 void* USB_ADD_BYTES (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 

__attribute__((used)) static void
usb_make_raw_desc(struct usb_temp_setup *temp,
    const uint8_t *raw)
{
	void *dst;
	uint8_t len;

	/*
         * The first byte of any USB descriptor gives the length.
         */
	if (raw) {
		len = raw[0];
		if (temp->buf) {
			dst = USB_ADD_BYTES(temp->buf, temp->size);
			memcpy(dst, raw, len);

			/* check if we have got a CDC union descriptor */

			if ((raw[0] == sizeof(struct usb_cdc_union_descriptor)) &&
			    (raw[1] == UDESC_CS_INTERFACE) &&
			    (raw[2] == UDESCSUB_CDC_UNION)) {
				struct usb_cdc_union_descriptor *ud = (void *)dst;

				/* update the interface numbers */

				ud->bMasterInterface +=
				    temp->bInterfaceNumber;
				ud->bSlaveInterface[0] +=
				    temp->bInterfaceNumber;
			}

			/* check if we have got an interface association descriptor */

			if ((raw[0] == sizeof(struct usb_interface_assoc_descriptor)) &&
			    (raw[1] == UDESC_IFACE_ASSOC)) {
				struct usb_interface_assoc_descriptor *iad = (void *)dst;

				/* update the interface number */

				iad->bFirstInterface +=
				    temp->bInterfaceNumber;
			}

			/* check if we have got a call management descriptor */

			if ((raw[0] == sizeof(struct usb_cdc_cm_descriptor)) &&
			    (raw[1] == UDESC_CS_INTERFACE) &&
			    (raw[2] == UDESCSUB_CDC_CM)) {
				struct usb_cdc_cm_descriptor *ccd = (void *)dst;

				/* update the interface number */

				ccd->bDataInterface +=
				    temp->bInterfaceNumber;
			}
		}
		temp->size += len;
	}
}
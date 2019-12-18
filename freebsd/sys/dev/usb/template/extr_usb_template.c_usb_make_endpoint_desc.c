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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_temp_setup {scalar_t__ size; size_t usb_speed; int /*<<< orphan*/  bNumEndpoints; scalar_t__ buf; void* err; } ;
struct usb_temp_endpoint_desc {int bEndpointAddress; int bmAttributes; void** ppRawDesc; TYPE_2__* pIntervals; TYPE_1__* pPacketSize; } ;
struct usb_endpoint_descriptor {int bLength; int bEndpointAddress; int bmAttributes; int bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_4__ {int* bInterval; } ;
struct TYPE_3__ {scalar_t__* mps; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDESC_ENDPOINT ; 
 int UE_ADDR ; 
#define  UE_BULK 132 
#define  UE_CONTROL 131 
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
#define  UE_INTERRUPT 130 
 int UE_ISOCHRONOUS ; 
 int UE_XFERTYPE ; 
 scalar_t__ UE_ZERO_MPS ; 
 struct usb_endpoint_descriptor* USB_ADD_BYTES (scalar_t__,scalar_t__) ; 
 void* USB_ERR_INVAL ; 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_make_raw_desc (struct usb_temp_setup*,void const*) ; 

__attribute__((used)) static void
usb_make_endpoint_desc(struct usb_temp_setup *temp,
    const struct usb_temp_endpoint_desc *ted)
{
	struct usb_endpoint_descriptor *ed;
	const void **rd;
	uint16_t old_size;
	uint16_t mps;
	uint8_t ea;			/* Endpoint Address */
	uint8_t et;			/* Endpiont Type */

	/* Reserve memory */
	old_size = temp->size;

	ea = (ted->bEndpointAddress & (UE_ADDR | UE_DIR_IN | UE_DIR_OUT));
	et = (ted->bmAttributes & UE_XFERTYPE);

	if (et == UE_ISOCHRONOUS) {
		/* account for extra byte fields */
		temp->size += sizeof(*ed) + 2;
	} else {
		temp->size += sizeof(*ed);
	}

	/* Scan all Raw Descriptors first */
	rd = ted->ppRawDesc;
	if (rd) {
		while (*rd) {
			usb_make_raw_desc(temp, *rd);
			rd++;
		}
	}
	if (ted->pPacketSize == NULL) {
		/* not initialized */
		temp->err = USB_ERR_INVAL;
		return;
	}
	mps = ted->pPacketSize->mps[temp->usb_speed];
	if (mps == 0) {
		/* not initialized */
		temp->err = USB_ERR_INVAL;
		return;
	} else if (mps == UE_ZERO_MPS) {
		/* escape for Zero Max Packet Size */
		mps = 0;
	}

	/*
	 * Fill out the real USB endpoint descriptor
	 * in case there is a buffer present:
	 */
	if (temp->buf) {
		ed = USB_ADD_BYTES(temp->buf, old_size);
		if (et == UE_ISOCHRONOUS)
			ed->bLength = sizeof(*ed) + 2;
		else
			ed->bLength = sizeof(*ed);
		ed->bDescriptorType = UDESC_ENDPOINT;
		ed->bEndpointAddress = ea;
		ed->bmAttributes = ted->bmAttributes;
		USETW(ed->wMaxPacketSize, mps);

		/* setup bInterval parameter */

		if (ted->pIntervals &&
		    ted->pIntervals->bInterval[temp->usb_speed]) {
			ed->bInterval =
			    ted->pIntervals->bInterval[temp->usb_speed];
		} else {
			switch (et) {
			case UE_BULK:
			case UE_CONTROL:
				ed->bInterval = 0;	/* not used */
				break;
			case UE_INTERRUPT:
				switch (temp->usb_speed) {
				case USB_SPEED_LOW:
				case USB_SPEED_FULL:
					ed->bInterval = 1;	/* 1 ms */
					break;
				default:
					ed->bInterval = 4;	/* 1 ms */
					break;
				}
				break;
			default:	/* UE_ISOCHRONOUS */
				switch (temp->usb_speed) {
				case USB_SPEED_LOW:
				case USB_SPEED_FULL:
					ed->bInterval = 1;	/* 1 ms */
					break;
				default:
					ed->bInterval = 1;	/* 125 us */
					break;
				}
				break;
			}
		}
	}
	temp->bNumEndpoints++;
}
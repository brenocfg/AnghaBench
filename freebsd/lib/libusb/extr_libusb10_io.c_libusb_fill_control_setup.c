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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct libusb_control_setup {void* wLength; void* wIndex; void* wValue; void* bRequest; void* bmRequestType; } ;

/* Variables and functions */
 void* htole16 (int /*<<< orphan*/ ) ; 

void
libusb_fill_control_setup(uint8_t *buf, uint8_t bmRequestType,
    uint8_t bRequest, uint16_t wValue,
    uint16_t wIndex, uint16_t wLength)
{
	struct libusb_control_setup *req = (struct libusb_control_setup *)buf;

	/* The alignment is OK for all fields below. */
	req->bmRequestType = bmRequestType;
	req->bRequest = bRequest;
	req->wValue = htole16(wValue);
	req->wIndex = htole16(wIndex);
	req->wLength = htole16(wLength);
}
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
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;

/* Variables and functions */
 int /*<<< orphan*/  UR_GET_REPORT ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 

__attribute__((used)) static void
uhid_fill_get_report(struct usb_device_request *req, uint8_t iface_no,
    uint8_t type, uint8_t id, uint16_t size)
{
	req->bmRequestType = UT_READ_CLASS_INTERFACE;
	req->bRequest = UR_GET_REPORT;
	USETW2(req->wValue, type, id);
	req->wIndex[0] = iface_no;
	req->wIndex[1] = 0;
	USETW(req->wLength, size);
}
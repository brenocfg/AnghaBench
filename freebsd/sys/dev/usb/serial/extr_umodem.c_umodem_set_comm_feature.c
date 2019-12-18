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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;
struct usb_cdc_abstract_state {int /*<<< orphan*/  wState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCDC_ABSTRACT_STATE_LENGTH ; 
 int /*<<< orphan*/  UCDC_SET_COMM_FEATURE ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  usbd_do_request (struct usb_device*,int /*<<< orphan*/ *,struct usb_device_request*,struct usb_cdc_abstract_state*) ; 

__attribute__((used)) static usb_error_t
umodem_set_comm_feature(struct usb_device *udev, uint8_t iface_no,
    uint16_t feature, uint16_t state)
{
	struct usb_device_request req;
	struct usb_cdc_abstract_state ast;

	DPRINTF("feature=%d state=%d\n",
	    feature, state);

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SET_COMM_FEATURE;
	USETW(req.wValue, feature);
	req.wIndex[0] = iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, UCDC_ABSTRACT_STATE_LENGTH);
	USETW(ast.wState, state);

	return (usbd_do_request(udev, NULL, &req, &ast));
}
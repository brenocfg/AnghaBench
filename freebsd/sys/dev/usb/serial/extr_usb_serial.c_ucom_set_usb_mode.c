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
struct ucom_super_softc {int /*<<< orphan*/  sc_flag; } ;
typedef  enum usb_hc_mode { ____Placeholder_usb_hc_mode } usb_hc_mode ;

/* Variables and functions */
 int /*<<< orphan*/  UCOM_FLAG_DEVICE_MODE ; 
#define  USB_MODE_DEVICE 128 

void
ucom_set_usb_mode(struct ucom_super_softc *ssc, enum usb_hc_mode usb_mode)
{

	switch (usb_mode) {
	case USB_MODE_DEVICE:
		ssc->sc_flag |= UCOM_FLAG_DEVICE_MODE;
		break;
	default:
		ssc->sc_flag &= ~UCOM_FLAG_DEVICE_MODE;
		break;
	}
}
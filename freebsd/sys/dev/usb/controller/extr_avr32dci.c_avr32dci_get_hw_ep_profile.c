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
struct usb_hw_ep_profile {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct usb_hw_ep_profile* avr32dci_ep_profile ; 

__attribute__((used)) static void
avr32dci_get_hw_ep_profile(struct usb_device *udev,
    const struct usb_hw_ep_profile **ppf, uint8_t ep_addr)
{
	if (ep_addr == 0)
		*ppf = avr32dci_ep_profile;
	else if (ep_addr < 3)
		*ppf = avr32dci_ep_profile + 1;
	else if (ep_addr < 5)
		*ppf = avr32dci_ep_profile + 2;
	else if (ep_addr < 7)
		*ppf = avr32dci_ep_profile + 3;
	else
		*ppf = NULL;
}
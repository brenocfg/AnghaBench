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
struct usb_hw_ep_profile {scalar_t__ support_control; scalar_t__ support_bulk; scalar_t__ support_isochronous; scalar_t__ support_interrupt; scalar_t__ support_out; scalar_t__ support_in; } ;

/* Variables and functions */
 scalar_t__ UE_BULK ; 
 scalar_t__ UE_CONTROL ; 
 scalar_t__ UE_INTERRUPT ; 
 scalar_t__ UE_ISOCHRONOUS ; 

__attribute__((used)) static uint8_t
usb_hw_ep_match(const struct usb_hw_ep_profile *pf,
    uint8_t ep_type, uint8_t ep_dir_in)
{
	if (ep_type == UE_CONTROL) {
		/* special */
		return (pf->support_control);
	}
	if ((pf->support_in && ep_dir_in) ||
	    (pf->support_out && !ep_dir_in)) {
		if ((pf->support_interrupt && (ep_type == UE_INTERRUPT)) ||
		    (pf->support_isochronous && (ep_type == UE_ISOCHRONOUS)) ||
		    (pf->support_bulk && (ep_type == UE_BULK))) {
			return (1);
		}
	}
	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_hw_ep_scratch_sub {scalar_t__ max_frame_size; int hw_endpoint_in; int hw_endpoint_out; scalar_t__ needs_out; scalar_t__ needs_in; struct usb_hw_ep_profile const* pf; int /*<<< orphan*/  needs_ep_type; } ;
struct usb_hw_ep_scratch {int* bmInAlloc; int* bmOutAlloc; int /*<<< orphan*/  udev; TYPE_1__* methods; } ;
typedef  struct usb_hw_ep_profile {int is_simplex; scalar_t__ max_in_frame_size; scalar_t__ max_out_frame_size; } const usb_hw_ep_profile ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_hw_ep_profile ) (int /*<<< orphan*/ ,struct usb_hw_ep_profile const**,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UE_CONTROL ; 
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
 int USB_EP_MAX ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct usb_hw_ep_profile const**,int) ; 
 int /*<<< orphan*/  usb_hw_ep_match (struct usb_hw_ep_profile const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
usb_hw_ep_find_match(struct usb_hw_ep_scratch *ues,
    struct usb_hw_ep_scratch_sub *ep, uint8_t is_simplex)
{
	const struct usb_hw_ep_profile *pf;
	uint16_t distance;
	uint16_t temp;
	uint16_t max_frame_size;
	uint8_t n;
	uint8_t best_n;
	uint8_t dir_in;
	uint8_t dir_out;

	distance = 0xFFFF;
	best_n = 0;

	if ((!ep->needs_in) && (!ep->needs_out)) {
		return (0);		/* we are done */
	}
	if (ep->needs_ep_type == UE_CONTROL) {
		dir_in = 1;
		dir_out = 1;
	} else {
		if (ep->needs_in) {
			dir_in = 1;
			dir_out = 0;
		} else {
			dir_in = 0;
			dir_out = 1;
		}
	}

	for (n = 1; n != (USB_EP_MAX / 2); n++) {

		/* get HW endpoint profile */
		(ues->methods->get_hw_ep_profile) (ues->udev, &pf, n);
		if (pf == NULL) {
			/* end of profiles */
			break;
		}
		/* check if IN-endpoint is reserved */
		if (dir_in || pf->is_simplex) {
			if (ues->bmInAlloc[n / 8] & (1 << (n % 8))) {
				/* mismatch */
				continue;
			}
		}
		/* check if OUT-endpoint is reserved */
		if (dir_out || pf->is_simplex) {
			if (ues->bmOutAlloc[n / 8] & (1 << (n % 8))) {
				/* mismatch */
				continue;
			}
		}
		/* check simplex */
		if (pf->is_simplex == is_simplex) {
			/* mismatch */
			continue;
		}
		/* check if HW endpoint matches */
		if (!usb_hw_ep_match(pf, ep->needs_ep_type, dir_in)) {
			/* mismatch */
			continue;
		}
		/* get maximum frame size */
		if (dir_in)
			max_frame_size = pf->max_in_frame_size;
		else
			max_frame_size = pf->max_out_frame_size;

		/* check if we have a matching profile */
		if (max_frame_size >= ep->max_frame_size) {
			temp = (max_frame_size - ep->max_frame_size);
			if (distance > temp) {
				distance = temp;
				best_n = n;
				ep->pf = pf;
			}
		}
	}

	/* see if we got a match */
	if (best_n != 0) {
		/* get the correct profile */
		pf = ep->pf;

		/* reserve IN-endpoint */
		if (dir_in) {
			ues->bmInAlloc[best_n / 8] |=
			    (1 << (best_n % 8));
			ep->hw_endpoint_in = best_n | UE_DIR_IN;
			ep->needs_in = 0;
		}
		/* reserve OUT-endpoint */
		if (dir_out) {
			ues->bmOutAlloc[best_n / 8] |=
			    (1 << (best_n % 8));
			ep->hw_endpoint_out = best_n | UE_DIR_OUT;
			ep->needs_out = 0;
		}
		return (0);		/* got a match */
	}
	return (1);			/* failure */
}
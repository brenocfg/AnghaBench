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
struct urb {int /*<<< orphan*/  cv_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

void
usb_free_urb(struct urb *urb)
{
	if (urb == NULL) {
		return;
	}
	/* make sure that the current URB is not active */
	usb_kill_urb(urb);

	/* destroy condition variable */
	cv_destroy(&urb->cv_wait);

	/* just free it */
	free(urb, M_USBDEV);
}
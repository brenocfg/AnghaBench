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
struct usb_process {int /*<<< orphan*/ * up_mtx; int /*<<< orphan*/  up_drain; int /*<<< orphan*/  up_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_drain (struct usb_process*) ; 

void
usb_proc_free(struct usb_process *up)
{
	/* check if not initialised */
	if (up->up_mtx == NULL)
		return;

	usb_proc_drain(up);

	cv_destroy(&up->up_cv);
	cv_destroy(&up->up_drain);

	/* make sure that we do not enter here again */
	up->up_mtx = NULL;
}
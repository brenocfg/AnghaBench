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
struct usb_process {int /*<<< orphan*/ * up_mtx; int /*<<< orphan*/  up_drain; int /*<<< orphan*/  up_cv; int /*<<< orphan*/  up_qhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_proc_mtx ; 

__attribute__((used)) static void
usb_process_init_sub(struct usb_process *up)
{
	TAILQ_INIT(&up->up_qhead);

	cv_init(&up->up_cv, "-");
	cv_init(&up->up_drain, "usbdrain");

	up->up_mtx = &usb_proc_mtx;
}
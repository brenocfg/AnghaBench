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
struct TYPE_2__ {int /*<<< orphan*/  curr; } ;
struct usb_xfer_root {int /*<<< orphan*/  xfer_mtx; TYPE_1__ done_q; int /*<<< orphan*/  bus; } ;
struct usb_proc_msg {int dummy; } ;
struct usb_done_msg {struct usb_xfer_root* xroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_command_wrapper (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_callback_proc(struct usb_proc_msg *_pm)
{
	struct usb_done_msg *pm = (void *)_pm;
	struct usb_xfer_root *info = pm->xroot;

	/* Change locking order */
	USB_BUS_UNLOCK(info->bus);

	/*
	 * We exploit the fact that the mutex is the same for all
	 * callbacks that will be called from this thread:
	 */
	USB_MTX_LOCK(info->xfer_mtx);
	USB_BUS_LOCK(info->bus);

	/* Continue where we lost track */
	usb_command_wrapper(&info->done_q,
	    info->done_q.curr);

	USB_MTX_UNLOCK(info->xfer_mtx);
}
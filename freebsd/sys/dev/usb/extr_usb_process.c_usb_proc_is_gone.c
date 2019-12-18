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
struct usb_process {int /*<<< orphan*/ * up_mtx; scalar_t__ up_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint8_t
usb_proc_is_gone(struct usb_process *up)
{
	if (up->up_gone)
		return (1);

	/*
	 * Allow calls when up_mtx is NULL, before the USB process
	 * structure is initialised.
	 */
	if (up->up_mtx != NULL)
		USB_MTX_ASSERT(up->up_mtx, MA_OWNED);
	return (0);
}
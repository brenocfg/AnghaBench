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
struct usb_xfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  umcs7840_write_callbackN (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
umcs7840_write_callback4(struct usb_xfer *xfer, usb_error_t error)
{
	umcs7840_write_callbackN(xfer, error, 3);
}
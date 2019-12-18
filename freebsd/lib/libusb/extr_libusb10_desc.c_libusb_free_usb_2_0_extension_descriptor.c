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
struct libusb_usb_2_0_extension_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libusb_usb_2_0_extension_descriptor*) ; 

void
libusb_free_usb_2_0_extension_descriptor(
    struct libusb_usb_2_0_extension_descriptor *usb_2_0_extension)
{

	free(usb_2_0_extension);
}
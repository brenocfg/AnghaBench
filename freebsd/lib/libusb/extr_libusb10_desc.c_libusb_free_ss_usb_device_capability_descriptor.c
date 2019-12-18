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
struct libusb_ss_usb_device_capability_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libusb_ss_usb_device_capability_descriptor*) ; 

void
libusb_free_ss_usb_device_capability_descriptor(
    struct libusb_ss_usb_device_capability_descriptor *ss_usb_device_capability)
{

	free(ss_usb_device_capability);
}
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
struct usb_interface {scalar_t__ num_altsetting; struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;

/* Variables and functions */

struct usb_host_interface *
usb_altnum_to_altsetting(const struct usb_interface *intf, uint8_t alt_index)
{
	if (alt_index >= intf->num_altsetting) {
		return (NULL);
	}
	return (intf->altsetting + alt_index);
}
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
struct usb_attach_arg {scalar_t__ usb_mode; } ;
struct umass_probe_proto {int error; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ USB_MODE_HOST ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct umass_probe_proto umass_probe_proto (int /*<<< orphan*/ ,struct usb_attach_arg*) ; 

__attribute__((used)) static int
umass_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct umass_probe_proto temp;

	if (uaa->usb_mode != USB_MODE_HOST) {
		return (ENXIO);
	}
	temp = umass_probe_proto(dev, uaa);

	return (temp.error);
}
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
typedef  int /*<<< orphan*/  usb_size_t ;
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct usb_attach_arg {int /*<<< orphan*/  driver_info; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int ENXIO ; 
 struct usb_device_id* usbd_lookup_id_by_info (struct usb_device_id const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
usbd_lookup_id_by_uaa(const struct usb_device_id *id, usb_size_t sizeof_id,
    struct usb_attach_arg *uaa)
{
	id = usbd_lookup_id_by_info(id, sizeof_id, &uaa->info);
	if (id) {
		/* copy driver info */
		uaa->driver_info = id->driver_info;
		return (0);
	}
	return (ENXIO);
}
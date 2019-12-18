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
struct usb_device_descriptor {int dummy; } ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  UDESC_DEVICE ; 
 int /*<<< orphan*/  usbd_req_get_desc (struct usb_device*,struct mtx*,int /*<<< orphan*/ *,struct usb_device_descriptor*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

usb_error_t
usbd_req_get_device_desc(struct usb_device *udev, struct mtx *mtx,
    struct usb_device_descriptor *d)
{
	DPRINTFN(4, "\n");
	return (usbd_req_get_desc(udev, mtx, NULL, d, sizeof(*d),
	    sizeof(*d), 0, UDESC_DEVICE, 0, 3));
}
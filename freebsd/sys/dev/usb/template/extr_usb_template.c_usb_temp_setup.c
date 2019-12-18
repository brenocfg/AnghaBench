#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_temp_setup {scalar_t__ size; void* err; int /*<<< orphan*/ * buf; int /*<<< orphan*/  self_powered; int /*<<< orphan*/  usb_speed; } ;
struct usb_temp_device_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  self_powered; } ;
struct TYPE_3__ {struct usb_temp_setup* temp_setup; } ;
struct usb_device {int /*<<< orphan*/ * usb_template_ptr; TYPE_2__ flags; int /*<<< orphan*/  speed; TYPE_1__ scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 void* USB_ERR_INVAL ; 
 void* USB_ERR_NOMEM ; 
 int /*<<< orphan*/  memset (struct usb_temp_setup*,int /*<<< orphan*/ ,int) ; 
 void* usb_hw_ep_resolve (struct usb_device*,void*) ; 
 int /*<<< orphan*/  usb_make_device_desc (struct usb_temp_setup*,struct usb_temp_device_desc const*) ; 
 void* usb_temp_get_config_desc (struct usb_device*,int /*<<< orphan*/ *,scalar_t__) ; 
 void* usb_temp_get_device_desc (struct usb_device*) ; 
 int /*<<< orphan*/  usb_temp_unsetup (struct usb_device*) ; 
 int /*<<< orphan*/ * usbd_alloc_config_desc (struct usb_device*,scalar_t__) ; 
 scalar_t__ usbd_ctrl_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_ctrl_unlock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_errstr (void*) ; 

usb_error_t
usb_temp_setup(struct usb_device *udev,
    const struct usb_temp_device_desc *tdd)
{
	struct usb_temp_setup *uts;
	void *buf;
	usb_error_t error;
	uint8_t n;
	uint8_t do_unlock;

	/* be NULL safe */
	if (tdd == NULL)
		return (0);

	/* Protect scratch area */
	do_unlock = usbd_ctrl_lock(udev);

	uts = udev->scratch.temp_setup;

	memset(uts, 0, sizeof(*uts));

	uts->usb_speed = udev->speed;
	uts->self_powered = udev->flags.self_powered;

	/* first pass */

	usb_make_device_desc(uts, tdd);

	if (uts->err) {
		/* some error happened */
		goto done;
	}
	/* sanity check */
	if (uts->size == 0) {
		uts->err = USB_ERR_INVAL;
		goto done;
	}
	/* allocate zeroed memory */
	uts->buf = usbd_alloc_config_desc(udev, uts->size);
	/*
	 * Allow malloc() to return NULL regardless of M_WAITOK flag.
	 * This helps when porting the software to non-FreeBSD
	 * systems.
	 */
	if (uts->buf == NULL) {
		/* could not allocate memory */
		uts->err = USB_ERR_NOMEM;
		goto done;
	}
	/* second pass */

	uts->size = 0;

	usb_make_device_desc(uts, tdd);

	/*
	 * Store a pointer to our descriptors:
	 */
	udev->usb_template_ptr = uts->buf;

	if (uts->err) {
		/* some error happened during second pass */
		goto done;
	}
	/*
	 * Resolve all endpoint addresses !
	 */
	buf = usb_temp_get_device_desc(udev);
	uts->err = usb_hw_ep_resolve(udev, buf);
	if (uts->err) {
		DPRINTFN(0, "Could not resolve endpoints for "
		    "Device Descriptor, error = %s\n",
		    usbd_errstr(uts->err));
		goto done;
	}
	for (n = 0;; n++) {

		buf = usb_temp_get_config_desc(udev, NULL, n);
		if (buf == NULL) {
			break;
		}
		uts->err = usb_hw_ep_resolve(udev, buf);
		if (uts->err) {
			DPRINTFN(0, "Could not resolve endpoints for "
			    "Config Descriptor %u, error = %s\n", n,
			    usbd_errstr(uts->err));
			goto done;
		}
	}
done:
	error = uts->err;
	if (error)
		usb_temp_unsetup(udev);
	if (do_unlock)
		usbd_ctrl_unlock(udev);
	return (error);
}
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
struct usb_endpoint {int /*<<< orphan*/ * edesc; } ;
struct usb_device {int endpoints_max; struct usb_endpoint* endpoints; } ;

/* Variables and functions */

struct usb_endpoint *
usb_endpoint_foreach(struct usb_device *udev, struct usb_endpoint *ep)
{
	struct usb_endpoint *ep_end;

	/* be NULL safe */
	if (udev == NULL)
		return (NULL);

	ep_end = udev->endpoints + udev->endpoints_max;

	/* get next endpoint */
	if (ep == NULL)
		ep = udev->endpoints;
	else
		ep++;

	/* find next allocated ep */
	while (ep != ep_end) {
		if (ep->edesc != NULL)
			return (ep);
		ep++;
	}
	return (NULL);
}
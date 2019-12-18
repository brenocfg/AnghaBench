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
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_interface_descriptor {int /*<<< orphan*/  bNumEndpoints; } ;
struct usb_interface {scalar_t__ iface_index; scalar_t__ refcount_alloc; scalar_t__ iface_index_alt; scalar_t__ parent_iface_index; scalar_t__ alt_index; struct usb_interface_descriptor* idesc; } ;
struct usb_idesc_parse_state {scalar_t__ iface_index; scalar_t__ refcount_alloc; scalar_t__ iface_index_alt; scalar_t__ parent_iface_index; scalar_t__ alt_index; struct usb_interface_descriptor* idesc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_endpoint {scalar_t__ iface_index; scalar_t__ refcount_alloc; scalar_t__ iface_index_alt; scalar_t__ parent_iface_index; scalar_t__ alt_index; struct usb_interface_descriptor* idesc; } ;
struct usb_device {scalar_t__ endpoints_max; scalar_t__ ifaces_max; struct usb_interface* endpoints; struct usb_interface* ifaces; int /*<<< orphan*/  bus; int /*<<< orphan*/ * ep_curr; int /*<<< orphan*/  cdesc; int /*<<< orphan*/  enum_sx; } ;
typedef  int /*<<< orphan*/  ips ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  M_USB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SA_LOCKED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_CFG_ALLOC ; 
 scalar_t__ USB_CFG_FREE ; 
 scalar_t__ USB_CFG_INIT ; 
 scalar_t__ USB_ERR_IN_USE ; 
 scalar_t__ USB_ERR_NOMEM ; 
 scalar_t__ USB_IFACE_INDEX_ANY ; 
 scalar_t__ USB_MAX_EP_UNITS ; 
 int /*<<< orphan*/  free (struct usb_interface*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct usb_interface*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* usb_ed_comp_foreach (int /*<<< orphan*/ ,void*) ; 
 struct usb_endpoint_descriptor* usb_edesc_foreach (int /*<<< orphan*/ ,struct usb_endpoint_descriptor*) ; 
 struct usb_interface_descriptor* usb_idesc_foreach (int /*<<< orphan*/ ,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_init_endpoint (struct usb_device*,scalar_t__,struct usb_endpoint_descriptor*,void*,struct usb_interface*) ; 

__attribute__((used)) static usb_error_t
usb_config_parse(struct usb_device *udev, uint8_t iface_index, uint8_t cmd)
{
	struct usb_idesc_parse_state ips;
	struct usb_interface_descriptor *id;
	struct usb_endpoint_descriptor *ed;
	struct usb_interface *iface;
	struct usb_endpoint *ep;
	usb_error_t err;
	uint8_t ep_curr;
	uint8_t ep_max;
	uint8_t temp;
	uint8_t do_init;
	uint8_t alt_index;

	if (iface_index != USB_IFACE_INDEX_ANY) {
		/* parameter overload */
		alt_index = cmd;
		cmd = USB_CFG_INIT;
	} else {
		/* not used */
		alt_index = 0;
	}

	err = 0;

	DPRINTFN(5, "iface_index=%d cmd=%d\n",
	    iface_index, cmd);

	if (cmd == USB_CFG_FREE)
		goto cleanup;

	if (cmd == USB_CFG_INIT) {
		sx_assert(&udev->enum_sx, SA_LOCKED);

		/* check for in-use endpoints */

		ep = udev->endpoints;
		ep_max = udev->endpoints_max;
		while (ep_max--) {
			/* look for matching endpoints */
			if ((iface_index == USB_IFACE_INDEX_ANY) ||
			    (iface_index == ep->iface_index)) {
				if (ep->refcount_alloc != 0) {
					/*
					 * This typically indicates a
					 * more serious error.
					 */
					err = USB_ERR_IN_USE;
				} else {
					/* reset endpoint */
					memset(ep, 0, sizeof(*ep));
					/* make sure we don't zero the endpoint again */
					ep->iface_index = USB_IFACE_INDEX_ANY;
				}
			}
			ep++;
		}

		if (err)
			return (err);
	}

	memset(&ips, 0, sizeof(ips));

	ep_curr = 0;
	ep_max = 0;

	while ((id = usb_idesc_foreach(udev->cdesc, &ips))) {

		iface = udev->ifaces + ips.iface_index;

		/* check for specific interface match */

		if (cmd == USB_CFG_INIT) {
			if ((iface_index != USB_IFACE_INDEX_ANY) && 
			    (iface_index != ips.iface_index)) {
				/* wrong interface */
				do_init = 0;
			} else if (alt_index != ips.iface_index_alt) {
				/* wrong alternate setting */
				do_init = 0;
			} else {
				/* initialise interface */
				do_init = 1;
			}
		} else
			do_init = 0;

		/* check for new interface */
		if (ips.iface_index_alt == 0) {
			/* update current number of endpoints */
			ep_curr = ep_max;
		}
		/* check for init */
		if (do_init) {
			/* setup the USB interface structure */
			iface->idesc = id;
			/* set alternate index */
			iface->alt_index = alt_index;
			/* set default interface parent */
			if (iface_index == USB_IFACE_INDEX_ANY) {
				iface->parent_iface_index =
				    USB_IFACE_INDEX_ANY;
			}
		}

		DPRINTFN(5, "found idesc nendpt=%d\n", id->bNumEndpoints);

		ed = (struct usb_endpoint_descriptor *)id;

		temp = ep_curr;

		/* iterate all the endpoint descriptors */
		while ((ed = usb_edesc_foreach(udev->cdesc, ed))) {

			/* check if endpoint limit has been reached */
			if (temp >= USB_MAX_EP_UNITS) {
				DPRINTF("Endpoint limit reached\n");
				break;
			}

			ep = udev->endpoints + temp;

			if (do_init) {
				void *ecomp;

				ecomp = usb_ed_comp_foreach(udev->cdesc, (void *)ed);
				if (ecomp != NULL)
					DPRINTFN(5, "Found endpoint companion descriptor\n");

				usb_init_endpoint(udev, 
				    ips.iface_index, ed, ecomp, ep);
			}

			temp ++;

			/* find maximum number of endpoints */
			if (ep_max < temp)
				ep_max = temp;
		}
	}

	/* NOTE: It is valid to have no interfaces and no endpoints! */

	if (cmd == USB_CFG_ALLOC) {
		udev->ifaces_max = ips.iface_index;
#if (USB_HAVE_FIXED_IFACE == 0)
		udev->ifaces = NULL;
		if (udev->ifaces_max != 0) {
			udev->ifaces = malloc(sizeof(*iface) * udev->ifaces_max,
			        M_USB, M_WAITOK | M_ZERO);
			if (udev->ifaces == NULL) {
				err = USB_ERR_NOMEM;
				goto done;
			}
		}
#endif
#if (USB_HAVE_FIXED_ENDPOINT == 0)
		if (ep_max != 0) {
			udev->endpoints = malloc(sizeof(*ep) * ep_max,
			        M_USB, M_WAITOK | M_ZERO);
			if (udev->endpoints == NULL) {
				err = USB_ERR_NOMEM;
				goto done;
			}
		} else {
			udev->endpoints = NULL;
		}
#endif
		USB_BUS_LOCK(udev->bus);
		udev->endpoints_max = ep_max;
		/* reset any ongoing clear-stall */
		udev->ep_curr = NULL;
		USB_BUS_UNLOCK(udev->bus);
	}
#if (USB_HAVE_FIXED_IFACE == 0) || (USB_HAVE_FIXED_ENDPOINT == 0) 
done:
#endif
	if (err) {
		if (cmd == USB_CFG_ALLOC) {
cleanup:
			USB_BUS_LOCK(udev->bus);
			udev->endpoints_max = 0;
			/* reset any ongoing clear-stall */
			udev->ep_curr = NULL;
			USB_BUS_UNLOCK(udev->bus);

#if (USB_HAVE_FIXED_IFACE == 0)
			free(udev->ifaces, M_USB);
			udev->ifaces = NULL;
#endif
#if (USB_HAVE_FIXED_ENDPOINT == 0)
			free(udev->endpoints, M_USB);
			udev->endpoints = NULL;
#endif
			udev->ifaces_max = 0;
		}
	}
	return (err);
}
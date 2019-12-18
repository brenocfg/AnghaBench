#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct usb_interface_descriptor {scalar_t__ bInterfaceNumber; } ;
struct usb_interface {int dummy; } ;
struct usb_config_descriptor {int dummy; } ;
struct usb_cdc_cm_descriptor {int bLength; int bmCapabilities; scalar_t__ bDataInterface; } ;
struct usb_cdc_acm_descriptor {int bLength; int bmCapabilities; } ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; struct usb_interface* iface; } ;
struct ufoma_softc {int sc_cm_cap; scalar_t__ sc_data_iface_no; int sc_acm_cap; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_bulk_xfer; scalar_t__ sc_data_iface_index; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UDESCSUB_CDC_ACM ; 
 int /*<<< orphan*/  UDESCSUB_CDC_CM ; 
 int /*<<< orphan*/  UDESC_CS_INTERFACE ; 
 int /*<<< orphan*/  UFOMA_BULK_ENDPT_MAX ; 
 int USB_CDC_ACM_HAS_BREAK ; 
 int USB_CDC_CM_OVER_DATA ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ufoma_bulk_config ; 
 void* ufoma_get_intconf (struct usb_config_descriptor*,struct usb_interface_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_config_descriptor* usbd_get_config_descriptor (int /*<<< orphan*/ ) ; 
 struct usb_interface* usbd_get_iface (int /*<<< orphan*/ ,scalar_t__) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (struct usb_interface*) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ufoma_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ufoma_modem_setup(device_t dev, struct ufoma_softc *sc,
    struct usb_attach_arg *uaa)
{
	struct usb_config_descriptor *cd;
	struct usb_cdc_acm_descriptor *acm;
	struct usb_cdc_cm_descriptor *cmd;
	struct usb_interface_descriptor *id;
	struct usb_interface *iface;
	uint8_t i;
	int32_t error;

	cd = usbd_get_config_descriptor(uaa->device);
	id = usbd_get_interface_descriptor(uaa->iface);

	cmd = ufoma_get_intconf(cd, id, UDESC_CS_INTERFACE, UDESCSUB_CDC_CM);

	if ((cmd == NULL) ||
	    (cmd->bLength < sizeof(*cmd))) {
		return (EINVAL);
	}
	sc->sc_cm_cap = cmd->bmCapabilities;
	sc->sc_data_iface_no = cmd->bDataInterface;

	acm = ufoma_get_intconf(cd, id, UDESC_CS_INTERFACE, UDESCSUB_CDC_ACM);

	if ((acm == NULL) ||
	    (acm->bLength < sizeof(*acm))) {
		return (EINVAL);
	}
	sc->sc_acm_cap = acm->bmCapabilities;

	device_printf(dev, "data interface %d, has %sCM over data, "
	    "has %sbreak\n",
	    sc->sc_data_iface_no,
	    sc->sc_cm_cap & USB_CDC_CM_OVER_DATA ? "" : "no ",
	    sc->sc_acm_cap & USB_CDC_ACM_HAS_BREAK ? "" : "no ");

	/* get the data interface too */

	for (i = 0;; i++) {

		iface = usbd_get_iface(uaa->device, i);

		if (iface) {

			id = usbd_get_interface_descriptor(iface);

			if (id && (id->bInterfaceNumber == sc->sc_data_iface_no)) {
				sc->sc_data_iface_index = i;
				usbd_set_parent_iface(uaa->device, i, uaa->info.bIfaceIndex);
				break;
			}
		} else {
			device_printf(dev, "no data interface\n");
			return (EINVAL);
		}
	}

	error = usbd_transfer_setup(uaa->device,
	    &sc->sc_data_iface_index, sc->sc_bulk_xfer,
	    ufoma_bulk_config, UFOMA_BULK_ENDPT_MAX, sc, &sc->sc_mtx);

	if (error) {
		device_printf(dev, "allocating BULK USB "
		    "transfers failed\n");
		return (EINVAL);
	}
	return (0);
}
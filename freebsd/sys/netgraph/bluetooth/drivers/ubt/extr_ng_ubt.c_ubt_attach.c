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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_interface_descriptor {int bInterfaceNumber; int bAlternateSetting; scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct usb_interface {int dummy; } ;
struct usb_endpoint_descriptor {scalar_t__ bDescriptorType; int bLength; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_descriptor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct ubt_softc {int /*<<< orphan*/  sc_if_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_task; int /*<<< orphan*/  sc_scoq; int /*<<< orphan*/  sc_aclq; int /*<<< orphan*/  sc_cmdq; int /*<<< orphan*/  sc_ng_mtx; int /*<<< orphan*/  sc_node; int /*<<< orphan*/  sc_debug; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_FORCE_WRITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,struct ubt_softc*) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_UBT_WARN_LEVEL ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_ALERT (struct ubt_softc*,char*,...) ; 
 int /*<<< orphan*/  UBT_DEFAULT_QLEN ; 
 int /*<<< orphan*/  UBT_N_TRANSFER ; 
 scalar_t__ UDESC_ENDPOINT ; 
 scalar_t__ UDESC_INTERFACE ; 
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ UICLASS_WIRELESS ; 
 scalar_t__ UIPROTO_BLUETOOTH ; 
 scalar_t__ UISUBCLASS_RF ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ubt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ng_make_node_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typestruct ; 
 int /*<<< orphan*/  ubt_config ; 
 int /*<<< orphan*/  ubt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubt_task ; 
 scalar_t__ usb_desc_foreach (int /*<<< orphan*/ ,struct usb_descriptor*) ; 
 int /*<<< orphan*/  usbd_get_config_descriptor (int /*<<< orphan*/ ) ; 
 struct usb_interface* usbd_get_iface (int /*<<< orphan*/ ,int) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (struct usb_interface*) ; 
 scalar_t__ usbd_set_alt_interface_index (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubt_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ubt_attach(device_t dev)
{
	struct usb_attach_arg		*uaa = device_get_ivars(dev);
	struct ubt_softc		*sc = device_get_softc(dev);
	struct usb_endpoint_descriptor	*ed;
	struct usb_interface_descriptor *id;
	struct usb_interface		*iface;
	uint16_t			wMaxPacketSize;
	uint8_t				alt_index, i, j;
	uint8_t				iface_index[2] = { 0, 1 };

	device_set_usb_desc(dev);

	sc->sc_dev = dev;
	sc->sc_debug = NG_UBT_WARN_LEVEL;

	/* 
	 * Create Netgraph node
	 */

	if (ng_make_node_common(&typestruct, &sc->sc_node) != 0) {
		UBT_ALERT(sc, "could not create Netgraph node\n");
		return (ENXIO);
	}

	/* Name Netgraph node */
	if (ng_name_node(sc->sc_node, device_get_nameunit(dev)) != 0) {
		UBT_ALERT(sc, "could not name Netgraph node\n");
		NG_NODE_UNREF(sc->sc_node);
		return (ENXIO);
	}
	NG_NODE_SET_PRIVATE(sc->sc_node, sc);
	NG_NODE_FORCE_WRITER(sc->sc_node);

	/*
	 * Initialize device softc structure
	 */

	/* initialize locks */
	mtx_init(&sc->sc_ng_mtx, "ubt ng", NULL, MTX_DEF);
	mtx_init(&sc->sc_if_mtx, "ubt if", NULL, MTX_DEF | MTX_RECURSE);

	/* initialize packet queues */
	NG_BT_MBUFQ_INIT(&sc->sc_cmdq, UBT_DEFAULT_QLEN);
	NG_BT_MBUFQ_INIT(&sc->sc_aclq, UBT_DEFAULT_QLEN);
	NG_BT_MBUFQ_INIT(&sc->sc_scoq, UBT_DEFAULT_QLEN);

	/* initialize glue task */
	TASK_INIT(&sc->sc_task, 0, ubt_task, sc);

	/*
	 * Configure Bluetooth USB device. Discover all required USB
	 * interfaces and endpoints.
	 *
	 * USB device must present two interfaces:
	 * 1) Interface 0 that has 3 endpoints
	 *	1) Interrupt endpoint to receive HCI events
	 *	2) Bulk IN endpoint to receive ACL data
	 *	3) Bulk OUT endpoint to send ACL data
	 *
	 * 2) Interface 1 then has 2 endpoints
	 *	1) Isochronous IN endpoint to receive SCO data
 	 *	2) Isochronous OUT endpoint to send SCO data
	 *
	 * Interface 1 (with isochronous endpoints) has several alternate
	 * configurations with different packet size.
	 */

	/*
	 * For interface #1 search alternate settings, and find
	 * the descriptor with the largest wMaxPacketSize
	 */

	wMaxPacketSize = 0;
	alt_index = 0;
	i = 0;
	j = 0;
	ed = NULL;

	/* 
	 * Search through all the descriptors looking for the largest
	 * packet size:
	 */
	while ((ed = (struct usb_endpoint_descriptor *)usb_desc_foreach(
	    usbd_get_config_descriptor(uaa->device), 
	    (struct usb_descriptor *)ed))) {

		if ((ed->bDescriptorType == UDESC_INTERFACE) &&
		    (ed->bLength >= sizeof(*id))) {
			id = (struct usb_interface_descriptor *)ed;
			i = id->bInterfaceNumber;
			j = id->bAlternateSetting;
		}

		if ((ed->bDescriptorType == UDESC_ENDPOINT) &&
		    (ed->bLength >= sizeof(*ed)) &&
		    (i == 1)) {
			uint16_t temp;

			temp = UGETW(ed->wMaxPacketSize);
			if (temp > wMaxPacketSize) {
				wMaxPacketSize = temp;
				alt_index = j;
			}
		}
	}

	/* Set alt configuration on interface #1 only if we found it */
	if (wMaxPacketSize > 0 &&
	    usbd_set_alt_interface_index(uaa->device, 1, alt_index)) {
		UBT_ALERT(sc, "could not set alternate setting %d " \
			"for interface 1!\n", alt_index);
		goto detach;
	}

	/* Setup transfers for both interfaces */
	if (usbd_transfer_setup(uaa->device, iface_index, sc->sc_xfer,
			ubt_config, UBT_N_TRANSFER, sc, &sc->sc_if_mtx)) {
		UBT_ALERT(sc, "could not allocate transfers\n");
		goto detach;
	}

	/* Claim all interfaces belonging to the Bluetooth part */
	for (i = 1;; i++) {
		iface = usbd_get_iface(uaa->device, i);
		if (iface == NULL)
			break;
		id = usbd_get_interface_descriptor(iface);

		if ((id != NULL) &&
		    (id->bInterfaceClass == UICLASS_WIRELESS) &&
		    (id->bInterfaceSubClass == UISUBCLASS_RF) &&
		    (id->bInterfaceProtocol == UIPROTO_BLUETOOTH)) {
			usbd_set_parent_iface(uaa->device, i,
			    uaa->info.bIfaceIndex);
		}
	}
	return (0); /* success */

detach:
	ubt_detach(dev);

	return (ENXIO);
}
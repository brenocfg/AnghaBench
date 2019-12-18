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
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_interface_descriptor {scalar_t__ bInterfaceNumber; } ;
struct usb_interface {int dummy; } ;
struct usb_ether {int* ue_eaddr; int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct cdce_softc* ue_sc; } ;
struct usb_config {int dummy; } ;
struct usb_cdc_union_descriptor {int bLength; scalar_t__* bSlaveInterface; } ;
struct usb_cdc_ethernet_descriptor {int bLength; int /*<<< orphan*/  iMacAddress; } ;
struct TYPE_2__ {scalar_t__ bIfaceIndex; } ;
struct usb_attach_arg {scalar_t__ usb_mode; int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct cdce_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; struct usb_ether sc_ue; int /*<<< orphan*/  sc_xfer; scalar_t__* sc_ifaces_index; } ;
typedef  int /*<<< orphan*/  eaddr_str ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CDCE_FLAG_NO_UNION ; 
 int /*<<< orphan*/  CDCE_N_TRANSFER ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UDESCSUB_CDC_ENF ; 
 int /*<<< orphan*/  UDESCSUB_CDC_UNION ; 
 int /*<<< orphan*/  UDESC_CS_INTERFACE ; 
 int USB_ERR_INVAL ; 
 int USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 struct usb_config* cdce_config ; 
 int /*<<< orphan*/  cdce_detach (int /*<<< orphan*/ ) ; 
 struct usb_config* cdce_ncm_config ; 
 scalar_t__ cdce_ncm_init (struct cdce_softc*) ; 
 int /*<<< orphan*/  cdce_ue_methods ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct cdce_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks ; 
 int uether_ifattach (struct usb_ether*) ; 
 void* usbd_find_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct usb_interface* usbd_get_iface (int /*<<< orphan*/ ,scalar_t__) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (struct usb_interface*) ; 
 int usbd_req_get_string_any (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int usbd_set_alt_interface_index (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,struct usb_config const*,int /*<<< orphan*/ ,struct cdce_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cdce_attach(device_t dev)
{
	struct cdce_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct usb_interface *iface;
	const struct usb_cdc_union_descriptor *ud;
	const struct usb_interface_descriptor *id;
	const struct usb_cdc_ethernet_descriptor *ued;
	const struct usb_config *pcfg;
	uint32_t seed;
	int error;
	uint8_t i;
	uint8_t data_iface_no;
	char eaddr_str[5 * ETHER_ADDR_LEN];	/* approx */

	sc->sc_flags = USB_GET_DRIVER_INFO(uaa);
	sc->sc_ue.ue_udev = uaa->device;

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	ud = usbd_find_descriptor
	    (uaa->device, NULL, uaa->info.bIfaceIndex,
	    UDESC_CS_INTERFACE, 0xFF, UDESCSUB_CDC_UNION, 0xFF);

	if ((ud == NULL) || (ud->bLength < sizeof(*ud)) ||
	    (sc->sc_flags & CDCE_FLAG_NO_UNION)) {
		DPRINTFN(1, "No union descriptor!\n");
		sc->sc_ifaces_index[0] = uaa->info.bIfaceIndex;
		sc->sc_ifaces_index[1] = uaa->info.bIfaceIndex;
		goto alloc_transfers;
	}
	data_iface_no = ud->bSlaveInterface[0];

	for (i = 0;; i++) {

		iface = usbd_get_iface(uaa->device, i);

		if (iface) {

			id = usbd_get_interface_descriptor(iface);

			if (id && (id->bInterfaceNumber == data_iface_no)) {
				sc->sc_ifaces_index[0] = i;
				sc->sc_ifaces_index[1] = uaa->info.bIfaceIndex;
				usbd_set_parent_iface(uaa->device, i, uaa->info.bIfaceIndex);
				break;
			}
		} else {
			device_printf(dev, "no data interface found\n");
			goto detach;
		}
	}

	/*
	 * <quote>
	 *
	 *  The Data Class interface of a networking device shall have
	 *  a minimum of two interface settings. The first setting
	 *  (the default interface setting) includes no endpoints and
	 *  therefore no networking traffic is exchanged whenever the
	 *  default interface setting is selected. One or more
	 *  additional interface settings are used for normal
	 *  operation, and therefore each includes a pair of endpoints
	 *  (one IN, and one OUT) to exchange network traffic. Select
	 *  an alternate interface setting to initialize the network
	 *  aspects of the device and to enable the exchange of
	 *  network traffic.
	 *
	 * </quote>
	 *
	 * Some devices, most notably cable modems, include interface
	 * settings that have no IN or OUT endpoint, therefore loop
	 * through the list of all available interface settings
	 * looking for one with both IN and OUT endpoints.
	 */

alloc_transfers:

	pcfg = cdce_config;	/* Default Configuration */

	for (i = 0; i != 32; i++) {

		error = usbd_set_alt_interface_index(uaa->device,
		    sc->sc_ifaces_index[0], i);
		if (error)
			break;
#if CDCE_HAVE_NCM
		if ((i == 0) && (cdce_ncm_init(sc) == 0))
			pcfg = cdce_ncm_config;
#endif
		error = usbd_transfer_setup(uaa->device,
		    sc->sc_ifaces_index, sc->sc_xfer,
		    pcfg, CDCE_N_TRANSFER, sc, &sc->sc_mtx);

		if (error == 0)
			break;
	}

	if (error || (i == 32)) {
		device_printf(dev, "No valid alternate "
		    "setting found\n");
		goto detach;
	}

	ued = usbd_find_descriptor
	    (uaa->device, NULL, uaa->info.bIfaceIndex,
	    UDESC_CS_INTERFACE, 0xFF, UDESCSUB_CDC_ENF, 0xFF);

	if ((ued == NULL) || (ued->bLength < sizeof(*ued))) {
		error = USB_ERR_INVAL;
	} else {
		error = usbd_req_get_string_any(uaa->device, NULL, 
		    eaddr_str, sizeof(eaddr_str), ued->iMacAddress);
	}

	if (error) {

		/* fake MAC address */

		device_printf(dev, "faking MAC address\n");
		seed = ticks;
		sc->sc_ue.ue_eaddr[0] = 0x2a;
		memcpy(&sc->sc_ue.ue_eaddr[1], &seed, sizeof(uint32_t));
		sc->sc_ue.ue_eaddr[5] = device_get_unit(dev);

	} else {

		memset(sc->sc_ue.ue_eaddr, 0, sizeof(sc->sc_ue.ue_eaddr));

		for (i = 0; i != (ETHER_ADDR_LEN * 2); i++) {

			char c = eaddr_str[i];

			if ('0' <= c && c <= '9')
				c -= '0';
			else if (c != 0)
				c -= 'A' - 10;
			else
				break;

			c &= 0xf;

			if ((i & 1) == 0)
				c <<= 4;
			sc->sc_ue.ue_eaddr[i / 2] |= c;
		}

		if (uaa->usb_mode == USB_MODE_DEVICE) {
			/*
			 * Do not use the same MAC address like the peer !
			 */
			sc->sc_ue.ue_eaddr[5] ^= 0xFF;
		}
	}

	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &cdce_ue_methods;

	error = uether_ifattach(ue);
	if (error) {
		device_printf(dev, "could not attach interface\n");
		goto detach;
	}
	return (0);			/* success */

detach:
	cdce_detach(dev);
	return (ENXIO);			/* failure */
}
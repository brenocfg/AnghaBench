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
typedef  int uint32_t ;
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; int /*<<< orphan*/  bInterfaceNumber; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; } ;
struct usb_interface {int dummy; } ;
struct usb_config {int ep_index; } ;
struct TYPE_2__ {int bIfaceIndex; int /*<<< orphan*/  idVendor; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct u3g_softc {int sc_numports; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_ucom; scalar_t__** sc_xfer; int /*<<< orphan*/ * sc_iface; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int U3GINIT_SAEL_M460 ; 
 size_t U3G_BULK_RD ; 
 size_t U3G_BULK_WR ; 
 size_t U3G_INTR ; 
 int U3G_MAXPORTS ; 
 int U3G_N_TRANSFER ; 
 scalar_t__ UICLASS_VENDOR ; 
 int /*<<< orphan*/  UQ_MSC_EJECT_SAEL_M460 ; 
 int USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 int USB_IFACE_MAX ; 
 scalar_t__ bootverbose ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct u3g_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u3g_callback ; 
 struct usb_config* u3g_config ; 
 int /*<<< orphan*/  u3g_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ u3g_huawei_is_cdce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u3g_sael_m460_init (int /*<<< orphan*/ ) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct u3g_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_test_quirk (struct usb_attach_arg*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usbd_get_iface (int /*<<< orphan*/ ,int) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (struct usb_interface*) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,int,int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int*,scalar_t__*,struct usb_config*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (scalar_t__) ; 

__attribute__((used)) static int
u3g_attach(device_t dev)
{
	struct usb_config u3g_config_tmp[U3G_N_TRANSFER];
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct u3g_softc *sc = device_get_softc(dev);
	struct usb_interface *iface;
	struct usb_interface_descriptor *id;
	uint32_t iface_valid;
	int error, type, nports;
	int ep, n;
	uint8_t i;

	DPRINTF("sc=%p\n", sc);

	type = USB_GET_DRIVER_INFO(uaa);
	if (type == U3GINIT_SAEL_M460
	    || usb_test_quirk(uaa, UQ_MSC_EJECT_SAEL_M460)) {
		u3g_sael_m460_init(uaa->device);
	}

	/* copy in USB config */
	for (n = 0; n != U3G_N_TRANSFER; n++)
		u3g_config_tmp[n] = u3g_config[n];

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "u3g", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_udev = uaa->device;

	/* Claim all interfaces on the device */
	iface_valid = 0;
	for (i = uaa->info.bIfaceIndex; i < USB_IFACE_MAX; i++) {
		iface = usbd_get_iface(uaa->device, i);
		if (iface == NULL)
			break;
		id = usbd_get_interface_descriptor(iface);
		if (id == NULL || id->bInterfaceClass != UICLASS_VENDOR)
			continue;
		if (u3g_huawei_is_cdce(uaa->info.idVendor,
		    id->bInterfaceSubClass, id->bInterfaceProtocol))
			continue;
		usbd_set_parent_iface(uaa->device, i, uaa->info.bIfaceIndex);
		iface_valid |= (1<<i);
	}

	i = 0;		/* interface index */
	ep = 0;		/* endpoint index */
	nports = 0;	/* number of ports */
	while (i < USB_IFACE_MAX) {
		if ((iface_valid & (1<<i)) == 0) {
			i++;
			continue;
		}

		/* update BULK endpoint index */
		for (n = 0; n < U3G_N_TRANSFER; n++)
			u3g_config_tmp[n].ep_index = ep;

		/* try to allocate a set of BULK endpoints */
		error = usbd_transfer_setup(uaa->device, &i,
		    sc->sc_xfer[nports], u3g_config_tmp, U3G_N_TRANSFER,
		    &sc->sc_ucom[nports], &sc->sc_mtx);
		if (error) {
			/* next interface */
			i++;
			ep = 0;
			continue;
		}

		iface = usbd_get_iface(uaa->device, i);
		id = usbd_get_interface_descriptor(iface);
		sc->sc_iface[nports] = id->bInterfaceNumber;

		if (bootverbose && sc->sc_xfer[nports][U3G_INTR]) {
			device_printf(dev, "port %d supports modem control\n",
				      nports);
		}

		/* set stall by default */
		mtx_lock(&sc->sc_mtx);
		usbd_xfer_set_stall(sc->sc_xfer[nports][U3G_BULK_WR]);
		usbd_xfer_set_stall(sc->sc_xfer[nports][U3G_BULK_RD]);
		mtx_unlock(&sc->sc_mtx);

		nports++;	/* found one port */
		ep++;
		if (nports == U3G_MAXPORTS)
			break;
	}
	if (nports == 0) {
		device_printf(dev, "no ports found\n");
		goto detach;
	}
	sc->sc_numports = nports;

	error = ucom_attach(&sc->sc_super_ucom, sc->sc_ucom,
	    sc->sc_numports, sc, &u3g_callback, &sc->sc_mtx);
	if (error) {
		DPRINTF("ucom_attach failed\n");
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);
	device_printf(dev, "Found %u port%s.\n", sc->sc_numports,
	    sc->sc_numports > 1 ? "s":"");

	return (0);

detach:
	u3g_detach(dev);
	return (ENXIO);
}
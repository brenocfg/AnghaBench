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
typedef  scalar_t__ usb_error_t ;
struct usb_interface_descriptor {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_3__ {int /*<<< orphan*/  bIfaceNum; int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; int /*<<< orphan*/  iface; } ;
struct uhso_tty {size_t ht_muxport; char* ht_name; } ;
struct uhso_softc {int sc_radio; int sc_ttys; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_type; struct ucom_softc* sc_ucom; struct uhso_tty* sc_tty; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ctrl_xfer; int /*<<< orphan*/  sc_iface_index; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_ctrl_iface_no; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_rxq; int /*<<< orphan*/  sc_udev; } ;
struct ucom_softc {int sc_subunit; TYPE_2__* sc_super; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int sc_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct uhso_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 scalar_t__ UHSO_AUTO_IFACE ; 
 int /*<<< orphan*/  UHSO_CTRL_MAX ; 
 size_t UHSO_IFACE_PORT (int /*<<< orphan*/ ) ; 
 size_t UHSO_IFACE_PORT_TYPE (int /*<<< orphan*/ ) ; 
 int UHSO_IFACE_USB_TYPE (int /*<<< orphan*/ ) ; 
 int UHSO_IF_MUX ; 
 scalar_t__ UHSO_STATIC_IFACE ; 
 scalar_t__ USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 scalar_t__ bootverbose ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct uhso_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhso_ctrl_config ; 
 int /*<<< orphan*/  uhso_detach (int /*<<< orphan*/ ) ; 
 int* uhso_mux_port_map ; 
 char** uhso_port ; 
 char** uhso_port_type ; 
 char** uhso_port_type_sysctl ; 
 int uhso_probe_iface (struct uhso_softc*,int /*<<< orphan*/ ,void*) ; 
 void* uhso_probe_iface_auto ; 
 void* uhso_probe_iface_static ; 
 int /*<<< orphan*/  uhso_radio_sysctl ; 
 int /*<<< orphan*/  usb_get_manufacturer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_product (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uhso_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uhso_attach(device_t self)
{
	struct uhso_softc *sc = device_get_softc(self);
	struct usb_attach_arg *uaa = device_get_ivars(self);
	struct usb_interface_descriptor *id;
	struct sysctl_ctx_list *sctx;
	struct sysctl_oid *soid;
	struct sysctl_oid *tree = NULL, *tty_node;
	struct ucom_softc *ucom;
	struct uhso_tty *ht;
	int i, error, port;
	void *probe_f;
	usb_error_t uerr;
	char *desc;

	sc->sc_dev = self;
	sc->sc_udev = uaa->device;
	mtx_init(&sc->sc_mtx, "uhso", NULL, MTX_DEF);
	mbufq_init(&sc->sc_rxq, INT_MAX);	/* XXXGL: sane maximum */
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_radio = 1;

	id = usbd_get_interface_descriptor(uaa->iface);
	sc->sc_ctrl_iface_no = id->bInterfaceNumber;

	sc->sc_iface_no = uaa->info.bIfaceNum;
	sc->sc_iface_index = uaa->info.bIfaceIndex;

	/* Setup control pipe */
	uerr = usbd_transfer_setup(uaa->device,
	    &sc->sc_iface_index, sc->sc_ctrl_xfer,
	    uhso_ctrl_config, UHSO_CTRL_MAX, sc, &sc->sc_mtx);
	if (uerr) {
		device_printf(self, "Failed to setup control pipe: %s\n",
		    usbd_errstr(uerr));
		goto out;
	}

	if (USB_GET_DRIVER_INFO(uaa) == UHSO_STATIC_IFACE)
		probe_f = uhso_probe_iface_static;
	else if (USB_GET_DRIVER_INFO(uaa) == UHSO_AUTO_IFACE)
		probe_f = uhso_probe_iface_auto;
	else
		goto out;

	error = uhso_probe_iface(sc, uaa->info.bIfaceNum, probe_f);
	if (error != 0)
		goto out;

	sctx = device_get_sysctl_ctx(sc->sc_dev);
	soid = device_get_sysctl_tree(sc->sc_dev);

	SYSCTL_ADD_STRING(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "type",
	    CTLFLAG_RD, uhso_port[UHSO_IFACE_PORT(sc->sc_type)], 0,
	    "Port available at this interface");
	SYSCTL_ADD_PROC(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "radio",
	    CTLTYPE_INT | CTLFLAG_RWTUN, sc, 0, uhso_radio_sysctl, "I", "Enable radio");

	/*
	 * The default interface description on most Option devices isn't
	 * very helpful. So we skip device_set_usb_desc and set the
	 * device description manually.
	 */
	device_set_desc_copy(self, uhso_port_type[UHSO_IFACE_PORT_TYPE(sc->sc_type)]); 
	/* Announce device */
	device_printf(self, "<%s port> at <%s %s> on %s\n",
	    uhso_port_type[UHSO_IFACE_PORT_TYPE(sc->sc_type)],
	    usb_get_manufacturer(uaa->device),
	    usb_get_product(uaa->device),
	    device_get_nameunit(device_get_parent(self)));

	if (sc->sc_ttys > 0) {
		SYSCTL_ADD_INT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "ports",
		    CTLFLAG_RD, &sc->sc_ttys, 0, "Number of attached serial ports");

		tree = SYSCTL_ADD_NODE(sctx, SYSCTL_CHILDREN(soid), OID_AUTO,
		    "port", CTLFLAG_RD, NULL, "Serial ports");
	}

	/*
	 * Loop through the number of found TTYs and create sysctl
	 * nodes for them.
	 */
	for (i = 0; i < sc->sc_ttys; i++) {
		ht = &sc->sc_tty[i];
		ucom = &sc->sc_ucom[i];

		if (UHSO_IFACE_USB_TYPE(sc->sc_type) & UHSO_IF_MUX)
			port = uhso_mux_port_map[ht->ht_muxport];
		else
			port = UHSO_IFACE_PORT_TYPE(sc->sc_type);

		desc = uhso_port_type_sysctl[port];

		tty_node = SYSCTL_ADD_NODE(sctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    desc, CTLFLAG_RD, NULL, "");

		ht->ht_name[0] = 0;
		if (sc->sc_ttys == 1)
			snprintf(ht->ht_name, 32, "cuaU%d", ucom->sc_super->sc_unit);
		else {
			snprintf(ht->ht_name, 32, "cuaU%d.%d",
			    ucom->sc_super->sc_unit, ucom->sc_subunit);
		}

		desc = uhso_port_type[port];
		SYSCTL_ADD_STRING(sctx, SYSCTL_CHILDREN(tty_node), OID_AUTO,
		    "tty", CTLFLAG_RD, ht->ht_name, 0, "");
		SYSCTL_ADD_STRING(sctx, SYSCTL_CHILDREN(tty_node), OID_AUTO,
		    "desc", CTLFLAG_RD, desc, 0, "");

		if (bootverbose)
			device_printf(sc->sc_dev,
			    "\"%s\" port at %s\n", desc, ht->ht_name);
	}

	return (0);
out:
	uhso_detach(sc->sc_dev);
	return (ENXIO);
}
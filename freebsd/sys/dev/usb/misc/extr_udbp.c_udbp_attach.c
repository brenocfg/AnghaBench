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
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct udbp_softc {char* sc_name; int /*<<< orphan*/ * sc_node; int /*<<< orphan*/  sc_xmitq_hipri; int /*<<< orphan*/  sc_xmitq; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ *,struct udbp_softc*) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UDBP_Q_MAXLEN ; 
 int /*<<< orphan*/  UDBP_T_MAX ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct udbp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ng_make_node_common (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ng_udbp_typestruct ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  udbp_config ; 
 int /*<<< orphan*/  udbp_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udbp_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udbp_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct udbp_softc *sc = device_get_softc(dev);
	int error;

	device_set_usb_desc(dev);

	snprintf(sc->sc_name, sizeof(sc->sc_name),
	    "%s", device_get_nameunit(dev));

	mtx_init(&sc->sc_mtx, "udbp lock", NULL, MTX_DEF | MTX_RECURSE);

	error = usbd_transfer_setup(uaa->device, &uaa->info.bIfaceIndex,
	    sc->sc_xfer, udbp_config, UDBP_T_MAX, sc, &sc->sc_mtx);
	if (error) {
		DPRINTF("error=%s\n", usbd_errstr(error));
		goto detach;
	}
	NG_BT_MBUFQ_INIT(&sc->sc_xmitq, UDBP_Q_MAXLEN);

	NG_BT_MBUFQ_INIT(&sc->sc_xmitq_hipri, UDBP_Q_MAXLEN);

	/* create Netgraph node */

	if (ng_make_node_common(&ng_udbp_typestruct, &sc->sc_node) != 0) {
		printf("%s: Could not create Netgraph node\n",
		    sc->sc_name);
		sc->sc_node = NULL;
		goto detach;
	}
	/* name node */

	if (ng_name_node(sc->sc_node, sc->sc_name) != 0) {
		printf("%s: Could not name node\n",
		    sc->sc_name);
		NG_NODE_UNREF(sc->sc_node);
		sc->sc_node = NULL;
		goto detach;
	}
	NG_NODE_SET_PRIVATE(sc->sc_node, sc);

	/* the device is now operational */

	return (0);			/* success */

detach:
	udbp_detach(dev);
	return (ENOMEM);		/* failure */
}
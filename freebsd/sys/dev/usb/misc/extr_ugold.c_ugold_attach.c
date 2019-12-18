#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int bIfaceIndex; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_3__ info; } ;
struct ugold_softc {int* sc_iface_index; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/ * sc_valid; int /*<<< orphan*/ * sc_calib; int /*<<< orphan*/ * sc_sensor; int /*<<< orphan*/  sc_report_id; int /*<<< orphan*/  sc_callout; TYPE_2__* sc_readout_msg; int /*<<< orphan*/  sc_udev; } ;
struct sysctl_oid {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pm_callback; } ;
struct TYPE_5__ {struct ugold_softc* sc; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 size_t UGOLD_INNER ; 
 size_t UGOLD_INTR_DT ; 
 int /*<<< orphan*/  UGOLD_N_TRANSFER ; 
 size_t UGOLD_OUTER ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ugold_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_input ; 
 int /*<<< orphan*/  hid_report_size (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ugold_config ; 
 int /*<<< orphan*/  ugold_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ugold_readout_msg ; 
 int /*<<< orphan*/  ugold_timeout (struct ugold_softc*) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int /*<<< orphan*/ * usbd_get_iface (int /*<<< orphan*/ ,int) ; 
 int usbd_req_get_hid_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,int,int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ugold_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ugold_attach(device_t dev)
{
	struct ugold_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct sysctl_oid *sensor_tree;
	uint16_t d_len;
	void *d_ptr;
	int error;
	int i;

	sc->sc_udev = uaa->device;
	sc->sc_readout_msg[0].hdr.pm_callback = &ugold_readout_msg;
	sc->sc_readout_msg[0].sc = sc;
	sc->sc_readout_msg[1].hdr.pm_callback = &ugold_readout_msg;
	sc->sc_readout_msg[1].sc = sc;
	sc->sc_iface_index[0] = uaa->info.bIfaceIndex;
	sc->sc_iface_index[1] = uaa->info.bIfaceIndex + 1;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "ugold lock", NULL, MTX_DEF | MTX_RECURSE);
	callout_init_mtx(&sc->sc_callout, &sc->sc_mtx, 0);

	/* grab all interfaces from other drivers */
	for (i = 0;; i++) {
		if (i == uaa->info.bIfaceIndex)
			continue;
		if (usbd_get_iface(uaa->device, i) == NULL)
			break;

		usbd_set_parent_iface(uaa->device, i, uaa->info.bIfaceIndex);
	}

	/* figure out report ID */
	error = usbd_req_get_hid_desc(uaa->device, NULL,
	    &d_ptr, &d_len, M_TEMP, uaa->info.bIfaceIndex);

	if (error)
		goto detach;

	(void)hid_report_size(d_ptr, d_len, hid_input, &sc->sc_report_id);

	free(d_ptr, M_TEMP);

	error = usbd_transfer_setup(uaa->device,
	    sc->sc_iface_index, sc->sc_xfer, ugold_config,
	    UGOLD_N_TRANSFER, sc, &sc->sc_mtx);
	if (error)
		goto detach;

	sensor_tree = SYSCTL_ADD_NODE(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO, "sensors",
	    CTLFLAG_RD, NULL, "");

	if (sensor_tree == NULL) {
		error = ENOMEM;
		goto detach;
	}
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(sensor_tree),
	    OID_AUTO, "inner", CTLFLAG_RD, &sc->sc_sensor[UGOLD_INNER], 0,
	    "Inner temperature in microCelcius");

	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(sensor_tree),
	    OID_AUTO, "inner_valid", CTLFLAG_RD, &sc->sc_valid[UGOLD_INNER], 0,
	    "Inner temperature is valid");

	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(sensor_tree),
	    OID_AUTO, "inner_calib", CTLFLAG_RWTUN, &sc->sc_calib[UGOLD_INNER], 0,
	    "Inner calibration temperature in microCelcius");
	
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(sensor_tree),
	    OID_AUTO, "outer", CTLFLAG_RD, &sc->sc_sensor[UGOLD_OUTER], 0,
	    "Outer temperature in microCelcius");

	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(sensor_tree),
	    OID_AUTO, "outer_calib", CTLFLAG_RWTUN, &sc->sc_calib[UGOLD_OUTER], 0,
	    "Outer calibration temperature in microCelcius");

	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(sensor_tree),
	    OID_AUTO, "outer_valid", CTLFLAG_RD, &sc->sc_valid[UGOLD_OUTER], 0,
	    "Outer temperature is valid");

	mtx_lock(&sc->sc_mtx);
	usbd_transfer_start(sc->sc_xfer[UGOLD_INTR_DT]);
	ugold_timeout(sc);
	mtx_unlock(&sc->sc_mtx);

	return (0);

detach:
	DPRINTF("error=%s\n", usbd_errstr(error));
	ugold_detach(dev);
	return (error);
}
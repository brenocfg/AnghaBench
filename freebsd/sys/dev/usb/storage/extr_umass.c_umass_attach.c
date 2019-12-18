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
typedef  size_t uint8_t ;
struct usb_interface_descriptor {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; int /*<<< orphan*/  iface; } ;
struct TYPE_6__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
struct umass_softc {int sc_proto; int sc_quirks; TYPE_3__ cam_scsi_test_unit_ready; TYPE_2__ cam_scsi_sense; scalar_t__ sc_maxlun; int /*<<< orphan*/ * sc_transform; int /*<<< orphan*/ ** sc_xfer; int /*<<< orphan*/  sc_last_xfer_index; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_unit; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_dev; } ;
struct umass_probe_proto {int proto; int quirks; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALT_IFACE_1 ; 
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*) ; 
 int ENXIO ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int NO_GETMAXLUN ; 
 int /*<<< orphan*/  REQUEST_SENSE ; 
 int SHUTTLE_INIT ; 
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 int /*<<< orphan*/  UDMASS_GEN ; 
 int /*<<< orphan*/  UDMASS_USB ; 
#define  UMASS_PROTO_ATAPI 134 
#define  UMASS_PROTO_BBB 133 
#define  UMASS_PROTO_CBI 132 
#define  UMASS_PROTO_CBI_I 131 
 int UMASS_PROTO_COMMAND ; 
#define  UMASS_PROTO_RBC 130 
#define  UMASS_PROTO_SCSI 129 
#define  UMASS_PROTO_UFI 128 
 int UMASS_PROTO_WIRE ; 
 int /*<<< orphan*/  UMASS_T_BBB_COMMAND ; 
 int /*<<< orphan*/  UMASS_T_BBB_MAX ; 
 int /*<<< orphan*/  UMASS_T_CBI_COMMAND ; 
 int /*<<< orphan*/  UMASS_T_CBI_MAX ; 
 size_t UMASS_T_MAX ; 
 int USB_ERR_INVAL ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct umass_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  umass_atapi_transform ; 
 int /*<<< orphan*/  umass_bbb_config ; 
 scalar_t__ umass_bbb_get_max_lun (struct umass_softc*) ; 
 int /*<<< orphan*/  umass_cam_attach (struct umass_softc*) ; 
 int umass_cam_attach_sim (struct umass_softc*) ; 
 int /*<<< orphan*/  umass_cbi_config ; 
 int /*<<< orphan*/  umass_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_init_shuttle (struct umass_softc*) ; 
 int /*<<< orphan*/  umass_no_transform ; 
 struct umass_probe_proto umass_probe_proto (int /*<<< orphan*/ ,struct usb_attach_arg*) ; 
 int /*<<< orphan*/  umass_rbc_transform ; 
 int /*<<< orphan*/  umass_scsi_transform ; 
 int umass_throttle ; 
 int /*<<< orphan*/  umass_ufi_transform ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (int /*<<< orphan*/ ) ; 
 int usbd_set_alt_interface_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umass_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_interval (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
umass_attach(device_t dev)
{
	struct umass_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct umass_probe_proto temp = umass_probe_proto(dev, uaa);
	struct usb_interface_descriptor *id;
	int err;

	/*
	 * NOTE: the softc struct is cleared in device_set_driver.
	 * We can safely call umass_detach without specifically
	 * initializing the struct.
	 */

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;
	sc->sc_proto = temp.proto;
	sc->sc_quirks = temp.quirks;
	sc->sc_unit = device_get_unit(dev);

	snprintf(sc->sc_name, sizeof(sc->sc_name),
	    "%s", device_get_nameunit(dev));

	device_set_usb_desc(dev);

        mtx_init(&sc->sc_mtx, device_get_nameunit(dev), 
	    NULL, MTX_DEF | MTX_RECURSE);

	/* get interface index */

	id = usbd_get_interface_descriptor(uaa->iface);
	if (id == NULL) {
		device_printf(dev, "failed to get "
		    "interface number\n");
		goto detach;
	}
	sc->sc_iface_no = id->bInterfaceNumber;

#ifdef USB_DEBUG
	device_printf(dev, " ");

	switch (sc->sc_proto & UMASS_PROTO_COMMAND) {
	case UMASS_PROTO_SCSI:
		printf("SCSI");
		break;
	case UMASS_PROTO_ATAPI:
		printf("8070i (ATAPI)");
		break;
	case UMASS_PROTO_UFI:
		printf("UFI");
		break;
	case UMASS_PROTO_RBC:
		printf("RBC");
		break;
	default:
		printf("(unknown 0x%02x)",
		    sc->sc_proto & UMASS_PROTO_COMMAND);
		break;
	}

	printf(" over ");

	switch (sc->sc_proto & UMASS_PROTO_WIRE) {
	case UMASS_PROTO_BBB:
		printf("Bulk-Only");
		break;
	case UMASS_PROTO_CBI:		/* uses Comand/Bulk pipes */
		printf("CBI");
		break;
	case UMASS_PROTO_CBI_I:	/* uses Comand/Bulk/Interrupt pipes */
		printf("CBI with CCI");
		break;
	default:
		printf("(unknown 0x%02x)",
		    sc->sc_proto & UMASS_PROTO_WIRE);
	}

	printf("; quirks = 0x%04x\n", sc->sc_quirks);
#endif

	if (sc->sc_quirks & ALT_IFACE_1) {
		err = usbd_set_alt_interface_index
		    (uaa->device, uaa->info.bIfaceIndex, 1);

		if (err) {
			DPRINTF(sc, UDMASS_USB, "could not switch to "
			    "Alt Interface 1\n");
			goto detach;
		}
	}
	/* allocate all required USB transfers */

	if (sc->sc_proto & UMASS_PROTO_BBB) {

		err = usbd_transfer_setup(uaa->device,
		    &uaa->info.bIfaceIndex, sc->sc_xfer, umass_bbb_config,
		    UMASS_T_BBB_MAX, sc, &sc->sc_mtx);

		/* skip reset first time */
		sc->sc_last_xfer_index = UMASS_T_BBB_COMMAND;

	} else if (sc->sc_proto & (UMASS_PROTO_CBI | UMASS_PROTO_CBI_I)) {

		err = usbd_transfer_setup(uaa->device,
		    &uaa->info.bIfaceIndex, sc->sc_xfer, umass_cbi_config,
		    UMASS_T_CBI_MAX, sc, &sc->sc_mtx);

		/* skip reset first time */
		sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

	} else {
		err = USB_ERR_INVAL;
	}

	if (err) {
		device_printf(dev, "could not setup required "
		    "transfers, %s\n", usbd_errstr(err));
		goto detach;
	}
#ifdef USB_DEBUG
	if (umass_throttle > 0) {
		uint8_t x;
		int iv;

		iv = umass_throttle;

		if (iv < 1)
			iv = 1;
		else if (iv > 8000)
			iv = 8000;

		for (x = 0; x != UMASS_T_MAX; x++) {
			if (sc->sc_xfer[x] != NULL)
				usbd_xfer_set_interval(sc->sc_xfer[x], iv);
		}
	}
#endif
	sc->sc_transform =
	    (sc->sc_proto & UMASS_PROTO_SCSI) ? &umass_scsi_transform :
	    (sc->sc_proto & UMASS_PROTO_UFI) ? &umass_ufi_transform :
	    (sc->sc_proto & UMASS_PROTO_ATAPI) ? &umass_atapi_transform :
	    (sc->sc_proto & UMASS_PROTO_RBC) ? &umass_rbc_transform :
	    &umass_no_transform;

	/* from here onwards the device can be used. */

	if (sc->sc_quirks & SHUTTLE_INIT) {
		umass_init_shuttle(sc);
	}
	/* get the maximum LUN supported by the device */

	if (((sc->sc_proto & UMASS_PROTO_WIRE) == UMASS_PROTO_BBB) &&
	    !(sc->sc_quirks & NO_GETMAXLUN))
		sc->sc_maxlun = umass_bbb_get_max_lun(sc);
	else
		sc->sc_maxlun = 0;

	/* Prepare the SCSI command block */
	sc->cam_scsi_sense.opcode = REQUEST_SENSE;
	sc->cam_scsi_test_unit_ready.opcode = TEST_UNIT_READY;

	/* register the SIM */
	err = umass_cam_attach_sim(sc);
	if (err) {
		goto detach;
	}
	/* scan the SIM */
	umass_cam_attach(sc);

	DPRINTF(sc, UDMASS_GEN, "Attach finished\n");

	return (0);			/* success */

detach:
	umass_detach(dev);
	return (ENXIO);			/* failure */
}
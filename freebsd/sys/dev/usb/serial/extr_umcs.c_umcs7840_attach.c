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
typedef  int uint8_t ;
struct usb_config {int /*<<< orphan*/  callback; scalar_t__ endpoint; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct umcs7840_softc {int sc_numports; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; TYPE_3__* sc_ucom; TYPE_2__* sc_ports; int /*<<< orphan*/  sc_intr_xfer; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int sc_portno; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int ENXIO ; 
 int MCS7840_DEV_GPIO_4PORTS ; 
 int MCS7840_DEV_MODE_EEPROMWR ; 
 int MCS7840_DEV_MODE_IRDA ; 
 int MCS7840_DEV_MODE_PLLBYPASS ; 
 int MCS7840_DEV_MODE_PORBYPASS ; 
 int MCS7840_DEV_MODE_RESET ; 
 int MCS7840_DEV_MODE_SELECT24S ; 
 int MCS7840_DEV_MODE_SER_PRSNT ; 
 int /*<<< orphan*/  MCS7840_DEV_REG_GPIO ; 
 int /*<<< orphan*/  MCS7840_DEV_REG_MODE ; 
 int MCS7840_IFACE_INDEX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t UMCS7840_BULK_RD_EP ; 
 size_t UMCS7840_BULK_WR_EP ; 
 int UMCS7840_N_TRANSFERS ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct umcs7840_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,TYPE_3__*,int,struct umcs7840_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_config* umcs7840_bulk_config_data ; 
 int /*<<< orphan*/  umcs7840_callback ; 
 int /*<<< orphan*/  umcs7840_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umcs7840_get_reg_sync (struct umcs7840_softc*,int /*<<< orphan*/ ,int*) ; 
 struct usb_config* umcs7840_intr_config_data ; 
 int /*<<< orphan*/ ** umcs7840_rw_callbacks ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,struct usb_config*,int,struct umcs7840_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umcs7840_attach(device_t dev)
{
	struct usb_config umcs7840_config_tmp[UMCS7840_N_TRANSFERS];
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct umcs7840_softc *sc = device_get_softc(dev);

	uint8_t iface_index = MCS7840_IFACE_INDEX;
	int error;
	int subunit;
	int n;
	uint8_t data;

	for (n = 0; n < UMCS7840_N_TRANSFERS; ++n)
		umcs7840_config_tmp[n] = umcs7840_bulk_config_data[n];

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "umcs7840", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;

	/*
	 * Get number of ports
	 * Documentation (full datasheet) says, that number of ports is
	 * set as MCS7840_DEV_MODE_SELECT24S bit in MODE R/Only
	 * register. But vendor driver uses these undocumented
	 * register & bit.
	 *
	 * Experiments show, that MODE register can have `0'
	 * (4 ports) bit on 2-port device, so use vendor driver's way.
	 *
	 * Also, see notes in header file for these constants.
	 */
	umcs7840_get_reg_sync(sc, MCS7840_DEV_REG_GPIO, &data);
	if (data & MCS7840_DEV_GPIO_4PORTS) {
		sc->sc_numports = 4;
		/* Store physical port numbers in sc_portno */
		sc->sc_ucom[0].sc_portno = 0;
		sc->sc_ucom[1].sc_portno = 1;
		sc->sc_ucom[2].sc_portno = 2;
		sc->sc_ucom[3].sc_portno = 3;
	} else {
		sc->sc_numports = 2;
		/* Store physical port numbers in sc_portno */
		sc->sc_ucom[0].sc_portno = 0;
		sc->sc_ucom[1].sc_portno = 2;	/* '1' is skipped */
	}
	device_printf(dev, "Chip mcs%04x, found %d active ports\n", uaa->info.idProduct, sc->sc_numports);
	if (!umcs7840_get_reg_sync(sc, MCS7840_DEV_REG_MODE, &data)) {
		device_printf(dev, "On-die confguration: RST: active %s, HRD: %s, PLL: %s, POR: %s, Ports: %s, EEPROM write %s, IrDA is %savailable\n",
		    (data & MCS7840_DEV_MODE_RESET) ? "low" : "high",
		    (data & MCS7840_DEV_MODE_SER_PRSNT) ? "yes" : "no",
		    (data & MCS7840_DEV_MODE_PLLBYPASS) ? "bypassed" : "avail",
		    (data & MCS7840_DEV_MODE_PORBYPASS) ? "bypassed" : "avail",
		    (data & MCS7840_DEV_MODE_SELECT24S) ? "2" : "4",
		    (data & MCS7840_DEV_MODE_EEPROMWR) ? "enabled" : "disabled",
		    (data & MCS7840_DEV_MODE_IRDA) ? "" : "not ");
	}
	/* Setup all transfers */
	for (subunit = 0; subunit < sc->sc_numports; ++subunit) {
		for (n = 0; n < UMCS7840_N_TRANSFERS; ++n) {
			/* Set endpoint address */
			umcs7840_config_tmp[n].endpoint = umcs7840_bulk_config_data[n].endpoint + 2 * sc->sc_ucom[subunit].sc_portno;
			umcs7840_config_tmp[n].callback = umcs7840_rw_callbacks[subunit][n];
		}
		error = usbd_transfer_setup(uaa->device,
		    &iface_index, sc->sc_ports[sc->sc_ucom[subunit].sc_portno].sc_xfer, umcs7840_config_tmp,
		    UMCS7840_N_TRANSFERS, sc, &sc->sc_mtx);
		if (error) {
			device_printf(dev, "allocating USB transfers failed for subunit %d of %d\n",
			    subunit + 1, sc->sc_numports);
			goto detach;
		}
	}
	error = usbd_transfer_setup(uaa->device,
	    &iface_index, &sc->sc_intr_xfer, umcs7840_intr_config_data,
	    1, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "allocating USB transfers failed for interrupt\n");
		goto detach;
	}
	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	for (subunit = 0; subunit < sc->sc_numports; ++subunit) {
		usbd_xfer_set_stall(sc->sc_ports[sc->sc_ucom[subunit].sc_portno].sc_xfer[UMCS7840_BULK_RD_EP]);
		usbd_xfer_set_stall(sc->sc_ports[sc->sc_ucom[subunit].sc_portno].sc_xfer[UMCS7840_BULK_WR_EP]);
	}
	mtx_unlock(&sc->sc_mtx);

	error = ucom_attach(&sc->sc_super_ucom, sc->sc_ucom, sc->sc_numports, sc,
	    &umcs7840_callback, &sc->sc_mtx);
	if (error)
		goto detach;

	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	umcs7840_detach(dev);
	return (ENXIO);
}
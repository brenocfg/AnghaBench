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
typedef  scalar_t__ uint8_t ;
struct usb_ether {int* ue_eaddr; int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct cdceem_softc* ue_sc; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct cdceem_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDCEEM_N_TRANSFER ; 
 int /*<<< orphan*/  CDCEEM_WARN (struct cdceem_softc*,char*,int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  arc4rand (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdceem_config ; 
 int /*<<< orphan*/  cdceem_ue_methods ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct cdceem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uether_ifattach (struct usb_ether*) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cdceem_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdceem_attach(device_t dev)
{
	struct cdceem_softc *sc;
	struct usb_ether *ue;
	struct usb_attach_arg *uaa;
	int error;
	uint8_t iface_index;

	sc = device_get_softc(dev);
	ue = &sc->sc_ue;
	uaa = device_get_ivars(dev);

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	/* Setup the endpoints. */
	iface_index = 0;
	error = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
	    cdceem_config, CDCEEM_N_TRANSFER, sc, &sc->sc_mtx);
	if (error != 0) {
		CDCEEM_WARN(sc,
		    "allocating USB transfers failed, error %d", error);
		mtx_destroy(&sc->sc_mtx);
		return (error);
	}

	/* Random MAC address. */
	arc4rand(ue->ue_eaddr, ETHER_ADDR_LEN, 0);
	ue->ue_eaddr[0] &= ~0x01;	/* unicast */
	ue->ue_eaddr[0] |= 0x02;	/* locally administered */

	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &cdceem_ue_methods;

	error = uether_ifattach(ue);
	if (error != 0) {
		CDCEEM_WARN(sc, "could not attach interface, error %d", error);
		usbd_transfer_unsetup(sc->sc_xfer, CDCEEM_N_TRANSFER);
		mtx_destroy(&sc->sc_mtx);
		return (error);
	}

	return (0);
}
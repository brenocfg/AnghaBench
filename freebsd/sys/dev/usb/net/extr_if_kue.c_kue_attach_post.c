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
struct usb_ether {int /*<<< orphan*/  ue_eaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  kue_macaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ue_dev; } ;
struct kue_softc {TYPE_2__ sc_desc; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  KUE_CMD_GET_ETHER_DESCRIPTOR ; 
 int /*<<< orphan*/  KUE_CTL_READ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kue_ctl (struct kue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int kue_load_fw (struct kue_softc*) ; 
 int /*<<< orphan*/  kue_reset (struct kue_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct kue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
kue_attach_post(struct usb_ether *ue)
{
	struct kue_softc *sc = uether_getsc(ue);
	int error;

	/* load the firmware into the NIC */
	error = kue_load_fw(sc);
	if (error) {
		device_printf(sc->sc_ue.ue_dev, "could not load firmware\n");
		/* ignore the error */
	}

	/* reset the adapter */
	kue_reset(sc);

	/* read ethernet descriptor */
	kue_ctl(sc, KUE_CTL_READ, KUE_CMD_GET_ETHER_DESCRIPTOR,
	    0, &sc->sc_desc, sizeof(sc->sc_desc));

	/* copy in ethernet address */
	memcpy(ue->ue_eaddr, sc->sc_desc.kue_macaddr, sizeof(ue->ue_eaddr));
}
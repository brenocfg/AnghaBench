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
struct usb_ether {int /*<<< orphan*/  ue_eaddr; } ;
struct TYPE_2__ {int* ue_eaddr; int /*<<< orphan*/  ue_dev; } ;
struct ure_softc {int sc_flags; int sc_chip; TYPE_1__ sc_ue; scalar_t__ sc_phyno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_IS_ZERO (int*) ; 
 int URE_CHIP_VER_4C00 ; 
 int URE_CHIP_VER_4C10 ; 
 int URE_FLAG_8152 ; 
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 int /*<<< orphan*/  URE_PLA_BACKUP ; 
 int /*<<< orphan*/  URE_PLA_IDR ; 
 int /*<<< orphan*/  arc4rand (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ure_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  ure_read_chipver (struct ure_softc*) ; 
 int /*<<< orphan*/  ure_read_mem (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ure_rtl8152_init (struct ure_softc*) ; 
 int /*<<< orphan*/  ure_rtl8153_init (struct ure_softc*) ; 

__attribute__((used)) static void
ure_attach_post(struct usb_ether *ue)
{
	struct ure_softc *sc = uether_getsc(ue);

	sc->sc_phyno = 0;

	/* Determine the chip version. */
	ure_read_chipver(sc);

	/* Initialize controller and get station address. */
	if (sc->sc_flags & URE_FLAG_8152)
		ure_rtl8152_init(sc);
	else
		ure_rtl8153_init(sc);

	if ((sc->sc_chip & URE_CHIP_VER_4C00) ||
	    (sc->sc_chip & URE_CHIP_VER_4C10))
		ure_read_mem(sc, URE_PLA_IDR, URE_MCU_TYPE_PLA,
		    ue->ue_eaddr, 8);
	else
		ure_read_mem(sc, URE_PLA_BACKUP, URE_MCU_TYPE_PLA,
		    ue->ue_eaddr, 8);

	if (ETHER_IS_ZERO(sc->sc_ue.ue_eaddr)) {
		device_printf(sc->sc_ue.ue_dev, "MAC assigned randomly\n");
		arc4rand(sc->sc_ue.ue_eaddr, ETHER_ADDR_LEN, 0);
		sc->sc_ue.ue_eaddr[0] &= ~0x01; /* unicast */
		sc->sc_ue.ue_eaddr[0] |= 0x02;  /* locally administered */
	}
}
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
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; } ;
struct aue_softc {int sc_flags; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_CTL1 ; 
 int AUE_CTL1_RESETMAC ; 
 int AUE_FLAG_LSYS ; 
 int AUE_FLAG_PII ; 
 int /*<<< orphan*/  AUE_GPIO0 ; 
 int AUE_GPIO_OUT0 ; 
 int AUE_GPIO_SEL0 ; 
 int AUE_GPIO_SEL1 ; 
 int /*<<< orphan*/  AUE_SETBIT (struct aue_softc*,int /*<<< orphan*/ ,int) ; 
 int AUE_TIMEOUT ; 
 int aue_csr_read_1 (struct aue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aue_csr_write_1 (struct aue_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aue_reset_pegasus_II (struct aue_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 scalar_t__ uether_pause (TYPE_1__*,int) ; 

__attribute__((used)) static void
aue_reset(struct aue_softc *sc)
{
	int i;

	AUE_SETBIT(sc, AUE_CTL1, AUE_CTL1_RESETMAC);

	for (i = 0; i != AUE_TIMEOUT; i++) {
		if (!(aue_csr_read_1(sc, AUE_CTL1) & AUE_CTL1_RESETMAC))
			break;
		if (uether_pause(&sc->sc_ue, hz / 100))
			break;
	}

	if (i == AUE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev, "reset failed\n");

	/*
	 * The PHY(s) attached to the Pegasus chip may be held
	 * in reset until we flip on the GPIO outputs. Make sure
	 * to set the GPIO pins high so that the PHY(s) will
	 * be enabled.
	 *
	 * NOTE: We used to force all of the GPIO pins low first and then
	 * enable the ones we want. This has been changed to better
	 * match the ADMtek's reference design to avoid setting the
	 * power-down configuration line of the PHY at the same time
	 * it is reset.
	 */
	aue_csr_write_1(sc, AUE_GPIO0, AUE_GPIO_SEL0|AUE_GPIO_SEL1);
	aue_csr_write_1(sc, AUE_GPIO0, AUE_GPIO_SEL0|AUE_GPIO_SEL1|AUE_GPIO_OUT0);

	if (sc->sc_flags & AUE_FLAG_LSYS) {
		/* Grrr. LinkSys has to be different from everyone else. */
		aue_csr_write_1(sc, AUE_GPIO0, AUE_GPIO_SEL0|AUE_GPIO_SEL1);
		aue_csr_write_1(sc, AUE_GPIO0,
		    AUE_GPIO_SEL0|AUE_GPIO_SEL1|AUE_GPIO_OUT0);
	}
	if (sc->sc_flags & AUE_FLAG_PII)
		aue_reset_pegasus_II(sc);

	/* Wait a little while for the chip to get its brains in order: */
	uether_pause(&sc->sc_ue, hz / 100);
}
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
typedef  int uint32_t ;
struct bwi_softc {scalar_t__ sc_bbp_id; int sc_card_flags; } ;
struct bwi_regwin {int dummy; } ;
struct bwi_mac {struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BWI_BBPID_BCM4301 ; 
 int BWI_CARD_F_PA_GPIO9 ; 
 int /*<<< orphan*/  BWI_GPIO_CTRL ; 
 struct bwi_regwin* BWI_GPIO_REGWIN (struct bwi_softc*) ; 
 int /*<<< orphan*/  BWI_MAC_GPIO_MASK ; 
 int /*<<< orphan*/  BWI_MAC_STATUS ; 
 int /*<<< orphan*/  BWI_MAC_STATUS_GPOSEL_MASK ; 
 int /*<<< orphan*/  CSR_CLRBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_FILT_SETBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CSR_SETBITS_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int bwi_regwin_switch (struct bwi_softc*,struct bwi_regwin*,struct bwi_regwin**) ; 

__attribute__((used)) static int
bwi_mac_gpio_init(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_regwin *old, *gpio_rw;
	uint32_t filt, bits;
	int error;

	CSR_CLRBITS_4(sc, BWI_MAC_STATUS, BWI_MAC_STATUS_GPOSEL_MASK);
	/* TODO:LED */

	CSR_SETBITS_2(sc, BWI_MAC_GPIO_MASK, 0xf);

	filt = 0x1f;
	bits = 0xf;
	if (sc->sc_bbp_id == BWI_BBPID_BCM4301) {
		filt |= 0x60;
		bits |= 0x60;
	}
	if (sc->sc_card_flags & BWI_CARD_F_PA_GPIO9) {
		CSR_SETBITS_2(sc, BWI_MAC_GPIO_MASK, 0x200);
		filt |= 0x200;
		bits |= 0x200;
	}

	gpio_rw = BWI_GPIO_REGWIN(sc);
	error = bwi_regwin_switch(sc, gpio_rw, &old);
	if (error)
		return error;

	CSR_FILT_SETBITS_4(sc, BWI_GPIO_CTRL, filt, bits);

	return bwi_regwin_switch(sc, old, NULL);
}
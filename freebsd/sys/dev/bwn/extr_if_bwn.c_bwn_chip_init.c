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
typedef  int u_int ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy {scalar_t__ type; int /*<<< orphan*/  (* set_antenna ) (struct bwn_mac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_im ) (struct bwn_mac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* switch_analog ) (struct bwn_mac*,int) ;scalar_t__ gmode; } ;
struct bwn_mac {struct bwn_phy mac_phy; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CLOCK_HT ; 
 int /*<<< orphan*/  BWN_ANT_DEFAULT ; 
 int BWN_DMA0_INTR_MASK ; 
 int BWN_DMA1_INTR_MASK ; 
 int BWN_DMA2_INTR_MASK ; 
 int BWN_DMA3_INTR_MASK ; 
 int BWN_DMA4_INTR_MASK ; 
 int BWN_DMA5_INTR_MASK ; 
 int /*<<< orphan*/  BWN_IMMODE_NONE ; 
 int BWN_INTR_REASON ; 
 int BWN_MACCTL ; 
 int BWN_MACCTL_GMODE ; 
 int BWN_MACCTL_IHR_ON ; 
 int BWN_MACCTL_SHM_ON ; 
 int BWN_MACCTL_STA ; 
 scalar_t__ BWN_PHYTYPE_B ; 
 int BWN_POWERUP_DELAY ; 
 int BWN_READ_2 (struct bwn_mac*,int) ; 
 int BWN_READ_4 (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int,int) ; 
 int ENXIO ; 
 int UINT16_MAX ; 
 int bhnd_get_clock_latency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 int bwn_fw_fillinfo (struct bwn_mac*) ; 
 int bwn_fw_loadinitvals (struct bwn_mac*) ; 
 int bwn_fw_loaducode (struct bwn_mac*) ; 
 int bwn_gpio_init (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_mac_phy_clock_set (struct bwn_mac*,int) ; 
 int bwn_phy_init (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_set_opmode (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_set_txantenna (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  stub2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_chip_init(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_phy *phy = &mac->mac_phy;
	uint32_t macctl;
	u_int delay;
	int error;

	macctl = BWN_MACCTL_IHR_ON | BWN_MACCTL_SHM_ON | BWN_MACCTL_STA;
	if (phy->gmode)
		macctl |= BWN_MACCTL_GMODE;
	BWN_WRITE_4(mac, BWN_MACCTL, macctl);

	error = bwn_fw_fillinfo(mac);
	if (error)
		return (error);
	error = bwn_fw_loaducode(mac);
	if (error)
		return (error);

	error = bwn_gpio_init(mac);
	if (error)
		return (error);

	error = bwn_fw_loadinitvals(mac);
	if (error)
		return (error);

	phy->switch_analog(mac, 1);
	error = bwn_phy_init(mac);
	if (error)
		return (error);

	if (phy->set_im)
		phy->set_im(mac, BWN_IMMODE_NONE);
	if (phy->set_antenna)
		phy->set_antenna(mac, BWN_ANT_DEFAULT);
	bwn_set_txantenna(mac, BWN_ANT_DEFAULT);

	if (phy->type == BWN_PHYTYPE_B)
		BWN_WRITE_2(mac, 0x005e, BWN_READ_2(mac, 0x005e) | 0x0004);
	BWN_WRITE_4(mac, 0x0100, 0x01000000);
	if (bhnd_get_hwrev(sc->sc_dev) < 5)
		BWN_WRITE_4(mac, 0x010c, 0x01000000);

	BWN_WRITE_4(mac, BWN_MACCTL,
	    BWN_READ_4(mac, BWN_MACCTL) & ~BWN_MACCTL_STA);
	BWN_WRITE_4(mac, BWN_MACCTL,
	    BWN_READ_4(mac, BWN_MACCTL) | BWN_MACCTL_STA);
	bwn_shm_write_2(mac, BWN_SHARED, 0x0074, 0x0000);

	bwn_set_opmode(mac);
	if (bhnd_get_hwrev(sc->sc_dev) < 3) {
		BWN_WRITE_2(mac, 0x060e, 0x0000);
		BWN_WRITE_2(mac, 0x0610, 0x8000);
		BWN_WRITE_2(mac, 0x0604, 0x0000);
		BWN_WRITE_2(mac, 0x0606, 0x0200);
	} else {
		BWN_WRITE_4(mac, 0x0188, 0x80000000);
		BWN_WRITE_4(mac, 0x018c, 0x02000000);
	}
	BWN_WRITE_4(mac, BWN_INTR_REASON, 0x00004000);
	BWN_WRITE_4(mac, BWN_DMA0_INTR_MASK, 0x0001dc00);
	BWN_WRITE_4(mac, BWN_DMA1_INTR_MASK, 0x0000dc00);
	BWN_WRITE_4(mac, BWN_DMA2_INTR_MASK, 0x0000dc00);
	BWN_WRITE_4(mac, BWN_DMA3_INTR_MASK, 0x0001dc00);
	BWN_WRITE_4(mac, BWN_DMA4_INTR_MASK, 0x0000dc00);
	BWN_WRITE_4(mac, BWN_DMA5_INTR_MASK, 0x0000dc00);

	bwn_mac_phy_clock_set(mac, true);

	/* Provide the HT clock transition latency to the MAC core */
	error = bhnd_get_clock_latency(sc->sc_dev, BHND_CLOCK_HT, &delay);
	if (error) {
		device_printf(sc->sc_dev, "failed to fetch HT clock latency: "
		    "%d\n", error);
		return (error);
	}

	if (delay > UINT16_MAX) {
		device_printf(sc->sc_dev, "invalid HT clock latency: %u\n",
		    delay);
		return (ENXIO);
	}

	BWN_WRITE_2(mac, BWN_POWERUP_DELAY, delay);
	return (0);
}
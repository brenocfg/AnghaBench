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
typedef  int uint16_t ;
struct bwn_rfatt {int att; scalar_t__ padmix; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct bwn_phy_g {scalar_t__ pg_max_lb_gain; } ;
struct bwn_phy {int /*<<< orphan*/  chan; struct bwn_phy_g phy_g; } ;
struct bwn_mac {TYPE_1__* mac_sc; struct bwn_phy mac_phy; } ;
typedef  struct bwn_loctl {int att; scalar_t__ padmix; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } const bwn_loctl ;
struct bwn_lo_g_value {int /*<<< orphan*/  old_channel; int /*<<< orphan*/  member_0; } ;
struct bwn_lo_calib {int /*<<< orphan*/  calib_time; int /*<<< orphan*/  ctl; int /*<<< orphan*/  rfatt; int /*<<< orphan*/  bbatt; } ;
struct bwn_bbatt {int att; scalar_t__ padmix; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  loctl ;
struct TYPE_2__ {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_GETTIME (int /*<<< orphan*/ ) ; 
 scalar_t__ BWN_HAS_LOOPBACK (struct bwn_phy*) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bwn_lo_measure_gain_values (struct bwn_mac*,int,scalar_t__) ; 
 int /*<<< orphan*/  bwn_lo_probe_sm (struct bwn_mac*,struct bwn_rfatt const*,int*) ; 
 int /*<<< orphan*/  bwn_lo_restore (struct bwn_mac*,struct bwn_lo_g_value*) ; 
 int /*<<< orphan*/  bwn_lo_save (struct bwn_mac*,struct bwn_lo_g_value*) ; 
 int bwn_lo_txctl_regtable (struct bwn_mac*,int*,int*) ; 
 int /*<<< orphan*/  bwn_mac_enable (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_mac_suspend (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_g_set_bbatt (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct bwn_lo_calib* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct bwn_rfatt const*,int) ; 

__attribute__((used)) static struct bwn_lo_calib *
bwn_lo_calibset(struct bwn_mac *mac,
    const struct bwn_bbatt *bbatt, const struct bwn_rfatt *rfatt)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	struct bwn_loctl loctl = { 0, 0 };
	struct bwn_lo_calib *cal;
	struct bwn_lo_g_value sval = { 0 };
	int rxgain;
	uint16_t pad, reg, value;

	sval.old_channel = phy->chan;
	bwn_mac_suspend(mac);
	bwn_lo_save(mac, &sval);

	reg = bwn_lo_txctl_regtable(mac, &value, &pad);
	BWN_RF_SETMASK(mac, 0x43, 0xfff0, rfatt->att);
	BWN_RF_SETMASK(mac, reg, ~value, (rfatt->padmix ? value :0));

	rxgain = (rfatt->att * 2) + (bbatt->att / 2);
	if (rfatt->padmix)
		rxgain -= pad;
	if (BWN_HAS_LOOPBACK(phy))
		rxgain += pg->pg_max_lb_gain;
	bwn_lo_measure_gain_values(mac, rxgain, BWN_HAS_LOOPBACK(phy));
	bwn_phy_g_set_bbatt(mac, bbatt->att);
	bwn_lo_probe_sm(mac, &loctl, &rxgain);

	bwn_lo_restore(mac, &sval);
	bwn_mac_enable(mac);

	cal = malloc(sizeof(*cal), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!cal) {
		device_printf(mac->mac_sc->sc_dev, "out of memory\n");
		return (NULL);
	}
	memcpy(&cal->bbatt, bbatt, sizeof(*bbatt));
	memcpy(&cal->rfatt, rfatt, sizeof(*rfatt));
	memcpy(&cal->ctl, &loctl, sizeof(loctl));

	BWN_GETTIME(cal->calib_time);

	return (cal);
}
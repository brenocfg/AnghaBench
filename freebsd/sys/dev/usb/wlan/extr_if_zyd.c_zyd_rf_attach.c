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
typedef  int uint8_t ;
struct zyd_rf {int update_pwr; int width; int /*<<< orphan*/  set_channel; int /*<<< orphan*/  switch_radio; int /*<<< orphan*/  init; int /*<<< orphan*/  bandedge6; struct zyd_softc* rf_sc; } ;
struct zyd_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_macrev; struct zyd_rf sc_rf; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ZYD_RF_AL2210 135 
#define  ZYD_RF_AL2230 134 
#define  ZYD_RF_AL2230S 133 
#define  ZYD_RF_AL7230B 132 
#define  ZYD_RF_GCT 131 
#define  ZYD_RF_MAXIM_NEW 130 
#define  ZYD_RF_MAXIM_NEW2 129 
#define  ZYD_RF_RFMD 128 
 int /*<<< orphan*/  ZYD_ZD1211B ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zyd_al2210_init ; 
 int /*<<< orphan*/  zyd_al2210_set_channel ; 
 int /*<<< orphan*/  zyd_al2210_switch_radio ; 
 int /*<<< orphan*/  zyd_al2230_bandedge6 ; 
 int /*<<< orphan*/  zyd_al2230_init ; 
 int /*<<< orphan*/  zyd_al2230_init_b ; 
 int /*<<< orphan*/  zyd_al2230_set_channel ; 
 int /*<<< orphan*/  zyd_al2230_set_channel_b ; 
 int /*<<< orphan*/  zyd_al2230_switch_radio ; 
 int /*<<< orphan*/  zyd_al7230B_init ; 
 int /*<<< orphan*/  zyd_al7230B_set_channel ; 
 int /*<<< orphan*/  zyd_al7230B_switch_radio ; 
 int /*<<< orphan*/  zyd_gct_init ; 
 int /*<<< orphan*/  zyd_gct_set_channel ; 
 int /*<<< orphan*/  zyd_gct_switch_radio ; 
 int /*<<< orphan*/  zyd_maxim2_init ; 
 int /*<<< orphan*/  zyd_maxim2_set_channel ; 
 int /*<<< orphan*/  zyd_maxim2_switch_radio ; 
 int /*<<< orphan*/  zyd_rf_name (int) ; 
 int /*<<< orphan*/  zyd_rfmd_init ; 
 int /*<<< orphan*/  zyd_rfmd_set_channel ; 
 int /*<<< orphan*/  zyd_rfmd_switch_radio ; 

__attribute__((used)) static int
zyd_rf_attach(struct zyd_softc *sc, uint8_t type)
{
	struct zyd_rf *rf = &sc->sc_rf;

	rf->rf_sc = sc;
	rf->update_pwr = 1;

	switch (type) {
	case ZYD_RF_RFMD:
		rf->init         = zyd_rfmd_init;
		rf->switch_radio = zyd_rfmd_switch_radio;
		rf->set_channel  = zyd_rfmd_set_channel;
		rf->width        = 24;	/* 24-bit RF values */
		break;
	case ZYD_RF_AL2230:
	case ZYD_RF_AL2230S:
		if (sc->sc_macrev == ZYD_ZD1211B) {
			rf->init = zyd_al2230_init_b;
			rf->set_channel = zyd_al2230_set_channel_b;
		} else {
			rf->init = zyd_al2230_init;
			rf->set_channel = zyd_al2230_set_channel;
		}
		rf->switch_radio = zyd_al2230_switch_radio;
		rf->bandedge6	 = zyd_al2230_bandedge6;
		rf->width        = 24;	/* 24-bit RF values */
		break;
	case ZYD_RF_AL7230B:
		rf->init         = zyd_al7230B_init;
		rf->switch_radio = zyd_al7230B_switch_radio;
		rf->set_channel  = zyd_al7230B_set_channel;
		rf->width        = 24;	/* 24-bit RF values */
		break;
	case ZYD_RF_AL2210:
		rf->init         = zyd_al2210_init;
		rf->switch_radio = zyd_al2210_switch_radio;
		rf->set_channel  = zyd_al2210_set_channel;
		rf->width        = 24;	/* 24-bit RF values */
		break;
	case ZYD_RF_MAXIM_NEW:
	case ZYD_RF_GCT:
		rf->init         = zyd_gct_init;
		rf->switch_radio = zyd_gct_switch_radio;
		rf->set_channel  = zyd_gct_set_channel;
		rf->width        = 24;	/* 24-bit RF values */
		rf->update_pwr   = 0;
		break;
	case ZYD_RF_MAXIM_NEW2:
		rf->init         = zyd_maxim2_init;
		rf->switch_radio = zyd_maxim2_switch_radio;
		rf->set_channel  = zyd_maxim2_set_channel;
		rf->width        = 18;	/* 18-bit RF values */
		break;
	default:
		device_printf(sc->sc_dev,
		    "sorry, radio \"%s\" is not supported yet\n",
		    zyd_rf_name(type));
		return (EINVAL);
	}
	return (0);
}
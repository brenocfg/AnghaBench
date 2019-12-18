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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct urtw_softc {int sc_flags; int /*<<< orphan*/  sc_dev; void* sc_rf_stop; void* sc_sens; void* sc_max_sens; int /*<<< orphan*/  sc_rf_set_chan; int /*<<< orphan*/  sc_rf_init; int /*<<< orphan*/  sc_rf_set_sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct urtw_softc*,int /*<<< orphan*/ ,char*,int) ; 
 void* URTW_8225_RF_DEF_SENS ; 
 void* URTW_8225_RF_MAX_SENS ; 
 int /*<<< orphan*/  URTW_DEBUG_STATE ; 
 int /*<<< orphan*/  URTW_EPROM_RFCHIPID ; 
#define  URTW_EPROM_RFCHIPID_RTL8225U 131 
#define  URTW_EPROM_RFCHIPID_RTL8225Z2 130 
 int URTW_RTL8187B ; 
 int URTW_RTL8187B_REV_B ; 
 int URTW_RTL8187B_REV_D ; 
 int URTW_RTL8187B_REV_E ; 
 int /*<<< orphan*/  URTW_TX_CONF ; 
 int URTW_TX_HWMASK ; 
#define  URTW_TX_R8187vD 129 
#define  URTW_TX_R8187vD_B 128 
 scalar_t__ USB_ERR_INVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ urtw_8225_isv2 (struct urtw_softc*,int*) ; 
 int /*<<< orphan*/  urtw_8225_rf_init ; 
 int /*<<< orphan*/  urtw_8225_rf_set_chan ; 
 int /*<<< orphan*/  urtw_8225_rf_set_sens ; 
 void* urtw_8225_rf_stop ; 
 int /*<<< orphan*/  urtw_8225v2_rf_init ; 
 int /*<<< orphan*/  urtw_8225v2_rf_set_chan ; 
 int /*<<< orphan*/  urtw_8225v2b_rf_init ; 
 int /*<<< orphan*/  urtw_8225v2b_rf_set_chan ; 
 scalar_t__ urtw_eprom_read32 (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_read32_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int,int*) ; 

__attribute__((used)) static usb_error_t
urtw_get_rfchip(struct urtw_softc *sc)
{
	int ret;
	uint8_t data8;
	uint32_t data;
	usb_error_t error;

	if (sc->sc_flags & URTW_RTL8187B) {
		urtw_read8_m(sc, 0xe1, &data8);
		switch (data8) {
		case 0:
			sc->sc_flags |= URTW_RTL8187B_REV_B;
			break;
		case 1:
			sc->sc_flags |= URTW_RTL8187B_REV_D;
			break;
		case 2:
			sc->sc_flags |= URTW_RTL8187B_REV_E;
			break;
		default:
			device_printf(sc->sc_dev, "unknown type: %#x\n", data8);
			sc->sc_flags |= URTW_RTL8187B_REV_B;
			break;
		}
	} else {
		urtw_read32_m(sc, URTW_TX_CONF, &data);
		switch (data & URTW_TX_HWMASK) {
		case URTW_TX_R8187vD_B:
			sc->sc_flags |= URTW_RTL8187B;
			break;
		case URTW_TX_R8187vD:
			break;
		default:
			device_printf(sc->sc_dev, "unknown RTL8187L type: %#x\n",
			    data & URTW_TX_HWMASK);
			break;
		}
	}

	error = urtw_eprom_read32(sc, URTW_EPROM_RFCHIPID, &data);
	if (error != 0)
		goto fail;
	switch (data & 0xff) {
	case URTW_EPROM_RFCHIPID_RTL8225U:
		error = urtw_8225_isv2(sc, &ret);
		if (error != 0)
			goto fail;
		if (ret == 0) {
			sc->sc_rf_init = urtw_8225_rf_init;
			sc->sc_rf_set_sens = urtw_8225_rf_set_sens;
			sc->sc_rf_set_chan = urtw_8225_rf_set_chan;
			sc->sc_rf_stop = urtw_8225_rf_stop;
		} else {
			sc->sc_rf_init = urtw_8225v2_rf_init;
			sc->sc_rf_set_chan = urtw_8225v2_rf_set_chan;
			sc->sc_rf_stop = urtw_8225_rf_stop;
		}
		sc->sc_max_sens = URTW_8225_RF_MAX_SENS;
		sc->sc_sens = URTW_8225_RF_DEF_SENS;
		break;
	case URTW_EPROM_RFCHIPID_RTL8225Z2:
		sc->sc_rf_init = urtw_8225v2b_rf_init;
		sc->sc_rf_set_chan = urtw_8225v2b_rf_set_chan;
		sc->sc_max_sens = URTW_8225_RF_MAX_SENS;
		sc->sc_sens = URTW_8225_RF_DEF_SENS;
		sc->sc_rf_stop = urtw_8225_rf_stop;
		break;
	default:
		DPRINTF(sc, URTW_DEBUG_STATE,
		    "unsupported RF chip %d\n", data & 0xff);
		error = USB_ERR_INVAL;
		goto fail;
	}

	device_printf(sc->sc_dev, "%s rf %s hwrev %s\n",
	    (sc->sc_flags & URTW_RTL8187B) ? "rtl8187b" : "rtl8187l",
	    ((data & 0xff) == URTW_EPROM_RFCHIPID_RTL8225U) ? "rtl8225u" :
	    "rtl8225z2",
	    (sc->sc_flags & URTW_RTL8187B) ? ((data8 == 0) ? "b" :
		(data8 == 1) ? "d" : "e") : "none");

fail:
	return (error);
}
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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {int ic_opmode; } ;
struct urtw_softc {scalar_t__ sc_state; int sc_flags; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct urtw_softc*,int /*<<< orphan*/ ,char*,int) ; 
#define  IEEE80211_M_HOSTAP 131 
#define  IEEE80211_M_IBSS 130 
#define  IEEE80211_M_MONITOR 129 
#define  IEEE80211_M_STA 128 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  URTW_DEBUG_STATE ; 
 int /*<<< orphan*/  URTW_MSR ; 
 int /*<<< orphan*/  URTW_MSR_LINK_ADHOC ; 
 int /*<<< orphan*/  URTW_MSR_LINK_ENEDCA ; 
 int /*<<< orphan*/  URTW_MSR_LINK_HOSTAP ; 
 int /*<<< orphan*/  URTW_MSR_LINK_MASK ; 
 int /*<<< orphan*/  URTW_MSR_LINK_NONE ; 
 int /*<<< orphan*/  URTW_MSR_LINK_STA ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
urtw_update_msr(struct urtw_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t data;
	usb_error_t error;

	urtw_read8_m(sc, URTW_MSR, &data);
	data &= ~URTW_MSR_LINK_MASK;

	if (sc->sc_state == IEEE80211_S_RUN) {
		switch (ic->ic_opmode) {
		case IEEE80211_M_STA:
		case IEEE80211_M_MONITOR:
			data |= URTW_MSR_LINK_STA;
			if (sc->sc_flags & URTW_RTL8187B)
				data |= URTW_MSR_LINK_ENEDCA;
			break;
		case IEEE80211_M_IBSS:
			data |= URTW_MSR_LINK_ADHOC;
			break;
		case IEEE80211_M_HOSTAP:
			data |= URTW_MSR_LINK_HOSTAP;
			break;
		default:
			DPRINTF(sc, URTW_DEBUG_STATE,
			    "unsupported operation mode 0x%x\n",
			    ic->ic_opmode);
			error = USB_ERR_INVAL;
			goto fail;
		}
	} else
		data |= URTW_MSR_LINK_NONE;

	urtw_write8_m(sc, URTW_MSR, data);
fail:
	return (error);
}
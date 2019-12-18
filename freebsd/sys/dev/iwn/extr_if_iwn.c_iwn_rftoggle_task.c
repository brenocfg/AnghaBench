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
struct ieee80211com {int dummy; } ;
struct iwn_softc {int int_mask; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_GP_CNTRL ; 
 int IWN_GP_CNTRL_RFKILL ; 
 int /*<<< orphan*/  IWN_INT ; 
 int /*<<< orphan*/  IWN_INT_MASK ; 
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int IWN_READ (struct iwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_WRITE (struct iwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ieee80211_resume_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_suspend_all (struct ieee80211com*) ; 

__attribute__((used)) static void
iwn_rftoggle_task(void *arg, int npending)
{
	struct iwn_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t tmp;

	IWN_LOCK(sc);
	tmp = IWN_READ(sc, IWN_GP_CNTRL);
	IWN_UNLOCK(sc);

	device_printf(sc->sc_dev, "RF switch: radio %s\n",
	    (tmp & IWN_GP_CNTRL_RFKILL) ? "enabled" : "disabled");
	if (!(tmp & IWN_GP_CNTRL_RFKILL)) {
		ieee80211_suspend_all(ic);

		/* Enable interrupts to get RF toggle notification. */
		IWN_LOCK(sc);
		IWN_WRITE(sc, IWN_INT, 0xffffffff);
		IWN_WRITE(sc, IWN_INT_MASK, sc->int_mask);
		IWN_UNLOCK(sc);
	} else
		ieee80211_resume_all(ic);
}
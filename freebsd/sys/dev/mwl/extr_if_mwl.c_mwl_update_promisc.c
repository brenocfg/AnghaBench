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
struct mwl_softc {int /*<<< orphan*/  sc_mh; } ;
struct ieee80211com {scalar_t__ ic_promisc; struct mwl_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwl_hal_setpromisc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mwl_update_promisc(struct ieee80211com *ic)
{
	struct mwl_softc *sc = ic->ic_softc;

	mwl_hal_setpromisc(sc->sc_mh, ic->ic_promisc > 0);
}
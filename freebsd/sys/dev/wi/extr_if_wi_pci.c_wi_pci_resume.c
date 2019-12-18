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
struct ieee80211com {scalar_t__ ic_nrunning; } ;
struct wi_softc {scalar_t__ wi_bus_type; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ WI_BUS_PCI_NATIVE ; 
 int /*<<< orphan*/  WI_LOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  WI_UNLOCK (struct wi_softc*) ; 
 struct wi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_init (struct wi_softc*) ; 

__attribute__((used)) static int
wi_pci_resume(device_t dev)
{
	struct wi_softc	*sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;

	WI_LOCK(sc);
	if (sc->wi_bus_type != WI_BUS_PCI_NATIVE) {
		WI_UNLOCK(sc);
		return (0);
	}
	if (ic->ic_nrunning > 0)
		wi_init(sc);
	WI_UNLOCK(sc);
	return (0);
}
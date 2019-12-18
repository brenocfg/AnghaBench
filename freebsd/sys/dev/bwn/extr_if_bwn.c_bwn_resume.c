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
struct TYPE_2__ {scalar_t__ ic_nrunning; } ;
struct bwn_softc {TYPE_1__ sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int EDOOFUS ; 
 int bwn_init (struct bwn_softc*) ; 
 struct bwn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_start_all (TYPE_1__*) ; 

__attribute__((used)) static int
bwn_resume(device_t dev)
{
	struct bwn_softc *sc = device_get_softc(dev);
	int error = EDOOFUS;

	BWN_LOCK(sc);
	if (sc->sc_ic.ic_nrunning > 0)
		error = bwn_init(sc);
	BWN_UNLOCK(sc);
	if (error == 0)
		ieee80211_start_all(&sc->sc_ic);
	return (0);
}
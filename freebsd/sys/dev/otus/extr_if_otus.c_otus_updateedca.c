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
struct otus_softc {int dummy; } ;
struct ieee80211com {struct otus_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTUS_LOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  OTUS_UNLOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_updateedca_locked (struct otus_softc*) ; 

__attribute__((used)) static int
otus_updateedca(struct ieee80211com *ic)
{
	struct otus_softc *sc = ic->ic_softc;

	OTUS_LOCK(sc);
	/*
	 * XXX TODO: take temporary copy of EDCA information
	 * when scheduling this so we have a more time-correct view
	 * of things.
	 * XXX TODO: this can be done on the net80211 level
	 */
	otus_updateedca_locked(sc);
	OTUS_UNLOCK(sc);
	return (0);
}
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
struct zyd_softc {int dummy; } ;
struct ieee80211com {struct zyd_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_LOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  ZYD_UNLOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_set_multi (struct zyd_softc*) ; 

__attribute__((used)) static void
zyd_update_mcast(struct ieee80211com *ic)
{
	struct zyd_softc *sc = ic->ic_softc;

	ZYD_LOCK(sc);
	zyd_set_multi(sc);
	ZYD_UNLOCK(sc);
}
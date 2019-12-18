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
struct run_softc {int dummy; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int IEEE80211_GET_SLOTTIME (struct ieee80211com*) ; 
 int /*<<< orphan*/  RT2860_BKOFF_SLOT_CFG ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_updateslot_cb(void *arg)
{
	struct ieee80211com *ic = arg;
	struct run_softc *sc = ic->ic_softc;
	uint32_t tmp;

	run_read(sc, RT2860_BKOFF_SLOT_CFG, &tmp);
	tmp &= ~0xff;
	tmp |= IEEE80211_GET_SLOTTIME(ic);
	run_write(sc, RT2860_BKOFF_SLOT_CFG, tmp);
}
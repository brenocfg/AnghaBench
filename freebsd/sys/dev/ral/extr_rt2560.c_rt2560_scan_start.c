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
struct rt2560_softc {int dummy; } ;
struct ieee80211com {struct rt2560_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2560_CSR14 ; 
 int /*<<< orphan*/  ieee80211broadcastaddr ; 
 int /*<<< orphan*/  rt2560_set_bssid (struct rt2560_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2560_scan_start(struct ieee80211com *ic)
{
	struct rt2560_softc *sc = ic->ic_softc;

	/* abort TSF synchronization */
	RAL_WRITE(sc, RT2560_CSR14, 0);
	rt2560_set_bssid(sc, ieee80211broadcastaddr);
}
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
struct rt2661_softc {int dummy; } ;
struct ieee80211com {struct rt2661_softc* ic_softc; } ;

/* Variables and functions */
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2661_TXRX_CSR9 ; 
 int /*<<< orphan*/  ieee80211broadcastaddr ; 
 int /*<<< orphan*/  rt2661_set_bssid (struct rt2661_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2661_scan_start(struct ieee80211com *ic)
{
	struct rt2661_softc *sc = ic->ic_softc;
	uint32_t tmp;

	/* abort TSF synchronization */
	tmp = RAL_READ(sc, RT2661_TXRX_CSR9);
	RAL_WRITE(sc, RT2661_TXRX_CSR9, tmp & ~0xffffff);
	rt2661_set_bssid(sc, ieee80211broadcastaddr);
}
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
struct ieee80211com {struct bwi_softc* ic_softc; } ;
struct bwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_LOCK (struct bwi_softc*) ; 
 int /*<<< orphan*/  BWI_MAC_STATUS ; 
 int /*<<< orphan*/  BWI_MAC_STATUS_PASS_BCN ; 
 int /*<<< orphan*/  BWI_UNLOCK (struct bwi_softc*) ; 
 int /*<<< orphan*/  CSR_CLRBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_scan_end(struct ieee80211com *ic)
{
	struct bwi_softc *sc = ic->ic_softc;

	BWI_LOCK(sc);
	CSR_CLRBITS_4(sc, BWI_MAC_STATUS, BWI_MAC_STATUS_PASS_BCN);
	BWI_UNLOCK(sc);
}
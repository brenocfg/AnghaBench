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
struct rtwn_vap {scalar_t__ curr_mode; int /*<<< orphan*/  id; } ;
struct rtwn_softc {int dummy; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 scalar_t__ R92C_MSR_NOLINK ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  rtwn_beacon_enable (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtwn_pci_beacon_update_end(struct rtwn_softc *sc, struct ieee80211vap *vap)
{
	struct rtwn_vap *rvp = RTWN_VAP(vap);

	RTWN_ASSERT_LOCKED(sc);

	if (rvp->curr_mode != R92C_MSR_NOLINK)
		rtwn_beacon_enable(sc, rvp->id, 1);
}
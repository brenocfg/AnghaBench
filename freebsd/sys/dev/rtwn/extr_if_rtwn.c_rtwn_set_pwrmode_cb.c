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
typedef  union sec_param {int dummy; } sec_param ;
struct rtwn_softc {TYPE_1__** vaps; } ;
struct ieee80211vap {int dummy; } ;
struct TYPE_2__ {struct ieee80211vap vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_set_pwrmode (struct rtwn_softc*,struct ieee80211vap*,int) ; 

__attribute__((used)) static void
rtwn_set_pwrmode_cb(struct rtwn_softc *sc, union sec_param *data)
{
	struct ieee80211vap *vap = &sc->vaps[0]->vap;

	if (vap != NULL)
		rtwn_set_pwrmode(sc, vap, 1);
}
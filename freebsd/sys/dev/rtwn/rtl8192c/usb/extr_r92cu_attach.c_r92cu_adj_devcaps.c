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
struct TYPE_2__ {int /*<<< orphan*/  ic_caps; } ;
struct rtwn_softc {TYPE_1__ sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_C_PMGT ; 

__attribute__((used)) static void
r92cu_adj_devcaps(struct rtwn_softc *sc)
{
	/* XXX Currently broken / incomplete. */
	sc->sc_ic.ic_caps &= ~IEEE80211_C_PMGT;
}
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
struct ndis_softc {int dummy; } ;
struct ieee80211com {struct ndis_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndis_setmulti (struct ndis_softc*) ; 

__attribute__((used)) static void
ndis_update_mcast(struct ieee80211com *ic)
{
       struct ndis_softc *sc = ic->ic_softc;

       ndis_setmulti(sc);
}
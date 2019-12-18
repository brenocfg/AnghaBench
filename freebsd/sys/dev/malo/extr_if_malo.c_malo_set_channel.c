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
struct malo_softc {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; struct malo_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  malo_chan_set (struct malo_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
malo_set_channel(struct ieee80211com *ic)
{
	struct malo_softc *sc = ic->ic_softc;

	(void) malo_chan_set(sc, ic->ic_curchan);
}
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
struct mwl_softc {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; struct mwl_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwl_chan_set (struct mwl_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl_set_channel(struct ieee80211com *ic)
{
	struct mwl_softc *sc = ic->ic_softc;

	(void) mwl_chan_set(sc, ic->ic_curchan);
}
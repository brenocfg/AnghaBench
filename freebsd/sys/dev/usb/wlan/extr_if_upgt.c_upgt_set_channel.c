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
struct upgt_softc {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; struct upgt_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_set_chan (struct upgt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_set_channel(struct ieee80211com *ic)
{
	struct upgt_softc *sc = ic->ic_softc;

	UPGT_LOCK(sc);
	upgt_set_chan(sc, ic->ic_curchan);
	UPGT_UNLOCK(sc);
}
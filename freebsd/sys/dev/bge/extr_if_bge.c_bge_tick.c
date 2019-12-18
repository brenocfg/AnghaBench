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
struct mii_data {int dummy; } ;
struct bge_softc {int bge_flags; scalar_t__ bge_asicrev; int /*<<< orphan*/  bge_stat_ch; int /*<<< orphan*/  bge_link_evt; int /*<<< orphan*/  bge_ifp; int /*<<< orphan*/  bge_link; int /*<<< orphan*/  bge_miibus; } ;

/* Variables and functions */
 scalar_t__ BGE_ASICREV_BCM5700 ; 
 int BGE_FLAG_5788 ; 
 int BGE_FLAG_TBI ; 
 int /*<<< orphan*/  BGE_HCCMODE_COAL_NOW ; 
 int /*<<< orphan*/  BGE_HCC_MODE ; 
 scalar_t__ BGE_IS_5705_PLUS (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_MISC_LOCAL_CTL ; 
 int /*<<< orphan*/  BGE_MLC_INTR_SET ; 
 int /*<<< orphan*/  BGE_SETBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  bge_asf_driver_up (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_stats_update (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_stats_update_regs (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_watchdog (struct bge_softc*) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct bge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
bge_tick(void *xsc)
{
	struct bge_softc *sc = xsc;
	struct mii_data *mii = NULL;

	BGE_LOCK_ASSERT(sc);

	/* Synchronize with possible callout reset/stop. */
	if (callout_pending(&sc->bge_stat_ch) ||
	    !callout_active(&sc->bge_stat_ch))
		return;

	if (BGE_IS_5705_PLUS(sc))
		bge_stats_update_regs(sc);
	else
		bge_stats_update(sc);

	/* XXX Add APE heartbeat check here? */

	if ((sc->bge_flags & BGE_FLAG_TBI) == 0) {
		mii = device_get_softc(sc->bge_miibus);
		/*
		 * Do not touch PHY if we have link up. This could break
		 * IPMI/ASF mode or produce extra input errors
		 * (extra errors was reported for bcm5701 & bcm5704).
		 */
		if (!sc->bge_link)
			mii_tick(mii);
	} else {
		/*
		 * Since in TBI mode auto-polling can't be used we should poll
		 * link status manually. Here we register pending link event
		 * and trigger interrupt.
		 */
#ifdef DEVICE_POLLING
		/* In polling mode we poll link state in bge_poll(). */
		if (!(if_getcapenable(sc->bge_ifp) & IFCAP_POLLING))
#endif
		{
		sc->bge_link_evt++;
		if (sc->bge_asicrev == BGE_ASICREV_BCM5700 ||
		    sc->bge_flags & BGE_FLAG_5788)
			BGE_SETBIT(sc, BGE_MISC_LOCAL_CTL, BGE_MLC_INTR_SET);
		else
			BGE_SETBIT(sc, BGE_HCC_MODE, BGE_HCCMODE_COAL_NOW);
		}
	}

	bge_asf_driver_up(sc);
	bge_watchdog(sc);

	callout_reset(&sc->bge_stat_ch, hz, bge_tick, sc);
}
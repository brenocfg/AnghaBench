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
struct storvsc_softc {int /*<<< orphan*/  hs_lock; int /*<<< orphan*/  hs_chan; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct storvsc_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  hv_storvsc_on_channel_callback (int /*<<< orphan*/ ,struct storvsc_softc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
storvsc_poll(struct cam_sim *sim)
{
	struct storvsc_softc *sc = cam_sim_softc(sim);

	mtx_assert(&sc->hs_lock, MA_OWNED);
	mtx_unlock(&sc->hs_lock);
	hv_storvsc_on_channel_callback(sc->hs_chan, sc);
	mtx_lock(&sc->hs_lock);
}
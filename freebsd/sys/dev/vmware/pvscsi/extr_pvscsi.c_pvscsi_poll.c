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
struct pvscsi_softc {int /*<<< orphan*/  lock; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct pvscsi_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_intr_locked (struct pvscsi_softc*) ; 

__attribute__((used)) static void
pvscsi_poll(struct cam_sim *sim)
{
	struct pvscsi_softc *sc;

	sc = cam_sim_softc(sim);

	mtx_assert(&sc->lock, MA_OWNED);
	pvscsi_intr_locked(sc);
}
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
struct sis_softc {int sis_flags; int /*<<< orphan*/  sis_stat_ch; int /*<<< orphan*/  sis_dev; int /*<<< orphan*/  sis_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int SIS_FLAG_LINK ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct sis_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  sis_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_watchdog (struct sis_softc*) ; 

__attribute__((used)) static void
sis_tick(void *xsc)
{
	struct sis_softc	*sc;
	struct mii_data		*mii;

	sc = xsc;
	SIS_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->sis_miibus);
	mii_tick(mii);
	sis_watchdog(sc);
	if ((sc->sis_flags & SIS_FLAG_LINK) == 0)
		sis_miibus_statchg(sc->sis_dev);
	callout_reset(&sc->sis_stat_ch, hz,  sis_tick, sc);
}
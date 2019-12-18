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
struct arge_softc {int /*<<< orphan*/  arge_stat_callout; scalar_t__ arge_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_LOCK_ASSERT (struct arge_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct arge_softc*) ; 
 struct mii_data* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
arge_tick(void *xsc)
{
	struct arge_softc	*sc = xsc;
	struct mii_data		*mii;

	ARGE_LOCK_ASSERT(sc);

	if (sc->arge_miibus) {
		mii = device_get_softc(sc->arge_miibus);
		mii_tick(mii);
		callout_reset(&sc->arge_stat_callout, hz, arge_tick, sc);
	}
}
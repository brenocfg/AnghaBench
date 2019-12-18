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
struct fv_softc {int /*<<< orphan*/  fv_stat_callout; int /*<<< orphan*/  fv_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FV_LOCK_ASSERT (struct fv_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct fv_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
fv_tick(void *xsc)
{
	struct fv_softc		*sc = xsc;
#ifdef MII
	struct mii_data		*mii;

	FV_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->fv_miibus);
	mii_tick(mii);
#endif
	callout_reset(&sc->fv_stat_callout, hz, fv_tick, sc);
}
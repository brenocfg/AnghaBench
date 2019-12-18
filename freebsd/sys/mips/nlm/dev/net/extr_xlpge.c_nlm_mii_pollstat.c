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
struct nlm_xlpge_softc {int /*<<< orphan*/  xlpge_callout; scalar_t__ mii_bus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct nlm_xlpge_softc*) ; 
 struct mii_data* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
nlm_mii_pollstat(void *arg)
{
	struct nlm_xlpge_softc *sc = (struct nlm_xlpge_softc *)arg;
	struct mii_data *mii = NULL;

	if (sc->mii_bus) {
		mii = device_get_softc(sc->mii_bus);

		KASSERT(mii != NULL, ("mii ptr is NULL"));

		mii_pollstat(mii);

		callout_reset(&sc->xlpge_callout, hz,
		    nlm_mii_pollstat, sc);
	}
}
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
struct mii_data {int mii_media_status; scalar_t__ mii_media_active; } ;
struct cgem_softc {scalar_t__ mii_media_active; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int /*<<< orphan*/  cgem_mediachange (struct cgem_softc*,struct mii_data*) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgem_miibus_linkchg(device_t dev)
{
	struct cgem_softc *sc  = device_get_softc(dev);
	struct mii_data *mii = device_get_softc(sc->miibus);

	CGEM_ASSERT_LOCKED(sc);

	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID) &&
	    sc->mii_media_active != mii->mii_media_active)
		cgem_mediachange(sc, mii);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct g_shsec_softc {size_t sc_ndisks; int /*<<< orphan*/  sc_name; TYPE_3__* sc_provider; TYPE_2__** sc_disks; int /*<<< orphan*/  sc_geom; } ;
typedef  scalar_t__ off_t ;
struct TYPE_7__ {size_t sectorsize; scalar_t__ mediasize; } ;
struct TYPE_6__ {TYPE_1__* provider; } ;
struct TYPE_5__ {scalar_t__ mediasize; scalar_t__ sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SHSEC_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_provider (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_new_providerf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t g_shsec_nvalid (struct g_shsec_softc*) ; 
 size_t lcm (size_t,scalar_t__) ; 

__attribute__((used)) static void
g_shsec_check_and_run(struct g_shsec_softc *sc)
{
	off_t mediasize, ms;
	u_int no, sectorsize = 0;

	if (g_shsec_nvalid(sc) != sc->sc_ndisks)
		return;

	sc->sc_provider = g_new_providerf(sc->sc_geom, "shsec/%s", sc->sc_name);
	/*
	 * Find the smallest disk.
	 */
	mediasize = sc->sc_disks[0]->provider->mediasize;
	mediasize -= sc->sc_disks[0]->provider->sectorsize;
	sectorsize = sc->sc_disks[0]->provider->sectorsize;
	for (no = 1; no < sc->sc_ndisks; no++) {
		ms = sc->sc_disks[no]->provider->mediasize;
		ms -= sc->sc_disks[no]->provider->sectorsize;
		if (ms < mediasize)
			mediasize = ms;
		sectorsize = lcm(sectorsize,
		    sc->sc_disks[no]->provider->sectorsize);
	}
	sc->sc_provider->sectorsize = sectorsize;
	sc->sc_provider->mediasize = mediasize;
	g_error_provider(sc->sc_provider, 0);

	G_SHSEC_DEBUG(0, "Device %s activated.", sc->sc_name);
}
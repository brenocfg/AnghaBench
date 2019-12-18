#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct g_provider {int /*<<< orphan*/  name; scalar_t__ sectorsize; scalar_t__ mediasize; } ;
struct g_eli_softc {int sc_flags; TYPE_1__* sc_geom; } ;
struct g_consumer {struct g_provider* provider; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; int /*<<< orphan*/  provider; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  G_ELI_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int G_ELI_FLAG_RO ; 
 void* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ELI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_destroy (struct g_eli_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_eli_overwrites ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_flush (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int g_write_data (struct g_consumer*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_eli_kill_one(struct g_eli_softc *sc)
{
	struct g_provider *pp;
	struct g_consumer *cp;
	int error = 0;

	g_topology_assert();

	if (sc == NULL)
		return (ENOENT);

	pp = LIST_FIRST(&sc->sc_geom->provider);
	g_error_provider(pp, ENXIO);

	cp = LIST_FIRST(&sc->sc_geom->consumer);
	pp = cp->provider;

	if (sc->sc_flags & G_ELI_FLAG_RO) {
		G_ELI_DEBUG(0, "WARNING: Metadata won't be erased on read-only "
		    "provider: %s.", pp->name);
	} else {
		u_char *sector;
		u_int i;
		int err;

		sector = malloc(pp->sectorsize, M_ELI, M_WAITOK);
		for (i = 0; i <= g_eli_overwrites; i++) {
			if (i == g_eli_overwrites)
				bzero(sector, pp->sectorsize);
			else
				arc4rand(sector, pp->sectorsize, 0);
			err = g_write_data(cp, pp->mediasize - pp->sectorsize,
			    sector, pp->sectorsize);
			if (err != 0) {
				G_ELI_DEBUG(0, "Cannot erase metadata on %s "
				    "(error=%d).", pp->name, err);
				if (error == 0)
					error = err;
			}
			/*
			 * Flush write cache so we don't overwrite data N times
			 * in cache and only once on disk.
			 */
			(void)g_io_flush(cp);
		}
		free(sector, M_ELI);
	}
	if (error == 0)
		G_ELI_DEBUG(0, "%s has been killed.", pp->name);
	g_eli_destroy(sc, TRUE);
	return (error);
}
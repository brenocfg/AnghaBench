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
struct g_eli_metadata {int md_keys; struct g_eli_metadata* md_mkeys; } ;
typedef  struct g_eli_metadata u_char ;
struct gctl_req {int dummy; } ;
struct g_provider {int sectorsize; int name; scalar_t__ mediasize; } ;
struct g_eli_softc {int sc_flags; int sc_nkey; TYPE_1__* sc_geom; } ;
struct g_consumer {struct g_provider* provider; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  md ;
typedef  int intmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,int,...) ; 
 int G_ELI_FLAG_RO ; 
 int G_ELI_MAXMKEYS ; 
 int G_ELI_MKEYLEN ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ELI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  arc4rand (struct g_eli_metadata*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eli_metadata_encode (struct g_eli_metadata*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  explicit_bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  free (struct g_eli_metadata*,int /*<<< orphan*/ ) ; 
 struct g_eli_softc* g_eli_find_device (struct g_class*,char const*) ; 
 scalar_t__ g_eli_overwrites ; 
 int g_eli_read_metadata (struct g_class*,struct g_provider*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  g_io_flush (struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int g_write_data (struct g_consumer*,scalar_t__,struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 struct g_eli_metadata* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_eli_ctl_delkey(struct gctl_req *req, struct g_class *mp)
{
	struct g_eli_softc *sc;
	struct g_eli_metadata md;
	struct g_provider *pp;
	struct g_consumer *cp;
	const char *name;
	u_char *mkeydst, *sector;
	intmax_t *valp;
	size_t keysize;
	int error, nkey, *all, *force;
	u_int i;

	g_topology_assert();

	nkey = 0;	/* fixes causeless gcc warning */

	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 0);
		return;
	}
	sc = g_eli_find_device(mp, name);
	if (sc == NULL) {
		gctl_error(req, "Provider %s is invalid.", name);
		return;
	}
	if (sc->sc_flags & G_ELI_FLAG_RO) {
		gctl_error(req, "Cannot delete keys for read-only provider.");
		return;
	}
	cp = LIST_FIRST(&sc->sc_geom->consumer);
	pp = cp->provider;

	error = g_eli_read_metadata(mp, pp, &md);
	if (error != 0) {
		gctl_error(req, "Cannot read metadata from %s (error=%d).",
		    name, error);
		return;
	}

	all = gctl_get_paraml(req, "all", sizeof(*all));
	if (all == NULL) {
		gctl_error(req, "No '%s' argument.", "all");
		return;
	}

	if (*all) {
		mkeydst = md.md_mkeys;
		keysize = sizeof(md.md_mkeys);
	} else {
		force = gctl_get_paraml(req, "force", sizeof(*force));
		if (force == NULL) {
			gctl_error(req, "No '%s' argument.", "force");
			return;
		}

		valp = gctl_get_paraml(req, "keyno", sizeof(*valp));
		if (valp == NULL) {
			gctl_error(req, "No '%s' argument.", "keyno");
			return;
		}
		if (*valp != -1)
			nkey = *valp;
		else
			nkey = sc->sc_nkey;
		if (nkey < 0 || nkey >= G_ELI_MAXMKEYS) {
			gctl_error(req, "Invalid '%s' argument.", "keyno");
			return;
		}
		if (!(md.md_keys & (1 << nkey)) && !*force) {
			gctl_error(req, "Master Key %u is not set.", nkey);
			return;
		}
		md.md_keys &= ~(1 << nkey);
		if (md.md_keys == 0 && !*force) {
			gctl_error(req, "This is the last Master Key. Use '-f' "
			    "flag if you really want to remove it.");
			return;
		}
		mkeydst = md.md_mkeys + nkey * G_ELI_MKEYLEN;
		keysize = G_ELI_MKEYLEN;
	}

	sector = malloc(pp->sectorsize, M_ELI, M_WAITOK | M_ZERO);
	for (i = 0; i <= g_eli_overwrites; i++) {
		if (i == g_eli_overwrites)
			explicit_bzero(mkeydst, keysize);
		else
			arc4rand(mkeydst, keysize, 0);
		/* Store metadata with destroyed key. */
		eli_metadata_encode(&md, sector);
		error = g_write_data(cp, pp->mediasize - pp->sectorsize, sector,
		    pp->sectorsize);
		if (error != 0) {
			G_ELI_DEBUG(0, "Cannot store metadata on %s "
			    "(error=%d).", pp->name, error);
		}
		/*
		 * Flush write cache so we don't overwrite data N times in cache
		 * and only once on disk.
		 */
		(void)g_io_flush(cp);
	}
	explicit_bzero(&md, sizeof(md));
	explicit_bzero(sector, pp->sectorsize);
	free(sector, M_ELI);
	if (*all)
		G_ELI_DEBUG(1, "All keys removed from %s.", pp->name);
	else
		G_ELI_DEBUG(1, "Key %d removed from %s.", nkey, pp->name);
}
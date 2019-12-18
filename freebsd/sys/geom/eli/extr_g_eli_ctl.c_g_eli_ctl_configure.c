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
typedef  int u_int ;
struct g_eli_metadata {int md_flags; } ;
typedef  struct g_eli_metadata u_char ;
struct gctl_req {int dummy; } ;
struct g_provider {int sectorsize; scalar_t__ mediasize; } ;
struct g_eli_softc {int sc_flags; TYPE_1__* sc_geom; } ;
struct g_consumer {struct g_provider* provider; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  md ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,char const*) ; 
 int G_ELI_FLAG_AUTORESIZE ; 
 int G_ELI_FLAG_BOOT ; 
 int G_ELI_FLAG_GELIBOOT ; 
 int G_ELI_FLAG_GELIDISPLAYPASS ; 
 int G_ELI_FLAG_NODELETE ; 
 int G_ELI_FLAG_ONETIME ; 
 int G_ELI_FLAG_RO ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ELI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  eli_metadata_encode (struct g_eli_metadata*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  explicit_bzero (struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  free (struct g_eli_metadata*,int /*<<< orphan*/ ) ; 
 struct g_eli_softc* g_eli_find_device (struct g_class*,char const*) ; 
 int g_eli_read_metadata (struct g_class*,struct g_provider*,struct g_eli_metadata*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int g_write_data (struct g_consumer*,scalar_t__,struct g_eli_metadata*,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 struct g_eli_metadata* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
g_eli_ctl_configure(struct gctl_req *req, struct g_class *mp)
{
	struct g_eli_softc *sc;
	struct g_eli_metadata md;
	struct g_provider *pp;
	struct g_consumer *cp;
	char param[16];
	const char *prov;
	u_char *sector;
	int *nargs, *boot, *noboot, *trim, *notrim, *geliboot, *nogeliboot;
	int *displaypass, *nodisplaypass, *autoresize, *noautoresize;
	int zero, error, changed;
	u_int i;

	g_topology_assert();

	changed = 0;
	zero = 0;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument.", "nargs");
		return;
	}
	if (*nargs <= 0) {
		gctl_error(req, "Missing device(s).");
		return;
	}

	boot = gctl_get_paraml(req, "boot", sizeof(*boot));
	if (boot == NULL)
		boot = &zero;
	noboot = gctl_get_paraml(req, "noboot", sizeof(*noboot));
	if (noboot == NULL)
		noboot = &zero;
	if (*boot && *noboot) {
		gctl_error(req, "Options -b and -B are mutually exclusive.");
		return;
	}
	if (*boot || *noboot)
		changed = 1;

	trim = gctl_get_paraml(req, "trim", sizeof(*trim));
	if (trim == NULL)
		trim = &zero;
	notrim = gctl_get_paraml(req, "notrim", sizeof(*notrim));
	if (notrim == NULL)
		notrim = &zero;
	if (*trim && *notrim) {
		gctl_error(req, "Options -t and -T are mutually exclusive.");
		return;
	}
	if (*trim || *notrim)
		changed = 1;

	geliboot = gctl_get_paraml(req, "geliboot", sizeof(*geliboot));
	if (geliboot == NULL)
		geliboot = &zero;
	nogeliboot = gctl_get_paraml(req, "nogeliboot", sizeof(*nogeliboot));
	if (nogeliboot == NULL)
		nogeliboot = &zero;
	if (*geliboot && *nogeliboot) {
		gctl_error(req, "Options -g and -G are mutually exclusive.");
		return;
	}
	if (*geliboot || *nogeliboot)
		changed = 1;

	displaypass = gctl_get_paraml(req, "displaypass", sizeof(*displaypass));
	if (displaypass == NULL)
		displaypass = &zero;
	nodisplaypass = gctl_get_paraml(req, "nodisplaypass", sizeof(*nodisplaypass));
	if (nodisplaypass == NULL)
		nodisplaypass = &zero;
	if (*displaypass && *nodisplaypass) {
		gctl_error(req, "Options -d and -D are mutually exclusive.");
		return;
	}
	if (*displaypass || *nodisplaypass)
		changed = 1;

	autoresize = gctl_get_paraml(req, "autoresize", sizeof(*autoresize));
	if (autoresize == NULL)
		autoresize = &zero;
	noautoresize = gctl_get_paraml(req, "noautoresize",
	    sizeof(*noautoresize));
	if (noautoresize == NULL)
		noautoresize = &zero;
	if (*autoresize && *noautoresize) {
		gctl_error(req, "Options -r and -R are mutually exclusive.");
		return;
	}
	if (*autoresize || *noautoresize)
		changed = 1;

	if (!changed) {
		gctl_error(req, "No option given.");
		return;
	}

	for (i = 0; i < *nargs; i++) {
		snprintf(param, sizeof(param), "arg%d", i);
		prov = gctl_get_asciiparam(req, param);
		if (prov == NULL) {
			gctl_error(req, "No 'arg%d' argument.", i);
			return;
		}
		sc = g_eli_find_device(mp, prov);
		if (sc == NULL) {
			/*
			 * We ignore not attached providers, userland part will
			 * take care of them.
			 */
			G_ELI_DEBUG(1, "Skipping configuration of not attached "
			    "provider %s.", prov);
			continue;
		}
		if (sc->sc_flags & G_ELI_FLAG_RO) {
			gctl_error(req, "Cannot change configuration of "
			    "read-only provider %s.", prov);
			continue;
		}

		if (*boot && (sc->sc_flags & G_ELI_FLAG_BOOT)) {
			G_ELI_DEBUG(1, "BOOT flag already configured for %s.",
			    prov);
			continue;
		} else if (*noboot && !(sc->sc_flags & G_ELI_FLAG_BOOT)) {
			G_ELI_DEBUG(1, "BOOT flag not configured for %s.",
			    prov);
			continue;
		}

		if (*notrim && (sc->sc_flags & G_ELI_FLAG_NODELETE)) {
			G_ELI_DEBUG(1, "TRIM disable flag already configured for %s.",
			    prov);
			continue;
		} else if (*trim && !(sc->sc_flags & G_ELI_FLAG_NODELETE)) {
			G_ELI_DEBUG(1, "TRIM disable flag not configured for %s.",
			    prov);
			continue;
		}

		if (*geliboot && (sc->sc_flags & G_ELI_FLAG_GELIBOOT)) {
			G_ELI_DEBUG(1, "GELIBOOT flag already configured for %s.",
			    prov);
			continue;
		} else if (*nogeliboot && !(sc->sc_flags & G_ELI_FLAG_GELIBOOT)) {
			G_ELI_DEBUG(1, "GELIBOOT flag not configured for %s.",
			    prov);
			continue;
		}

		if (*displaypass && (sc->sc_flags & G_ELI_FLAG_GELIDISPLAYPASS)) {
			G_ELI_DEBUG(1, "GELIDISPLAYPASS flag already configured for %s.",
			    prov);
			continue;
		} else if (*nodisplaypass &&
		    !(sc->sc_flags & G_ELI_FLAG_GELIDISPLAYPASS)) {
			G_ELI_DEBUG(1, "GELIDISPLAYPASS flag not configured for %s.",
			    prov);
			continue;
		}

		if (*autoresize && (sc->sc_flags & G_ELI_FLAG_AUTORESIZE)) {
			G_ELI_DEBUG(1, "AUTORESIZE flag already configured for %s.",
			    prov);
			continue;
		} else if (*noautoresize &&
		    !(sc->sc_flags & G_ELI_FLAG_AUTORESIZE)) {
			G_ELI_DEBUG(1, "AUTORESIZE flag not configured for %s.",
			    prov);
			continue;
		}

		if (!(sc->sc_flags & G_ELI_FLAG_ONETIME)) {
			/*
			 * ONETIME providers don't write metadata to
			 * disk, so don't try reading it.  This means
			 * we're bit-flipping uninitialized memory in md
			 * below, but that's OK; we don't do anything
			 * with it later.
			 */
			cp = LIST_FIRST(&sc->sc_geom->consumer);
			pp = cp->provider;
			error = g_eli_read_metadata(mp, pp, &md);
			if (error != 0) {
			    gctl_error(req,
				"Cannot read metadata from %s (error=%d).",
				prov, error);
			    continue;
			}
		}

		if (*boot) {
			md.md_flags |= G_ELI_FLAG_BOOT;
			sc->sc_flags |= G_ELI_FLAG_BOOT;
		} else if (*noboot) {
			md.md_flags &= ~G_ELI_FLAG_BOOT;
			sc->sc_flags &= ~G_ELI_FLAG_BOOT;
		}

		if (*notrim) {
			md.md_flags |= G_ELI_FLAG_NODELETE;
			sc->sc_flags |= G_ELI_FLAG_NODELETE;
		} else if (*trim) {
			md.md_flags &= ~G_ELI_FLAG_NODELETE;
			sc->sc_flags &= ~G_ELI_FLAG_NODELETE;
		}

		if (*geliboot) {
			md.md_flags |= G_ELI_FLAG_GELIBOOT;
			sc->sc_flags |= G_ELI_FLAG_GELIBOOT;
		} else if (*nogeliboot) {
			md.md_flags &= ~G_ELI_FLAG_GELIBOOT;
			sc->sc_flags &= ~G_ELI_FLAG_GELIBOOT;
		}

		if (*displaypass) {
			md.md_flags |= G_ELI_FLAG_GELIDISPLAYPASS;
			sc->sc_flags |= G_ELI_FLAG_GELIDISPLAYPASS;
		} else if (*nodisplaypass) {
			md.md_flags &= ~G_ELI_FLAG_GELIDISPLAYPASS;
			sc->sc_flags &= ~G_ELI_FLAG_GELIDISPLAYPASS;
		}

		if (*autoresize) {
			md.md_flags |= G_ELI_FLAG_AUTORESIZE;
			sc->sc_flags |= G_ELI_FLAG_AUTORESIZE;
		} else if (*noautoresize) {
			md.md_flags &= ~G_ELI_FLAG_AUTORESIZE;
			sc->sc_flags &= ~G_ELI_FLAG_AUTORESIZE;
		}

		if (sc->sc_flags & G_ELI_FLAG_ONETIME) {
			/* There's no metadata on disk so we are done here. */
			continue;
		}

		sector = malloc(pp->sectorsize, M_ELI, M_WAITOK | M_ZERO);
		eli_metadata_encode(&md, sector);
		error = g_write_data(cp, pp->mediasize - pp->sectorsize, sector,
		    pp->sectorsize);
		if (error != 0) {
			gctl_error(req,
			    "Cannot store metadata on %s (error=%d).",
			    prov, error);
		}
		explicit_bzero(&md, sizeof(md));
		explicit_bzero(sector, pp->sectorsize);
		free(sector, M_ELI);
	}
}
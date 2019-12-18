#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct gctl_req {int dummy; } ;
struct g_consumer {TYPE_2__* provider; } ;
struct g_class {int dummy; } ;
struct g_cache_softc {scalar_t__ sc_type; TYPE_1__* sc_geom; scalar_t__ sc_bsize; scalar_t__ sc_maxent; } ;
struct g_cache_metadata {int /*<<< orphan*/  md_provsize; scalar_t__ md_bsize; scalar_t__ md_size; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; int /*<<< orphan*/  md_name; } ;
typedef  scalar_t__ intmax_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  mediasize; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_CACHE_DEBUG (int,char*,char const*,...) ; 
 char const* G_CACHE_MAGIC ; 
 scalar_t__ G_CACHE_TYPE_AUTOMATIC ; 
 int /*<<< orphan*/  G_CACHE_VERSION ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct g_cache_softc* g_cache_find_device (struct g_class*,char const*) ; 
 int g_cache_write_metadata (struct g_consumer*,struct g_cache_metadata*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 void* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
g_cache_ctl_configure(struct gctl_req *req, struct g_class *mp)
{
	struct g_cache_metadata md;
	struct g_cache_softc *sc;
	struct g_consumer *cp;
	intmax_t *bsize, *size;
	const char *name;
	int error, *nargs;

	g_topology_assert();

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument", "nargs");
		return;
	}
	if (*nargs != 1) {
		gctl_error(req, "Missing device.");
		return;
	}

	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg0' argument");
		return;
	}
	sc = g_cache_find_device(mp, name);
	if (sc == NULL) {
		G_CACHE_DEBUG(1, "Device %s is invalid.", name);
		gctl_error(req, "Device %s is invalid.", name);
		return;
	}

	size = gctl_get_paraml(req, "size", sizeof(*size));
	if (size == NULL) {
		gctl_error(req, "No '%s' argument", "size");
		return;
	}
	if ((u_int)*size != 0 && (u_int)*size < 100) {
		gctl_error(req, "Invalid '%s' argument", "size");
		return;
	}
	if ((u_int)*size != 0)
		sc->sc_maxent = (u_int)*size;

	bsize = gctl_get_paraml(req, "blocksize", sizeof(*bsize));
	if (bsize == NULL) {
		gctl_error(req, "No '%s' argument", "blocksize");
		return;
	}
	if (*bsize < 0) {
		gctl_error(req, "Invalid '%s' argument", "blocksize");
		return;
	}

	if (sc->sc_type != G_CACHE_TYPE_AUTOMATIC)
		return;

	strlcpy(md.md_name, name, sizeof(md.md_name));
	strlcpy(md.md_magic, G_CACHE_MAGIC, sizeof(md.md_magic));
	md.md_version = G_CACHE_VERSION;
	if ((u_int)*size != 0)
		md.md_size = (u_int)*size;
	else
		md.md_size = sc->sc_maxent;
	if ((u_int)*bsize != 0)
		md.md_bsize = (u_int)*bsize;
	else
		md.md_bsize = sc->sc_bsize;
	cp = LIST_FIRST(&sc->sc_geom->consumer);
	md.md_provsize = cp->provider->mediasize;
	error = g_cache_write_metadata(cp, &md);
	if (error == 0)
		G_CACHE_DEBUG(2, "Metadata on %s updated.", cp->provider->name);
	else
		G_CACHE_DEBUG(0, "Cannot update metadata on %s (error=%d).",
		    cp->provider->name, error);
}
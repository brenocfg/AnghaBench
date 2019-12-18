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
typedef  int /*<<< orphan*/  u_char ;
struct gctl_req {int dummy; } ;
struct g_raid3_softc {size_t sc_ndisks; int sc_sectorsize; int sc_mediasize; int /*<<< orphan*/  sc_lock; struct g_raid3_disk* sc_disks; } ;
struct g_raid3_metadata {int md_provsize; int /*<<< orphan*/  md_provider; scalar_t__ md_dflags; scalar_t__ md_syncid; } ;
struct g_raid3_disk {scalar_t__ d_state; } ;
struct g_provider {size_t name; int sectorsize; int mediasize; } ;
struct g_geom {int /*<<< orphan*/  orphan; } ;
struct g_consumer {scalar_t__ acw; int /*<<< orphan*/ * provider; } ;
struct g_class {int dummy; } ;
typedef  int off_t ;
typedef  size_t intmax_t ;

/* Variables and functions */
 scalar_t__ G_RAID3_DISK_STATE_NODISK ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int g_access (struct g_consumer*,int /*<<< orphan*/ ,int,int) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_malloc (int,int /*<<< orphan*/ ) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_raid3_ctl_insert_orphan ; 
 int /*<<< orphan*/  g_raid3_fill_metadata (struct g_raid3_disk*,struct g_raid3_metadata*) ; 
 struct g_raid3_softc* g_raid3_find_device (struct g_class*,char const*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int g_write_data (struct g_consumer*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int /*<<< orphan*/ * gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 void* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  raid3_metadata_encode (struct g_raid3_metadata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid3_ctl_insert(struct gctl_req *req, struct g_class *mp)
{
	struct g_raid3_metadata md;
	struct g_raid3_softc *sc;
	struct g_raid3_disk *disk;
	struct g_geom *gp;
	struct g_provider *pp;
	struct g_consumer *cp;
	const char *name;
	u_char *sector;
	off_t compsize;
	intmax_t *no;
	int *hardcode, *nargs, error, autono;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument.", "nargs");
		return;
	}
	if (*nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}
	hardcode = gctl_get_paraml(req, "hardcode", sizeof(*hardcode));
	if (hardcode == NULL) {
		gctl_error(req, "No '%s' argument.", "hardcode");
		return;
	}
	name = gctl_get_asciiparam(req, "arg1");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 1);
		return;
	}
	if (gctl_get_param(req, "number", NULL) != NULL)
		no = gctl_get_paraml(req, "number", sizeof(*no));
	else
		no = NULL;
	if (strncmp(name, "/dev/", 5) == 0)
		name += 5;
	g_topology_lock();
	pp = g_provider_by_name(name);
	if (pp == NULL) {
		g_topology_unlock();
		gctl_error(req, "Invalid provider.");
		return;
	}
	gp = g_new_geomf(mp, "raid3:insert");
	gp->orphan = g_raid3_ctl_insert_orphan;
	cp = g_new_consumer(gp);
	error = g_attach(cp, pp);
	if (error != 0) {
		g_topology_unlock();
		gctl_error(req, "Cannot attach to %s.", pp->name);
		goto end;
	}
	error = g_access(cp, 0, 1, 1);
	if (error != 0) {
		g_topology_unlock();
		gctl_error(req, "Cannot access %s.", pp->name);
		goto end;
	}
	g_topology_unlock();
	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 0);
		goto end;
	}
	sc = g_raid3_find_device(mp, name);
	if (sc == NULL) {
		gctl_error(req, "No such device: %s.", name);
		goto end;
	}
	if (no != NULL) {
		if (*no < 0 || *no >= sc->sc_ndisks) {
			sx_xunlock(&sc->sc_lock);
			gctl_error(req, "Invalid component number.");
			goto end;
		}
		disk = &sc->sc_disks[*no];
		if (disk->d_state != G_RAID3_DISK_STATE_NODISK) {
			sx_xunlock(&sc->sc_lock);
			gctl_error(req, "Component %jd is already connected.",
			    *no);
			goto end;
		}
	} else {
		disk = NULL;
		for (autono = 0; autono < sc->sc_ndisks && disk == NULL; autono++)
			if (sc->sc_disks[autono].d_state ==
			    G_RAID3_DISK_STATE_NODISK)
				disk = &sc->sc_disks[autono];
		if (disk == NULL) {
			sx_xunlock(&sc->sc_lock);
			gctl_error(req, "No disconnected components.");
			goto end;
		}
	}
	if (((sc->sc_sectorsize / (sc->sc_ndisks - 1)) % pp->sectorsize) != 0) {
		sx_xunlock(&sc->sc_lock);
		gctl_error(req,
		    "Cannot insert provider %s, because of its sector size.",
		    pp->name);
		goto end;
	}
	compsize = sc->sc_mediasize / (sc->sc_ndisks - 1);
	if (compsize > pp->mediasize - pp->sectorsize) {
		sx_xunlock(&sc->sc_lock);
		gctl_error(req, "Provider %s too small.", pp->name);
		goto end;
	}
	if (compsize < pp->mediasize - pp->sectorsize) {
		gctl_error(req,
		    "warning: %s: only %jd bytes from %jd bytes used.",
		    pp->name, (intmax_t)compsize,
		    (intmax_t)(pp->mediasize - pp->sectorsize));
	}
	g_raid3_fill_metadata(disk, &md);
	sx_xunlock(&sc->sc_lock);
	md.md_syncid = 0;
	md.md_dflags = 0;
	if (*hardcode)
		strlcpy(md.md_provider, pp->name, sizeof(md.md_provider));
	else
		bzero(md.md_provider, sizeof(md.md_provider));
	md.md_provsize = pp->mediasize;
	sector = g_malloc(pp->sectorsize, M_WAITOK);
	raid3_metadata_encode(&md, sector);
	error = g_write_data(cp, pp->mediasize - pp->sectorsize, sector,
	    pp->sectorsize);
	g_free(sector);
	if (error != 0)
		gctl_error(req, "Cannot store metadata on %s.", pp->name);
end:
	g_topology_lock();
	if (cp->acw > 0)
		g_access(cp, 0, -1, -1);
	if (cp->provider != NULL)
		g_detach(cp);
	g_destroy_consumer(cp);
	g_destroy_geom(gp);
	g_topology_unlock();
}
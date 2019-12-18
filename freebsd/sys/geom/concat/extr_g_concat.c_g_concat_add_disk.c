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
typedef  size_t u_int ;
struct g_provider {int /*<<< orphan*/  name; } ;
struct g_geom {int /*<<< orphan*/  consumer; } ;
struct g_consumer {int flags; int /*<<< orphan*/  ace; int /*<<< orphan*/  acw; int /*<<< orphan*/  acr; struct g_concat_disk* private; } ;
struct g_concat_softc {size_t sc_ndisks; scalar_t__ sc_type; scalar_t__ sc_id; int /*<<< orphan*/  sc_name; struct g_geom* sc_geom; struct g_concat_disk* sc_disks; } ;
struct g_concat_metadata {scalar_t__ md_id; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_magic; } ;
struct g_concat_disk {scalar_t__ d_removed; scalar_t__ d_end; scalar_t__ d_start; struct g_concat_softc* d_softc; struct g_consumer* d_consumer; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int G_CF_DIRECT_RECEIVE ; 
 int G_CF_DIRECT_SEND ; 
 int /*<<< orphan*/  G_CONCAT_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_CONCAT_MAGIC ; 
 scalar_t__ G_CONCAT_TYPE_AUTOMATIC ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int g_access (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_concat_check_and_run (struct g_concat_softc*) ; 
 int g_concat_read_metadata (struct g_consumer*,struct g_concat_metadata*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_concat_add_disk(struct g_concat_softc *sc, struct g_provider *pp, u_int no)
{
	struct g_concat_disk *disk;
	struct g_consumer *cp, *fcp;
	struct g_geom *gp;
	int error;

	g_topology_assert();
	/* Metadata corrupted? */
	if (no >= sc->sc_ndisks)
		return (EINVAL);

	disk = &sc->sc_disks[no];
	/* Check if disk is not already attached. */
	if (disk->d_consumer != NULL)
		return (EEXIST);

	gp = sc->sc_geom;
	fcp = LIST_FIRST(&gp->consumer);

	cp = g_new_consumer(gp);
	cp->flags |= G_CF_DIRECT_SEND | G_CF_DIRECT_RECEIVE;
	error = g_attach(cp, pp);
	if (error != 0) {
		g_destroy_consumer(cp);
		return (error);
	}

	if (fcp != NULL && (fcp->acr > 0 || fcp->acw > 0 || fcp->ace > 0)) {
		error = g_access(cp, fcp->acr, fcp->acw, fcp->ace);
		if (error != 0) {
			g_detach(cp);
			g_destroy_consumer(cp);
			return (error);
		}
	}
	if (sc->sc_type == G_CONCAT_TYPE_AUTOMATIC) {
		struct g_concat_metadata md;

		/* Re-read metadata. */
		error = g_concat_read_metadata(cp, &md);
		if (error != 0)
			goto fail;

		if (strcmp(md.md_magic, G_CONCAT_MAGIC) != 0 ||
		    strcmp(md.md_name, sc->sc_name) != 0 ||
		    md.md_id != sc->sc_id) {
			G_CONCAT_DEBUG(0, "Metadata on %s changed.", pp->name);
			goto fail;
		}
	}

	cp->private = disk;
	disk->d_consumer = cp;
	disk->d_softc = sc;
	disk->d_start = 0;	/* not yet */
	disk->d_end = 0;	/* not yet */
	disk->d_removed = 0;

	G_CONCAT_DEBUG(0, "Disk %s attached to %s.", pp->name, sc->sc_name);

	g_concat_check_and_run(sc);

	return (0);
fail:
	if (fcp != NULL && (fcp->acr > 0 || fcp->acw > 0 || fcp->ace > 0))
		g_access(cp, -fcp->acr, -fcp->acw, -fcp->ace);
	g_detach(cp);
	g_destroy_consumer(cp);
	return (error);
}
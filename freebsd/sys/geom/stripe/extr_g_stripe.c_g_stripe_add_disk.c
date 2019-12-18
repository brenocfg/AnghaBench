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
struct g_stripe_softc {size_t sc_ndisks; scalar_t__ sc_type; scalar_t__ sc_id; int /*<<< orphan*/  sc_name; struct g_consumer** sc_disks; struct g_geom* sc_geom; } ;
struct g_stripe_metadata {scalar_t__ md_id; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_magic; } ;
struct g_provider {int /*<<< orphan*/  name; } ;
struct g_geom {int /*<<< orphan*/  consumer; } ;
struct g_consumer {int flags; size_t index; int /*<<< orphan*/  ace; int /*<<< orphan*/  acw; int /*<<< orphan*/  acr; int /*<<< orphan*/ * private; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int G_CF_DIRECT_RECEIVE ; 
 int G_CF_DIRECT_SEND ; 
 int /*<<< orphan*/  G_STRIPE_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_STRIPE_MAGIC ; 
 scalar_t__ G_STRIPE_TYPE_AUTOMATIC ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int g_access (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 int /*<<< orphan*/  g_stripe_check_and_run (struct g_stripe_softc*) ; 
 int g_stripe_read_metadata (struct g_consumer*,struct g_stripe_metadata*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_stripe_add_disk(struct g_stripe_softc *sc, struct g_provider *pp, u_int no)
{
	struct g_consumer *cp, *fcp;
	struct g_geom *gp;
	int error;

	g_topology_assert();
	/* Metadata corrupted? */
	if (no >= sc->sc_ndisks)
		return (EINVAL);

	/* Check if disk is not already attached. */
	if (sc->sc_disks[no] != NULL)
		return (EEXIST);

	gp = sc->sc_geom;
	fcp = LIST_FIRST(&gp->consumer);

	cp = g_new_consumer(gp);
	cp->flags |= G_CF_DIRECT_SEND | G_CF_DIRECT_RECEIVE;
	cp->private = NULL;
	cp->index = no;
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
	if (sc->sc_type == G_STRIPE_TYPE_AUTOMATIC) {
		struct g_stripe_metadata md;

		/* Reread metadata. */
		error = g_stripe_read_metadata(cp, &md);
		if (error != 0)
			goto fail;

		if (strcmp(md.md_magic, G_STRIPE_MAGIC) != 0 ||
		    strcmp(md.md_name, sc->sc_name) != 0 ||
		    md.md_id != sc->sc_id) {
			G_STRIPE_DEBUG(0, "Metadata on %s changed.", pp->name);
			goto fail;
		}
	}

	sc->sc_disks[no] = cp;
	G_STRIPE_DEBUG(0, "Disk %s attached to %s.", pp->name, sc->sc_name);
	g_stripe_check_and_run(sc);

	return (0);
fail:
	if (fcp != NULL && (fcp->acr > 0 || fcp->acw > 0 || fcp->ace > 0))
		g_access(cp, -fcp->acr, -fcp->acw, -fcp->ace);
	g_detach(cp);
	g_destroy_consumer(cp);
	return (error);
}
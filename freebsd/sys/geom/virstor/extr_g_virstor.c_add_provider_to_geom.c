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
struct g_virstor_softc {size_t n_components; struct g_geom* geom; struct g_virstor_component* components; } ;
struct g_virstor_metadata {size_t no; int /*<<< orphan*/  flags; int /*<<< orphan*/  chunk_reserved; int /*<<< orphan*/  chunk_next; int /*<<< orphan*/  chunk_count; } ;
struct g_virstor_component {size_t index; int /*<<< orphan*/  flags; int /*<<< orphan*/  chunk_reserved; int /*<<< orphan*/  chunk_next; int /*<<< orphan*/  chunk_count; struct g_virstor_softc* sc; struct g_consumer* gcons; } ;
struct g_provider {int /*<<< orphan*/  name; int /*<<< orphan*/  sectorsize; } ;
struct g_geom {int /*<<< orphan*/  name; int /*<<< orphan*/  consumer; } ;
struct g_consumer {scalar_t__ acr; scalar_t__ ace; struct g_virstor_component* private; scalar_t__ acw; TYPE_1__* provider; } ;
struct TYPE_2__ {int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LVL_DEBUG ; 
 int /*<<< orphan*/  LVL_ERROR ; 
 int g_access (struct g_consumer*,scalar_t__,scalar_t__,scalar_t__) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 int /*<<< orphan*/  virstor_check_and_run (struct g_virstor_softc*) ; 

__attribute__((used)) static int
add_provider_to_geom(struct g_virstor_softc *sc, struct g_provider *pp,
    struct g_virstor_metadata *md)
{
	struct g_virstor_component *component;
	struct g_consumer *cp, *fcp;
	struct g_geom *gp;
	int error;

	if (md->no >= sc->n_components)
		return (EINVAL);

	/* "Current" compontent */
	component = &(sc->components[md->no]);
	if (component->gcons != NULL)
		return (EEXIST);

	gp = sc->geom;
	fcp = LIST_FIRST(&gp->consumer);

	cp = g_new_consumer(gp);
	error = g_attach(cp, pp);

	if (error != 0) {
		g_destroy_consumer(cp);
		return (error);
	}

	if (fcp != NULL) {
		if (fcp->provider->sectorsize != pp->sectorsize) {
			/* TODO: this can be made to work */
			LOG_MSG(LVL_ERROR, "Provider %s of %s has invalid "
			    "sector size (%d)", pp->name, sc->geom->name,
			    pp->sectorsize);
			return (EINVAL);
		}
		if (fcp->acr > 0 || fcp->acw || fcp->ace > 0) {
			/* Replicate access permissions from first "live" consumer
			 * to the new one */
			error = g_access(cp, fcp->acr, fcp->acw, fcp->ace);
			if (error != 0) {
				g_detach(cp);
				g_destroy_consumer(cp);
				return (error);
			}
		}
	}

	/* Bring up a new component */
	cp->private = component;
	component->gcons = cp;
	component->sc = sc;
	component->index = md->no;
	component->chunk_count = md->chunk_count;
	component->chunk_next = md->chunk_next;
	component->chunk_reserved = md->chunk_reserved;
	component->flags = md->flags;

	LOG_MSG(LVL_DEBUG, "%s attached to %s", pp->name, sc->geom->name);

	virstor_check_and_run(sc);
	return (0);
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct gctl_req {int dummy; } ;
struct g_provider {char const* name; scalar_t__ sectorsize; scalar_t__ mediasize; } ;
struct g_multipath_softc {scalar_t__* sc_uuid; struct g_consumer* sc_active; } ;
struct g_geom {struct g_multipath_softc* softc; } ;
struct g_consumer {struct g_provider* provider; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int g_access (struct g_consumer*,int,int,int) ; 
 int /*<<< orphan*/ * g_malloc (scalar_t__,int) ; 
 int g_multipath_destroy (struct g_geom*) ; 
 struct g_geom* g_multipath_find_geom (struct g_class*,char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int g_write_data (struct g_consumer*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 

__attribute__((used)) static void
g_multipath_ctl_destroy(struct gctl_req *req, struct g_class *mp)
{
	struct g_geom *gp;
	struct g_multipath_softc *sc;
	struct g_consumer *cp;
	struct g_provider *pp;
	const char *name;
	uint8_t *buf;
	int error;

	g_topology_assert();

	name = gctl_get_asciiparam(req, "arg0");
        if (name == NULL) {
                gctl_error(req, "No 'arg0' argument");
                return;
        }
	gp = g_multipath_find_geom(mp, name);
	if (gp == NULL) {
		gctl_error(req, "Device %s is invalid", name);
		return;
	}
	sc = gp->softc;

	if (sc->sc_uuid[0] != 0 && sc->sc_active != NULL) {
		cp = sc->sc_active;
		pp = cp->provider;
		error = g_access(cp, 1, 1, 1);
		if (error != 0) {
			gctl_error(req, "Can't open %s (%d)", pp->name, error);
			goto destroy;
		}
		g_topology_unlock();
		buf = g_malloc(pp->sectorsize, M_WAITOK | M_ZERO);
		error = g_write_data(cp, pp->mediasize - pp->sectorsize,
		    buf, pp->sectorsize);
		g_topology_lock();
		g_access(cp, -1, -1, -1);
		if (error != 0)
			gctl_error(req, "Can't erase metadata on %s (%d)",
			    pp->name, error);
	}

destroy:
	error = g_multipath_destroy(gp);
	if (error != 0 && error != EINPROGRESS)
		gctl_error(req, "failed to destroy %s (err=%d)", name, error);
}
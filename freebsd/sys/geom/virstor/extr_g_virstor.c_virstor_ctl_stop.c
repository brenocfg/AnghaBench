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
struct gctl_req {int dummy; } ;
struct g_virstor_softc {TYPE_1__* geom; } ;
struct g_class {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LVL_ERROR ; 
 int /*<<< orphan*/  LVL_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  update_metadata (struct g_virstor_softc*) ; 
 struct g_virstor_softc* virstor_find_geom (struct g_class*,char const*) ; 
 int virstor_geom_destroy (struct g_virstor_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
virstor_ctl_stop(struct gctl_req *req, struct g_class *cp)
{
	int *force, *nargs;
	int i;

	nargs = gctl_get_paraml(req, "nargs", sizeof *nargs);
	if (nargs == NULL) {
		gctl_error(req, "Error fetching argument '%s'", "nargs");
		return;
	}
	if (*nargs < 1) {
		gctl_error(req, "Invalid number of arguments");
		return;
	}
	force = gctl_get_paraml(req, "force", sizeof *force);
	if (force == NULL) {
		gctl_error(req, "Error fetching argument '%s'", "force");
		return;
	}

	g_topology_lock();
	for (i = 0; i < *nargs; i++) {
		char param[8];
		const char *name;
		struct g_virstor_softc *sc;
		int error;

		sprintf(param, "arg%d", i);
		name = gctl_get_asciiparam(req, param);
		if (name == NULL) {
			gctl_error(req, "No 'arg%d' argument", i);
			g_topology_unlock();
			return;
		}
		sc = virstor_find_geom(cp, name);
		if (sc == NULL) {
			gctl_error(req, "Don't know anything about '%s'", name);
			g_topology_unlock();
			return;
		}

		LOG_MSG(LVL_INFO, "Stopping %s by the userland command",
		    sc->geom->name);
		update_metadata(sc);
		if ((error = virstor_geom_destroy(sc, TRUE, TRUE)) != 0) {
			LOG_MSG(LVL_ERROR, "Cannot destroy %s: %d",
			    sc->geom->name, error);
		}
	}
	g_topology_unlock();
}
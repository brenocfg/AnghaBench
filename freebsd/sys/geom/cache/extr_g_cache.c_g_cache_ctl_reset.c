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
struct gctl_req {int dummy; } ;
struct g_class {int dummy; } ;
struct g_cache_softc {scalar_t__ sc_wrotebytes; scalar_t__ sc_writes; scalar_t__ sc_cachefull; scalar_t__ sc_cachemisses; scalar_t__ sc_cachehits; scalar_t__ sc_cachereadbytes; scalar_t__ sc_cachereads; scalar_t__ sc_readbytes; scalar_t__ sc_reads; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  G_CACHE_DEBUG (int,char*,char const*) ; 
 struct g_cache_softc* g_cache_find_device (struct g_class*,char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
g_cache_ctl_reset(struct gctl_req *req, struct g_class *mp)
{
	struct g_cache_softc *sc;
	const char *name;
	char param[16];
	int i, *nargs;

	g_topology_assert();

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument", "nargs");
		return;
	}
	if (*nargs <= 0) {
		gctl_error(req, "Missing device(s).");
		return;
	}

	for (i = 0; i < *nargs; i++) {
		snprintf(param, sizeof(param), "arg%d", i);
		name = gctl_get_asciiparam(req, param);
		if (name == NULL) {
			gctl_error(req, "No 'arg%d' argument", i);
			return;
		}
		sc = g_cache_find_device(mp, name);
		if (sc == NULL) {
			G_CACHE_DEBUG(1, "Device %s is invalid.", name);
			gctl_error(req, "Device %s is invalid.", name);
			return;
		}
		sc->sc_reads = 0;
		sc->sc_readbytes = 0;
		sc->sc_cachereads = 0;
		sc->sc_cachereadbytes = 0;
		sc->sc_cachehits = 0;
		sc->sc_cachemisses = 0;
		sc->sc_cachefull = 0;
		sc->sc_writes = 0;
		sc->sc_wrotebytes = 0;
	}
}
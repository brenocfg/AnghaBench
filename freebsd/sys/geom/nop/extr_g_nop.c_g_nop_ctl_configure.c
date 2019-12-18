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
typedef  void* u_int ;
struct gctl_req {int dummy; } ;
struct g_provider {TYPE_1__* geom; } ;
struct g_nop_softc {int sc_error; void* sc_count_until_fail; void* sc_delaymsec; void* sc_wdelayprob; void* sc_rdelayprob; void* sc_wfailprob; void* sc_rfailprob; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int intmax_t ;
struct TYPE_2__ {struct g_nop_softc* softc; struct g_class* class; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_NOP_DEBUG (int,char*,char const*) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int* gctl_get_paraml_opt (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_nop_ctl_configure(struct gctl_req *req, struct g_class *mp)
{
	struct g_nop_softc *sc;
	struct g_provider *pp;
	intmax_t *val, delaymsec, error, rdelayprob, rfailprob, wdelayprob,
	    wfailprob, count_until_fail;
	const char *name;
	char param[16];
	int i, *nargs;

	g_topology_assert();

	count_until_fail = -1;
	delaymsec = -1;
	error = -1;
	rdelayprob = -1;
	rfailprob = -1;
	wdelayprob = -1;
	wfailprob = -1;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument", "nargs");
		return;
	}
	if (*nargs <= 0) {
		gctl_error(req, "Missing device(s).");
		return;
	}
	val = gctl_get_paraml_opt(req, "error", sizeof(*val));
	if (val != NULL) {
		error = *val;
	}
	val = gctl_get_paraml_opt(req, "count_until_fail", sizeof(*val));
	if (val != NULL) {
		count_until_fail = *val;
	}
	val = gctl_get_paraml_opt(req, "rfailprob", sizeof(*val));
	if (val != NULL) {
		rfailprob = *val;
		if (rfailprob < -1 || rfailprob > 100) {
			gctl_error(req, "Invalid '%s' argument", "rfailprob");
			return;
		}
	}
	val = gctl_get_paraml_opt(req, "wfailprob", sizeof(*val));
	if (val != NULL) {
		wfailprob = *val;
		if (wfailprob < -1 || wfailprob > 100) {
			gctl_error(req, "Invalid '%s' argument", "wfailprob");
			return;
		}
	}
	val = gctl_get_paraml_opt(req, "delaymsec", sizeof(*val));
	if (val != NULL) {
		delaymsec = *val;
		if (delaymsec < 1 && delaymsec != -1) {
			gctl_error(req, "Invalid '%s' argument", "delaymsec");
			return;
		}
	}
	val = gctl_get_paraml_opt(req, "rdelayprob", sizeof(*val));
	if (val != NULL) {
		rdelayprob = *val;
		if (rdelayprob < -1 || rdelayprob > 100) {
			gctl_error(req, "Invalid '%s' argument", "rdelayprob");
			return;
		}
	}
	val = gctl_get_paraml_opt(req, "wdelayprob", sizeof(*val));
	if (val != NULL) {
		wdelayprob = *val;
		if (wdelayprob < -1 || wdelayprob > 100) {
			gctl_error(req, "Invalid '%s' argument", "wdelayprob");
			return;
		}
	}

	for (i = 0; i < *nargs; i++) {
		snprintf(param, sizeof(param), "arg%d", i);
		name = gctl_get_asciiparam(req, param);
		if (name == NULL) {
			gctl_error(req, "No 'arg%d' argument", i);
			return;
		}
		if (strncmp(name, "/dev/", strlen("/dev/")) == 0)
			name += strlen("/dev/");
		pp = g_provider_by_name(name);
		if (pp == NULL || pp->geom->class != mp) {
			G_NOP_DEBUG(1, "Provider %s is invalid.", name);
			gctl_error(req, "Provider %s is invalid.", name);
			return;
		}
		sc = pp->geom->softc;
		if (error != -1)
			sc->sc_error = (int)error;
		if (rfailprob != -1)
			sc->sc_rfailprob = (u_int)rfailprob;
		if (wfailprob != -1)
			sc->sc_wfailprob = (u_int)wfailprob;
		if (rdelayprob != -1)
			sc->sc_rdelayprob = (u_int)rdelayprob;
		if (wdelayprob != -1)
			sc->sc_wdelayprob = (u_int)wdelayprob;
		if (delaymsec != -1)
			sc->sc_delaymsec = (u_int)delaymsec;
		if (count_until_fail != -1)
			sc->sc_count_until_fail = (u_int)count_until_fail;
	}
}
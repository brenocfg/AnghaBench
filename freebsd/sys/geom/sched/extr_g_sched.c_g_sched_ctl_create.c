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
struct g_provider {int dummy; } ;
struct g_gsched {int dummy; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SCHED_DEBUG (int,char*,char const*) ; 
 struct g_gsched* g_gsched_find (char const*) ; 
 int /*<<< orphan*/  g_gsched_unref (struct g_gsched*) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 char* g_sched_argi (struct gctl_req*,int) ; 
 scalar_t__ g_sched_create (struct gctl_req*,struct g_class*,struct g_provider*,struct g_gsched*,int) ; 
 int g_sched_get_nargs (struct gctl_req*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 

__attribute__((used)) static void
g_sched_ctl_create(struct gctl_req *req, struct g_class *mp, int proxy)
{
	struct g_provider *pp;
	struct g_gsched *gsp;
	const char *name;
	int i, nargs;

	g_topology_assert();

	name = gctl_get_asciiparam(req, "algo");
	if (name == NULL) {
		gctl_error(req, "No '%s' argument", "algo");
		return;
	}

	gsp = g_gsched_find(name);	/* also get a reference */
	if (gsp == NULL) {
		gctl_error(req, "Bad algorithm '%s'", name);
		return;
	}

	nargs = g_sched_get_nargs(req);

	/*
	 * Run on the arguments, and break on any error.
	 * We look for a device name, but skip the /dev/ prefix if any.
	 */
	for (i = 0; i < nargs; i++) {
		name = g_sched_argi(req, i);
		if (name == NULL)
			break;
		pp = g_provider_by_name(name);
		if (pp == NULL) {
			G_SCHED_DEBUG(1, "Provider %s is invalid.", name);
			gctl_error(req, "Provider %s is invalid.", name);
			break;
		}
		if (g_sched_create(req, mp, pp, gsp, proxy) != 0)
			break;
	}

	g_gsched_unref(gsp);
}
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
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  G_MOUNTVER_DEBUG (int,char*,char const*) ; 
 scalar_t__ g_mountver_create (struct gctl_req*,struct g_class*,struct g_provider*) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_mountver_ctl_create(struct gctl_req *req, struct g_class *mp)
{
	struct g_provider *pp;
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
		if (strncmp(name, "/dev/", strlen("/dev/")) == 0)
			name += strlen("/dev/");
		pp = g_provider_by_name(name);
		if (pp == NULL) {
			G_MOUNTVER_DEBUG(1, "Provider %s is invalid.", name);
			gctl_error(req, "Provider %s is invalid.", name);
			return;
		}
		if (g_mountver_create(req, mp, pp) != 0)
			return;
	}
}
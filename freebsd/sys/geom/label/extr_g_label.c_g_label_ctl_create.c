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
struct g_provider {int /*<<< orphan*/  mediasize; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LABEL_DEBUG (int,char*,char const*) ; 
 int /*<<< orphan*/  G_LABEL_DIR ; 
 int /*<<< orphan*/  g_label_create (struct gctl_req*,struct g_class*,struct g_provider*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_label_ctl_create(struct gctl_req *req, struct g_class *mp)
{
	struct g_provider *pp;
	const char *name;
	int *nargs;

	g_topology_assert();

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument", "nargs");
		return;
	}
	if (*nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}
	/*
	 * arg1 is the name of provider.
	 */
	name = gctl_get_asciiparam(req, "arg1");
	if (name == NULL) {
		gctl_error(req, "No 'arg%d' argument", 1);
		return;
	}
	if (strncmp(name, "/dev/", strlen("/dev/")) == 0)
		name += strlen("/dev/");
	pp = g_provider_by_name(name);
	if (pp == NULL) {
		G_LABEL_DEBUG(1, "Provider %s is invalid.", name);
		gctl_error(req, "Provider %s is invalid.", name);
		return;
	}
	/*
	 * arg0 is the label.
	 */
	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%d' argument", 0);
		return;
	}
	g_label_create(req, mp, pp, name, G_LABEL_DIR, pp->mediasize);
}
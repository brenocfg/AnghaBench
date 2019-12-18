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
typedef  scalar_t__ uint32_t ;
struct gctl_req {int dummy; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 scalar_t__ G_MULTIPATH_VERSION ; 
 int /*<<< orphan*/  g_multipath_ctl_add (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_configure (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_create (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_destroy (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_fail (struct gctl_req*,struct g_class*,int) ; 
 int /*<<< orphan*/  g_multipath_ctl_getactive (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_prefer (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_remove (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_rotate (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_multipath_ctl_stop (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 scalar_t__* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
g_multipath_config(struct gctl_req *req, struct g_class *mp, const char *verb)
{
	uint32_t *version;
	g_topology_assert();
	version = gctl_get_paraml(req, "version", sizeof(*version));
	if (version == NULL) {
		gctl_error(req, "No 'version' argument");
	} else if (*version != G_MULTIPATH_VERSION) {
		gctl_error(req, "Userland and kernel parts are out of sync");
	} else if (strcmp(verb, "add") == 0) {
		g_multipath_ctl_add(req, mp);
	} else if (strcmp(verb, "prefer") == 0) {
		g_multipath_ctl_prefer(req, mp);
	} else if (strcmp(verb, "create") == 0) {
		g_multipath_ctl_create(req, mp);
	} else if (strcmp(verb, "configure") == 0) {
		g_multipath_ctl_configure(req, mp);
	} else if (strcmp(verb, "stop") == 0) {
		g_multipath_ctl_stop(req, mp);
	} else if (strcmp(verb, "destroy") == 0) {
		g_multipath_ctl_destroy(req, mp);
	} else if (strcmp(verb, "fail") == 0) {
		g_multipath_ctl_fail(req, mp, 1);
	} else if (strcmp(verb, "restore") == 0) {
		g_multipath_ctl_fail(req, mp, 0);
	} else if (strcmp(verb, "remove") == 0) {
		g_multipath_ctl_remove(req, mp);
	} else if (strcmp(verb, "rotate") == 0) {
		g_multipath_ctl_rotate(req, mp);
	} else if (strcmp(verb, "getactive") == 0) {
		g_multipath_ctl_getactive(req, mp);
	} else {
		gctl_error(req, "Unknown verb %s", verb);
	}
}
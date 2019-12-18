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
struct g_geom {int dummy; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_ccd_create (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_ccd_destroy_geom (struct gctl_req*,struct g_class*,struct g_geom*) ; 
 int /*<<< orphan*/  g_ccd_list (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 struct g_geom* gctl_get_geom (struct gctl_req*,struct g_class*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void
g_ccd_config(struct gctl_req *req, struct g_class *mp, char const *verb)
{
	struct g_geom *gp;

	g_topology_assert();
	if (!strcmp(verb, "create geom")) {
		g_ccd_create(req, mp);
	} else if (!strcmp(verb, "destroy geom")) {
		gp = gctl_get_geom(req, mp, "geom");
		if (gp != NULL)
		g_ccd_destroy_geom(req, mp, gp);
	} else if (!strcmp(verb, "list")) {
		g_ccd_list(req, mp);
	} else {
		gctl_error(req, "unknown verb");
	}
}
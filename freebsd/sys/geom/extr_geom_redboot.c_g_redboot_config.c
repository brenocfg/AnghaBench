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
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 struct g_geom* gctl_get_geom (struct gctl_req*,struct g_class*,char*) ; 

__attribute__((used)) static void
g_redboot_config(struct gctl_req *req, struct g_class *mp, const char *verb)
{
	struct g_geom *gp;

	g_topology_assert();
	gp = gctl_get_geom(req, mp, "geom");
	if (gp == NULL)
		return;
	gctl_error(req, "Unknown verb");
}
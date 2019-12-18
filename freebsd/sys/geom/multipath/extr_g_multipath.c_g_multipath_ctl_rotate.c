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
 struct g_geom* g_multipath_find_geom (struct g_class*,char const*) ; 
 int g_multipath_rotate (struct g_geom*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 

__attribute__((used)) static void
g_multipath_ctl_rotate(struct gctl_req *req, struct g_class *mp)
{
	struct g_geom *gp;
	const char *name;
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
	error = g_multipath_rotate(gp);
	if (error != 0) {
		gctl_error(req, "failed to rotate %s (err=%d)", name, error);
	}
}
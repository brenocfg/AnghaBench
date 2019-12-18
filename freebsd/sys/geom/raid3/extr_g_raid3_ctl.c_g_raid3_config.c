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
 scalar_t__ G_RAID3_VERSION ; 
 int /*<<< orphan*/  g_raid3_ctl_configure (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_raid3_ctl_insert (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_raid3_ctl_rebuild (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_raid3_ctl_remove (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_raid3_ctl_stop (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 scalar_t__* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
g_raid3_config(struct gctl_req *req, struct g_class *mp, const char *verb)
{
	uint32_t *version;

	g_topology_assert();

	version = gctl_get_paraml(req, "version", sizeof(*version));
	if (version == NULL) {
		gctl_error(req, "No '%s' argument.", "version");
		return;
	}
	if (*version != G_RAID3_VERSION) {
		gctl_error(req, "Userland and kernel parts are out of sync.");
		return;
	}

	g_topology_unlock();
	if (strcmp(verb, "configure") == 0)
		g_raid3_ctl_configure(req, mp);
	else if (strcmp(verb, "insert") == 0)
		g_raid3_ctl_insert(req, mp);
	else if (strcmp(verb, "rebuild") == 0)
		g_raid3_ctl_rebuild(req, mp);
	else if (strcmp(verb, "remove") == 0)
		g_raid3_ctl_remove(req, mp);
	else if (strcmp(verb, "stop") == 0)
		g_raid3_ctl_stop(req, mp);
	else
		gctl_error(req, "Unknown verb.");
	g_topology_lock();
}
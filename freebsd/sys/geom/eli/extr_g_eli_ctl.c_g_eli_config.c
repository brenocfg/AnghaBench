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
 scalar_t__ G_ELI_VERSION ; 
 scalar_t__ G_ELI_VERSION_05 ; 
 scalar_t__ G_ELI_VERSION_06 ; 
 scalar_t__ G_ELI_VERSION_07 ; 
 int /*<<< orphan*/  g_eli_ctl_attach (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_configure (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_delkey (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_detach (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_kill (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_onetime (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_resume (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_setkey (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_eli_ctl_suspend (struct gctl_req*,struct g_class*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 scalar_t__* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
g_eli_config(struct gctl_req *req, struct g_class *mp, const char *verb)
{
	uint32_t *version;

	g_topology_assert();

	version = gctl_get_paraml(req, "version", sizeof(*version));
	if (version == NULL) {
		gctl_error(req, "No '%s' argument.", "version");
		return;
	}
	while (*version != G_ELI_VERSION) {
		if (G_ELI_VERSION == G_ELI_VERSION_06 &&
		    *version == G_ELI_VERSION_05) {
			/* Compatible. */
			break;
		}
		if (G_ELI_VERSION == G_ELI_VERSION_07 &&
		    (*version == G_ELI_VERSION_05 ||
		     *version == G_ELI_VERSION_06)) {
			/* Compatible. */
			break;
		}
		gctl_error(req, "Userland and kernel parts are out of sync.");
		return;
	}

	if (strcmp(verb, "attach") == 0)
		g_eli_ctl_attach(req, mp);
	else if (strcmp(verb, "detach") == 0 || strcmp(verb, "stop") == 0)
		g_eli_ctl_detach(req, mp);
	else if (strcmp(verb, "onetime") == 0)
		g_eli_ctl_onetime(req, mp);
	else if (strcmp(verb, "configure") == 0)
		g_eli_ctl_configure(req, mp);
	else if (strcmp(verb, "setkey") == 0)
		g_eli_ctl_setkey(req, mp);
	else if (strcmp(verb, "delkey") == 0)
		g_eli_ctl_delkey(req, mp);
	else if (strcmp(verb, "suspend") == 0)
		g_eli_ctl_suspend(req, mp);
	else if (strcmp(verb, "resume") == 0)
		g_eli_ctl_resume(req, mp);
	else if (strcmp(verb, "kill") == 0)
		g_eli_ctl_kill(req, mp);
	else
		gctl_error(req, "Unknown verb.");
}
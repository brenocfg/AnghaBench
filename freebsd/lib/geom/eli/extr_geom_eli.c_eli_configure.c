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

/* Variables and functions */
 int /*<<< orphan*/  eli_configure_detached (struct gctl_req*,char const*,int,int,int,int,int) ; 
 int /*<<< orphan*/  eli_is_attached (char const*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  gctl_issue (struct gctl_req*) ; 

__attribute__((used)) static void
eli_configure(struct gctl_req *req)
{
	const char *prov;
	bool boot, noboot, geliboot, nogeliboot, displaypass, nodisplaypass;
	bool autoresize, noautoresize, trim, notrim;
	int doboot, dogeliboot, dodisplaypass, dotrim, doautoresize;
	int i, nargs;

	nargs = gctl_get_int(req, "nargs");
	if (nargs == 0) {
		gctl_error(req, "Too few arguments.");
		return;
	}

	boot = gctl_get_int(req, "boot");
	noboot = gctl_get_int(req, "noboot");
	geliboot = gctl_get_int(req, "geliboot");
	nogeliboot = gctl_get_int(req, "nogeliboot");
	displaypass = gctl_get_int(req, "displaypass");
	nodisplaypass = gctl_get_int(req, "nodisplaypass");
	trim = gctl_get_int(req, "trim");
	notrim = gctl_get_int(req, "notrim");
	autoresize = gctl_get_int(req, "autoresize");
	noautoresize = gctl_get_int(req, "noautoresize");

	doboot = -1;
	if (boot && noboot) {
		gctl_error(req, "Options -b and -B are mutually exclusive.");
		return;
	}
	if (boot)
		doboot = 1;
	else if (noboot)
		doboot = 0;

	dogeliboot = -1;
	if (geliboot && nogeliboot) {
		gctl_error(req, "Options -g and -G are mutually exclusive.");
		return;
	}
	if (geliboot)
		dogeliboot = 1;
	else if (nogeliboot)
		dogeliboot = 0;

	dodisplaypass = -1;
	if (displaypass && nodisplaypass) {
		gctl_error(req, "Options -d and -D are mutually exclusive.");
		return;
	}
	if (displaypass)
		dodisplaypass = 1;
	else if (nodisplaypass)
		dodisplaypass = 0;

	dotrim = -1;
	if (trim && notrim) {
		gctl_error(req, "Options -t and -T are mutually exclusive.");
		return;
	}
	if (trim)
		dotrim = 1;
	else if (notrim)
		dotrim = 0;

	doautoresize = -1;
	if (autoresize && noautoresize) {
		gctl_error(req, "Options -r and -R are mutually exclusive.");
		return;
	}
	if (autoresize)
		doautoresize = 1;
	else if (noautoresize)
		doautoresize = 0;

	if (doboot == -1 && dogeliboot == -1 && dodisplaypass == -1 &&
	    dotrim == -1 && doautoresize == -1) {
		gctl_error(req, "No option given.");
		return;
	}

	/* First attached providers. */
	gctl_issue(req);
	/* Now the rest. */
	for (i = 0; i < nargs; i++) {
		prov = gctl_get_ascii(req, "arg%d", i);
		if (!eli_is_attached(prov)) {
			eli_configure_detached(req, prov, doboot, dogeliboot,
			    dodisplaypass, dotrim, doautoresize);
		}
	}
}
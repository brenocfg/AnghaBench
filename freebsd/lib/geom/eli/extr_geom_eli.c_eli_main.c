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
 unsigned int G_FLAG_VERBOSE ; 
 int /*<<< orphan*/  eli_attach (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_backup (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_clear (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_configure (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_delkey (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_dump (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_init (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_kill (struct gctl_req*) ; 
 int eli_protect (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_resize (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_restore (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_resume (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_setkey (struct gctl_req*) ; 
 int /*<<< orphan*/  eli_version (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int verbose ; 

__attribute__((used)) static void
eli_main(struct gctl_req *req, unsigned int flags)
{
	const char *name;

	if (eli_protect(req) == -1)
		return;

	if ((flags & G_FLAG_VERBOSE) != 0)
		verbose = 1;

	name = gctl_get_ascii(req, "verb");
	if (name == NULL) {
		gctl_error(req, "No '%s' argument.", "verb");
		return;
	}
	if (strcmp(name, "init") == 0 || strcmp(name, "label") == 0)
		eli_init(req);
	else if (strcmp(name, "attach") == 0)
		eli_attach(req);
	else if (strcmp(name, "configure") == 0)
		eli_configure(req);
	else if (strcmp(name, "setkey") == 0)
		eli_setkey(req);
	else if (strcmp(name, "delkey") == 0)
		eli_delkey(req);
	else if (strcmp(name, "resume") == 0)
		eli_resume(req);
	else if (strcmp(name, "kill") == 0)
		eli_kill(req);
	else if (strcmp(name, "backup") == 0)
		eli_backup(req);
	else if (strcmp(name, "restore") == 0)
		eli_restore(req);
	else if (strcmp(name, "resize") == 0)
		eli_resize(req);
	else if (strcmp(name, "version") == 0)
		eli_version(req);
	else if (strcmp(name, "dump") == 0)
		eli_dump(req);
	else if (strcmp(name, "clear") == 0)
		eli_clear(req);
	else
		gctl_error(req, "Unknown command: %s.", name);
}
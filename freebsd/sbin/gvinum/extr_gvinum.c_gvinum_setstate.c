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
 int GV_FLAG_F ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 int getopt (int,char* const*,char*) ; 
 int optind ; 
 int optreset ; 
 scalar_t__ strcmp (char* const,char*) ; 
 int /*<<< orphan*/  warn (char*,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
gvinum_setstate(int argc, char * const *argv)
{
	struct gctl_req *req;
	int flags, i;
	const char *errstr;

	flags = 0;

	optreset = 1;
	optind = 1;

	while ((i = getopt(argc, argv, "f")) != -1) {
		switch (i) {
		case 'f':
			flags |= GV_FLAG_F;
			break;
		case '?':
		default:
			warn("invalid flag: %c", i);
			return;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 2) {
		warnx("usage: setstate [-f] <state> <obj>");
		return;
	}

	/*
	 * XXX: This hack is needed to avoid tripping over (now) invalid
	 * 'classic' vinum states and will go away later.
	 */
	if (strcmp(argv[0], "up") && strcmp(argv[0], "down") &&
	    strcmp(argv[0], "stale")) {
		warnx("invalid state '%s'", argv[0]);
		return;
	}

	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");
	gctl_ro_param(req, "verb", -1, "setstate");
	gctl_ro_param(req, "state", -1, argv[0]);
	gctl_ro_param(req, "object", -1, argv[1]);
	gctl_ro_param(req, "flags", sizeof(int), &flags);

	errstr = gctl_issue(req);
	if (errstr != NULL)
		warnx("%s", errstr);
	gctl_free(req);
}
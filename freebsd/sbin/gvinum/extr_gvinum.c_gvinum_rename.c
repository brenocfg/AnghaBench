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
 int GV_FLAG_R ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 int getopt (int,char* const*,char*) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
gvinum_rename(int argc, char * const *argv)
{
	struct gctl_req *req;
	const char *errstr;
	int flags, j;

	flags = 0;

	if (argc) {
		optreset = 1;
		optind = 1;
		while ((j = getopt(argc, argv, "r")) != -1) {
			switch (j) {
			case 'r':
				flags |= GV_FLAG_R;
				break;
			default:
				return;
			}
		}
		argc -= optind;
		argv += optind;
	}

	switch (argc) {
		case 0:
			warnx("no object to rename specified");
			return;
		case 1:
			warnx("no new name specified");
			return;
		case 2:
			break;
		default:
			warnx("more than one new name specified");
			return;
	}

	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");
	gctl_ro_param(req, "verb", -1, "rename");
	gctl_ro_param(req, "flags", sizeof(int), &flags);
	gctl_ro_param(req, "object", -1, argv[0]);
	gctl_ro_param(req, "newname", -1, argv[1]);
	errstr = gctl_issue(req);
	if (errstr != NULL)
		warnx("can't rename object:  %s", errstr);
	gctl_free(req);
}
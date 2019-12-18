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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int GV_FLAG_F ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 int getopt (int,char* const*,char*) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
gvinum_move(int argc, char * const *argv)
{
	struct gctl_req *req;
	const char *errstr;
	char buf[20];
	int flags, i, j;

	flags = 0;
	if (argc) {
		optreset = 1;
		optind = 1;
		while ((j = getopt(argc, argv, "f")) != -1) {
			switch (j) {
			case 'f':
				flags |= GV_FLAG_F;
				break;
			case '?':
			default:
				return;
			}
		}
		argc -= optind;
		argv += optind;
	}

	switch (argc) {
		case 0:
			warnx("no destination or object(s) to move specified");
			return;
		case 1:
			warnx("no object(s) to move specified");
			return;
		default:
			break;
	}

	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");
	gctl_ro_param(req, "verb", -1, "move");
	gctl_ro_param(req, "argc", sizeof(int), &argc);
	gctl_ro_param(req, "flags", sizeof(int), &flags);
	gctl_ro_param(req, "destination", -1, argv[0]);
	for (i = 1; i < argc; i++) {
		snprintf(buf, sizeof(buf), "argv%d", i);
		gctl_ro_param(req, buf, -1, argv[i]);
	}
	errstr = gctl_issue(req);
	if (errstr != NULL)
		warnx("can't move object(s):  %s", errstr);
	gctl_free(req);
}
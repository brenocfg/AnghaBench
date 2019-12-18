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
 int GV_FLAG_R ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 int getopt (int,char* const*,char*) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
gvinum_rm(int argc, char * const *argv)
{
	struct gctl_req *req;
	int flags, i, j;
	const char *errstr;
	char buf[20];

	flags = 0;
	optreset = 1;
	optind = 1;
	while ((j = getopt(argc, argv, "rf")) != -1) {
		switch (j) {
		case 'f':
			flags |= GV_FLAG_F;
			break;
		case 'r':
			flags |= GV_FLAG_R;
			break;
		default:
			return;
		}
	}
	argc -= optind;
	argv += optind;

	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");
	gctl_ro_param(req, "verb", -1, "remove");
	gctl_ro_param(req, "argc", sizeof(int), &argc);
	gctl_ro_param(req, "flags", sizeof(int), &flags);
	if (argc) {
		for (i = 0; i < argc; i++) {
			snprintf(buf, sizeof(buf), "argv%d", i);
			gctl_ro_param(req, buf, -1, argv[i]);
		}
	}
	errstr = gctl_issue(req);
	if (errstr != NULL) {
		warnx("can't remove: %s", errstr);
		gctl_free(req);
		return;
	}
	gctl_free(req);
}
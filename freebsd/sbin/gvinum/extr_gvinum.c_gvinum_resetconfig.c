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
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int GV_FLAG_F ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char*) ; 
 int getopt (int,char* const*,char*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
gvinum_resetconfig(int argc, char * const *argv)
{
	struct gctl_req *req;
	const char *errstr;
	char reply[32];
	int flags, i;

	flags = 0;
	while ((i = getopt(argc, argv, "f")) != -1) {
		switch (i) {
		case 'f':
			flags |= GV_FLAG_F;
			break;
		default:
			warn("invalid flag: %c", i);
			return;
		}
	}
	if ((flags & GV_FLAG_F) == 0) {
		if (!isatty(STDIN_FILENO)) {
			warn("Please enter this command from a tty device\n");
			return;
		}
		printf(" WARNING!  This command will completely wipe out"
		    " your gvinum configuration.\n"
		    " All data will be lost.  If you really want to do this,"
		    " enter the text\n\n"
		    " NO FUTURE\n"
		    " Enter text -> ");
		fgets(reply, sizeof(reply), stdin);
		if (strcmp(reply, "NO FUTURE\n")) {
			printf("\n No change\n");
			return;
		}
	}
	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");
	gctl_ro_param(req, "verb", -1, "resetconfig");
	errstr = gctl_issue(req);
	if (errstr != NULL) {
		warnx("can't reset config: %s", errstr);
		gctl_free(req);
		return;
	}
	gctl_free(req);
	printf("gvinum configuration obliterated\n");
}
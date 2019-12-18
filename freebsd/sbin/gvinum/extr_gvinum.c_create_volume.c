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
typedef  char off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int GV_FLAG_F ; 
 int GV_FLAG_S ; 
 int GV_FLAG_V ; 
 int /*<<< orphan*/  GV_MAXVOLNAME ; 
 int /*<<< orphan*/  GV_TYPE_VOL ; 
 char* create_drive (char* const) ; 
 char* find_name (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,...) ; 
 char gv_sizespec (char* const) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

__attribute__((used)) static void
create_volume(int argc, char * const *argv, const char *verb)
{
	struct gctl_req *req;
	const char *errstr;
	char buf[BUFSIZ], *drivename, *volname;
	int drives, flags, i;
	off_t stripesize;

	flags = 0;
	drives = 0;
	volname = NULL;
	stripesize = 262144;

	/* XXX: Should we check for argument length? */

	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-f")) {
			flags |= GV_FLAG_F;
		} else if (!strcmp(argv[i], "-n")) {
			volname = argv[++i];
		} else if (!strcmp(argv[i], "-v")) {
			flags |= GV_FLAG_V;
		} else if (!strcmp(argv[i], "-s")) {
			flags |= GV_FLAG_S;
			if (!strcmp(verb, "raid5"))
				stripesize = gv_sizespec(argv[++i]);
		} else {
			/* Assume it's a drive. */
			snprintf(buf, sizeof(buf), "drive%d", drives++);

			/* First we create the drive. */
			drivename = create_drive(argv[i]);
			if (drivename == NULL)
				goto bad;
			/* Then we add it to the request. */
			gctl_ro_param(req, buf, -1, drivename);
		}
	}

	gctl_ro_param(req, "stripesize", sizeof(off_t), &stripesize);

	/* Find a free volume name. */
	if (volname == NULL)
		volname = find_name("gvinumvolume", GV_TYPE_VOL, GV_MAXVOLNAME);

	/* Then we send a request to actually create the volumes. */
	gctl_ro_param(req, "verb", -1, verb);
	gctl_ro_param(req, "flags", sizeof(int), &flags);
	gctl_ro_param(req, "drives", sizeof(int), &drives);
	gctl_ro_param(req, "name", -1, volname);
	errstr = gctl_issue(req);
	if (errstr != NULL)
		warnx("creating %s volume failed: %s", verb, errstr);
bad:
	gctl_free(req);
}
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
 int /*<<< orphan*/  GV_CFG_LEN ; 
#define  GV_TYPE_DRIVE 131 
#define  GV_TYPE_PLEX 130 
#define  GV_TYPE_SD 129 
#define  GV_TYPE_VOL 128 
 char* find_pattern (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char*) ; 
 int /*<<< orphan*/  gctl_rw_param (struct gctl_req*,char*,int,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static char *
find_name(const char *prefix, int type, int namelen)
{
	struct gctl_req *req;
	char comment[1], buf[GV_CFG_LEN - 1], *sname, *ptr;
	const char *errstr, *name;
	int i, n, begin, len, conflict;
	char line[1024];

	comment[0] = '\0';

	/* Find a name. Fetch out configuration first. */
	req = gctl_get_handle();
	gctl_ro_param(req, "class", -1, "VINUM");
	gctl_ro_param(req, "verb", -1, "getconfig");
	gctl_ro_param(req, "comment", -1, comment);
	gctl_rw_param(req, "config", sizeof(buf), buf);
	errstr = gctl_issue(req);
	if (errstr != NULL) {
		warnx("can't get configuration: %s", errstr);
		return (NULL);
	}
	gctl_free(req);

	begin = 0;
	len = strlen(buf);
	i = 0;
	sname = malloc(namelen + 1);

	/* XXX: Max object setting? */
	for (n = 0; n < 10000; n++) {
		snprintf(sname, namelen, "%s%d", prefix, n);
		conflict = 0;
		begin = 0;
		/* Loop through the configuration line by line. */
		for (i = 0; i < len; i++) {
			if (buf[i] == '\n' || buf[i] == '\0') {
				ptr = buf + begin;
				strlcpy(line, ptr, (i - begin) + 1);
				begin = i + 1;
				switch (type) {
				case GV_TYPE_DRIVE:
					name = find_pattern(line, "drive");
					break;
				case GV_TYPE_VOL:
					name = find_pattern(line, "volume");
					break;
				case GV_TYPE_PLEX:
				case GV_TYPE_SD:
					name = find_pattern(line, "name");
					break;
				default:
					printf("Invalid type given\n");
					continue;
				}
				if (name == NULL)
					continue;
				if (!strcmp(sname, name)) {
					conflict = 1;
					/* XXX: Could quit the loop earlier. */
				}
			}
		}
		if (!conflict)
			return (sname);
	}
	free(sname);
	return (NULL);
}
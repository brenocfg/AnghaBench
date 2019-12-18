#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct group {int /*<<< orphan*/  gr_mem; TYPE_1__* gr_passwd; TYPE_1__* gr_name; int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_5__ {int /*<<< orphan*/  sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct group*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,char*) ; 
 TYPE_1__* sl_init () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 char* strsep (char**,char const*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static int
group_read_snapshot_func(struct group *grp, char *line)
{
	StringList *sl;
	char *s, *ps, *ts;
	const char *sep;
	int i;

	printf("1 line read from snapshot:\n%s\n", line);

	i = 0;
	sl = NULL;
	ps = line;
	sep = ":";
	memset(grp, 0, sizeof(struct group));
	while ((s = strsep(&ps, sep)) != NULL) {
		switch (i) {
		case 0:
			grp->gr_name = strdup(s);
			ATF_REQUIRE(grp->gr_name != NULL);
			break;

		case 1:
			grp->gr_passwd = strdup(s);
			ATF_REQUIRE(grp->gr_passwd != NULL);
			break;

		case 2:
			grp->gr_gid = (gid_t)strtol(s, &ts, 10);
			if (*ts != '\0') {
				free(grp->gr_name);
				free(grp->gr_passwd);
				grp->gr_name = NULL;
				grp->gr_passwd = NULL;
				return (-1);
			}
			/* Change to parsing groups. */
			sep = ",";
			break;

		default:
			if (sl == NULL) {
				if (strcmp(s, "(null)") == 0)
					return (0);

				sl = sl_init();
				ATF_REQUIRE(sl != NULL);

				if (strcmp(s, "nomem") != 0) {
					ts = strdup(s);
					ATF_REQUIRE(ts != NULL);
					sl_add(sl, ts);
				}
			} else {
				ts = strdup(s);
				ATF_REQUIRE(ts != NULL);
				sl_add(sl, ts);
			}
			break;
		}
		++i;
	}

	if (i < 3) {
		free(grp->gr_name);
		free(grp->gr_passwd);
		memset(grp, 0, sizeof(struct group));
		return (-1);
	}

	sl_add(sl, NULL);
	grp->gr_mem = sl->sl_str;

	/* NOTE: is it a dirty hack or not? */
	free(sl);
	return (0);
}